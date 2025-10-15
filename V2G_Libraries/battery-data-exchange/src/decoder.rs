//! Semantic decoder: **tokens → typed fields + per-field diagnostics**.
//!
//! Interpret each `RawField` according to the protocol schema (by tag), producing a
//! `Field` with typed `Value`s, units, and precise byte ranges. This stage
//! emits per-field diagnostics for issues within a token’s semantics:
//! wrong length for this tag, invalid UTF‑8, unknown enum variant, suspicious but
//! decodable values (as WARN).

use crate::scanner::RawField;
use crate::{Diagnostic, Field, KnownTag, Tag, Value};

/// Decode a `RawField` into a `Field` and emit diagnostics on decoding issues.
pub fn decode_raw_field(raw: &RawField) -> Field {
    let mut diagnostics = Vec::new();
    let tag = Tag::from(raw.tag);
    let (value, unit) = match tag {
        Tag::Unknown(code) => {
            diagnostics.push(Diagnostic::UnknownTag(code));
            (Value::Raw(raw.value.to_vec()), None)
        }
        Tag::Known(kt) => match kt {
            // --- Group A (select one) ---
            KnownTag::Timestamp => (decode_u32(raw.value, &mut diagnostics), Some("s")),
            KnownTag::SessionDuration => (decode_u32(raw.value, &mut diagnostics), Some("s")),
            KnownTag::Counter => (decode_u16(raw.value, &mut diagnostics), None),
            // // --- Group B (select one) ---
            KnownTag::Vin => (decode_vin(raw.value, &mut diagnostics), None),
            KnownTag::BatteryId => (decode_string(raw.value, &mut diagnostics), None),
            KnownTag::EncryptedVin => (decode_encrypted_vin(raw.value, &mut diagnostics), None),
            // // --- Group C ---
            KnownTag::StateOfCharge => {
                (decode_percent(raw.value, 0.5, &mut diagnostics), Some("%"))
            }
            // // --- Group D ---
            KnownTag::StateOfHealth => {
                (decode_percent(raw.value, 1.0, &mut diagnostics), Some("%"))
            }
            // --- Group E ---
            KnownTag::BatteryPackCurrent => {
                (decode_f16(raw.value, 0.1, 0.0, &mut diagnostics), Some("A"))
            }
            // --- Group F ---
            KnownTag::BatteryPackVoltage => {
                (decode_f16(raw.value, 0.1, 0.0, &mut diagnostics), Some("V"))
            }
            // --- Group G (select one) ---
            KnownTag::BatteryCellVoltageAll => (
                decode_f8_array(raw.value, 0.02, 0.0, &mut diagnostics),
                Some("V"),
            ),
            KnownTag::BatteryCellVoltageMaxMin => (
                decode_maxmin_array(raw.value, 0.02, 0.0, &mut diagnostics),
                Some("V"),
            ),
            // --- Group H (select one) ---
            KnownTag::BatteryTemperatureAll => (
                decode_f8_array(raw.value, 1.0, -40.0, &mut diagnostics),
                Some("°C"),
            ),
            KnownTag::BatteryTemperatureMaxMin => (
                decode_maxmin_array(raw.value, 1.0, -40., &mut diagnostics),
                Some("°C"),
            ),
        },
    };
    Field {
        tag,
        value,
        unit,
        range: raw.range.clone(),
        diagnostics,
    }
}

fn decode_u16(input: &[u8], diagnostics: &mut Vec<Diagnostic>) -> Value {
    if input.len() == 2 {
        Value::U16(u16::from_be_bytes([input[0], input[1]]))
    } else {
        diagnostics.push(Diagnostic::UnexpectedLength(input.len()));
        Value::Raw(input.to_vec())
    }
}
fn decode_u32(input: &[u8], diagnostics: &mut Vec<Diagnostic>) -> Value {
    if input.len() == 4 {
        Value::U32(u32::from_be_bytes([input[0], input[1], input[2], input[3]]))
    } else {
        diagnostics.push(Diagnostic::UnexpectedLength(input.len()));
        Value::Raw(input.to_vec())
    }
}
fn decode_f8(input: &[u8], gain: f32, offset: f32, diagnostics: &mut Vec<Diagnostic>) -> Value {
    if input.len() == 1 {
        let value = u8::from_be_bytes([input[0]]);
        if value == 0xFF {
            diagnostics.push(Diagnostic::InvalidValue);
            Value::Float(f32::NAN)
        } else {
            Value::Float(f32::from(value) * gain + offset)
        }
    } else {
        diagnostics.push(Diagnostic::UnexpectedLength(input.len()));
        Value::Raw(input.to_vec())
    }
}
fn decode_f16(input: &[u8], gain: f32, offset: f32, diagnostics: &mut Vec<Diagnostic>) -> Value {
    if input.len() == 2 {
        let value = u16::from_be_bytes([input[0], input[1]]);
        if value == 0xFFFF {
            diagnostics.push(Diagnostic::InvalidValue);
            Value::Float(f32::NAN)
        } else {
            Value::Float(f32::from(value) * gain + offset)
        }
    } else {
        diagnostics.push(Diagnostic::UnexpectedLength(input.len()));
        Value::Raw(input.to_vec())
    }
}
fn decode_f8_array(
    input: &[u8],
    gain: f32,
    offset: f32,
    diagnostics: &mut Vec<Diagnostic>,
) -> Value {
    let vec: Vec<f32> = input
        .iter()
        .map(|b| {
            let value = u8::from_be_bytes([*b]);
            if value == 0xFF {
                if !diagnostics.contains(&Diagnostic::InvalidValue) {
                    diagnostics.push(Diagnostic::InvalidValue);
                }
                f32::NAN
            } else {
                f32::from(value) * gain + offset
            }
        })
        .collect();
    Value::FloatArray(vec)
}
fn decode_string(input: &[u8], diagnostics: &mut Vec<Diagnostic>) -> Value {
    if input.iter().all(|&b| b == 0x00) {
        // see note 39 of specification
        diagnostics.push(Diagnostic::InvalidValue);
        return Value::Raw(input.to_vec());
    }
    if let Ok(s) = std::str::from_utf8(input) {
        Value::Str(s.to_string())
    } else {
        diagnostics.push(Diagnostic::StringDecodingError);
        Value::Raw(input.to_vec())
    }
}
fn decode_vin(input: &[u8], diagnostics: &mut Vec<Diagnostic>) -> Value {
    if input.len() != 17 && input.iter().any(|&b| b != 0x00) {
        diagnostics.push(Diagnostic::UnexpectedLength(input.len()));
    }
    decode_string(input, diagnostics)
}
fn decode_encrypted_vin(input: &[u8], diagnostics: &mut Vec<Diagnostic>) -> Value {
    // Spec: either 32 bytes (VIN enc) or 97 bytes (VIN enc + uncompressed V_pub)
    if input.len() != 32 && input.len() != 97 && input.iter().any(|&b| b != 0x00) {
        diagnostics.push(Diagnostic::UnexpectedLength(input.len()));
    }
    Value::Raw(input.to_vec())
}
fn decode_percent(input: &[u8], gain: f32, diagnostics: &mut Vec<Diagnostic>) -> Value {
    let result = decode_f8(input, gain, 0.0, diagnostics);
    if let Value::Float(f) = result
        && !(0.0..=100.0).contains(&f)
    {
        diagnostics.push(Diagnostic::OutOfRange);
    }
    result
}
fn decode_maxmin_array(
    input: &[u8],
    gain: f32,
    offset: f32,
    diagnostics: &mut Vec<Diagnostic>,
) -> Value {
    if input.len() == 2 {
        let result = decode_f8_array(input, gain, offset, diagnostics);
        if let Value::FloatArray(arr) = &result {
            if arr[0] < arr[1] {
                diagnostics.push(Diagnostic::MinGreaterThanMax);
            }
        } else {
            panic!("Unexpected array length");
        }
        result
    } else {
        diagnostics.push(Diagnostic::UnexpectedLength(input.len()));
        Value::Raw(input.to_vec())
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::scanner::RawField;
    use crate::{Diagnostic, KnownTag, Tag, Value};
    fn rf(tag_u8: u8, val: &[u8]) -> RawField<'_> {
        // Simulate the range length as a scanner would produce:
        // - A7 uses 2-byte length field
        let total = if tag_u8 == KnownTag::BatteryCellVoltageAll as u8 {
            1 + 2 + val.len()
        } else {
            1 + 1 + val.len()
        };
        RawField {
            tag: tag_u8,
            value: val,
            range: 0..total,
        }
    }

    // --- Group A: Timestamp (0xA1), SessionDuration (0xB1), Counter (0xC1)
    #[test]
    fn timestamp_ok() {
        let f = decode_raw_field(&rf(KnownTag::Timestamp as u8, &[0x00, 0x00, 0x00, 0x2A]));
        assert_eq!(f.tag, Tag::Known(KnownTag::Timestamp));
        assert_eq!(f.unit, Some("s"));
        assert_eq!(f.value, Value::U32(42));
        assert!(f.diagnostics.is_empty());
    }
    #[test]
    fn timestamp_bad_len() {
        let f = decode_raw_field(&rf(KnownTag::Timestamp as u8, &[0x00, 0x00, 0x2A])); // 3 bytes
        assert_eq!(f.tag, Tag::Known(KnownTag::Timestamp));
        assert_eq!(f.unit, Some("s"));
        assert_eq!(f.value, Value::Raw(vec![0x00, 0x00, 0x2A]));
        assert_eq!(f.diagnostics[0], Diagnostic::UnexpectedLength(3));
    }
    #[test]
    fn session_duration_ok() {
        let f = decode_raw_field(&rf(
            KnownTag::SessionDuration as u8,
            &[0x00, 0x00, 0x00, 0x03],
        ));
        assert_eq!(f.tag, Tag::Known(KnownTag::SessionDuration));
        assert_eq!(f.unit, Some("s"));
        assert_eq!(f.value, Value::U32(3));
        assert!(f.diagnostics.is_empty());
    }
    #[test]
    fn session_duration_bad_len() {
        let f = decode_raw_field(&rf(KnownTag::SessionDuration as u8, &[]));
        assert_eq!(f.tag, Tag::Known(KnownTag::SessionDuration));
        assert_eq!(f.unit, Some("s"));
        assert_eq!(f.value, Value::Raw(vec![]));
        assert_eq!(f.diagnostics[0], Diagnostic::UnexpectedLength(0));
    }
    #[test]
    fn counter_ok() {
        let f = decode_raw_field(&rf(KnownTag::Counter as u8, &[0x01, 0x2C])); // 300
        assert_eq!(f.tag, Tag::Known(KnownTag::Counter));
        assert_eq!(f.unit, None);
        assert_eq!(f.value, Value::U16(300));
        assert!(f.diagnostics.is_empty());
    }
    #[test]
    fn counter_bad_len() {
        let f = decode_raw_field(&rf(KnownTag::Counter as u8, &[0x2C])); // 1 byte
        assert_eq!(f.tag, Tag::Known(KnownTag::Counter));
        assert_eq!(f.unit, None);
        assert_eq!(f.value, Value::Raw(vec![0x2c]));
        assert_eq!(f.diagnostics[0], Diagnostic::UnexpectedLength(1));
    }
    // --- Group B: VIN (0xA2), BatteryId (0xB2), EncryptedVIN (0xC2)
    #[test]
    fn vin_ok() {
        let vin = b"KMHEM42APXA123456"; // 17 bytes ASCII
        let f = decode_raw_field(&rf(KnownTag::Vin as u8, vin));
        assert_eq!(f.tag, Tag::Known(KnownTag::Vin));
        assert_eq!(f.unit, None);
        assert_eq!(f.value, Value::Str("KMHEM42APXA123456".to_string()));
        assert!(f.diagnostics.is_empty());
    }
    #[test]
    fn vin_no_ascii() {
        let vin = b"K\x80HEM42APXA123456"; // 2. byte is non-ASCII
        let f = decode_raw_field(&rf(KnownTag::Vin as u8, vin));
        assert_eq!(f.tag, Tag::Known(KnownTag::Vin));
        assert_eq!(f.unit, None);
        // Spec: invalid VIN -> diagnostic + keep raw
        assert_eq!(f.value, Value::Raw(vin.into()));
        assert!(f.diagnostics.contains(&Diagnostic::StringDecodingError));
    }
    #[test]
    fn vin_zero_17() {
        let vin = [0; 17];
        let f = decode_raw_field(&rf(KnownTag::Vin as u8, &vin));
        assert_eq!(f.tag, Tag::Known(KnownTag::Vin));
        assert_eq!(f.unit, None);
        assert_eq!(f.value, Value::Raw(vin.into()));
        assert_eq!(f.diagnostics[0], Diagnostic::InvalidValue);
    }
    #[test]
    fn vin_zero_1() {
        let vin = [0];
        let f = decode_raw_field(&rf(KnownTag::Vin as u8, &vin));
        assert_eq!(f.tag, Tag::Known(KnownTag::Vin));
        assert_eq!(f.unit, None);
        assert_eq!(f.value, Value::Raw(vin.into()));
        assert_eq!(f.diagnostics[0], Diagnostic::InvalidValue);
    }
    #[test]
    fn vin_bad_len() {
        let f = decode_raw_field(&rf(KnownTag::Vin as u8, &[0xAA; 18]));
        assert_eq!(f.tag, Tag::Known(KnownTag::Vin));
        assert_eq!(f.unit, None);
        assert_eq!(f.value, Value::Raw(vec![0xAA; 18]));
        assert_eq!(f.diagnostics[0], Diagnostic::UnexpectedLength(18));
    }
    #[test]
    fn battery_id_ok() {
        let id = b"K13243EM42A223BC";
        let f = decode_raw_field(&rf(KnownTag::BatteryId as u8, id));
        assert_eq!(f.tag, Tag::Known(KnownTag::BatteryId));
        assert_eq!(f.unit, None);
        assert_eq!(f.value, Value::Str("K13243EM42A223BC".into()));
        assert!(f.diagnostics.is_empty());
    }
    #[test]
    fn battery_id_zero() {
        let id = [0];
        let f = decode_raw_field(&rf(KnownTag::BatteryId as u8, &id));
        assert_eq!(f.tag, Tag::Known(KnownTag::BatteryId));
        assert_eq!(f.unit, None);
        assert_eq!(f.value, Value::Raw(id.into()));
        assert_eq!(f.diagnostics[0], Diagnostic::InvalidValue);
    }
    #[test]
    fn encrypted_vin_ok_32() {
        // see [V2GBIP_M03_012]
        let vin = [42; 32];
        let f = decode_raw_field(&rf(KnownTag::EncryptedVin as u8, &vin));
        assert_eq!(f.tag, Tag::Known(KnownTag::EncryptedVin));
        assert_eq!(f.unit, None);
        assert_eq!(f.value, Value::Raw(vin.into()));
        assert!(f.diagnostics.is_empty());
    }
    #[test]
    fn encrypted_vin_ok_97() {
        // see [V2GBIP_M03_013]
        let vin = [42; 97];
        let f = decode_raw_field(&rf(KnownTag::EncryptedVin as u8, &vin));
        assert_eq!(f.tag, Tag::Known(KnownTag::EncryptedVin));
        assert_eq!(f.unit, None);
        assert_eq!(f.value, Value::Raw(vin.into()));
        assert!(f.diagnostics.is_empty());
    }
    #[test]
    fn encrypted_vin_bad_len() {
        let f = decode_raw_field(&rf(KnownTag::EncryptedVin as u8, &[0xAA; 31]));
        assert_eq!(f.tag, Tag::Known(KnownTag::EncryptedVin));
        assert_eq!(f.unit, None);
        assert_eq!(f.value, Value::Raw(vec![0xAA; 31]));
        assert_eq!(f.diagnostics[0], Diagnostic::UnexpectedLength(31));
    }
    // --- Group C: SoC (0xA3)
    #[test]
    fn soc_ok() {
        // 0x64 = 100 -> 100 * 0.5 = 50.0%
        let f = decode_raw_field(&rf(KnownTag::StateOfCharge as u8, &[0x64]));
        assert_eq!(f.tag, Tag::Known(KnownTag::StateOfCharge));
        assert_eq!(f.unit, Some("%"));
        assert_eq!(f.value, Value::Float(50.0));
        assert!(f.diagnostics.is_empty());
    }
    #[test]
    fn soc_out_of_range() {
        let f = decode_raw_field(&rf(KnownTag::StateOfCharge as u8, &[0]));
        assert_eq!(f.value, Value::Float(0.0));
        assert!(f.diagnostics.is_empty());

        let f = decode_raw_field(&rf(KnownTag::StateOfCharge as u8, &[200]));
        assert_eq!(f.value, Value::Float(100.0));
        assert!(f.diagnostics.is_empty());

        let f = decode_raw_field(&rf(KnownTag::StateOfCharge as u8, &[201]));
        assert_eq!(f.value, Value::Float(100.5));
        assert_eq!(f.diagnostics[0], Diagnostic::OutOfRange);
    }
    #[test]
    fn soc_invalid_ff() {
        let f = decode_raw_field(&rf(KnownTag::StateOfCharge as u8, &[0xFF]));
        assert_eq!(f.tag, Tag::Known(KnownTag::StateOfCharge));
        assert_eq!(f.unit, Some("%"));
        if let Value::Float(val) = f.value {
            assert!(val.is_nan());
        } else {
            panic!("Expected float");
        }
        assert_eq!(f.diagnostics[0], Diagnostic::InvalidValue);
    }
    #[test]
    fn soc_bad_len() {
        let f = decode_raw_field(&rf(KnownTag::StateOfCharge as u8, &[0x01, 0x02]));
        assert_eq!(f.tag, Tag::Known(KnownTag::StateOfCharge));
        assert_eq!(f.unit, Some("%"));
        assert_eq!(f.value, Value::Raw(vec![0x01, 0x02]));
        assert_eq!(f.diagnostics[0], Diagnostic::UnexpectedLength(2));
    }
    // --- Group D: SoH (0xA4)
    #[test]
    fn soh_ok() {
        let f = decode_raw_field(&rf(KnownTag::StateOfHealth as u8, &[42]));
        assert_eq!(f.tag, Tag::Known(KnownTag::StateOfHealth));
        assert_eq!(f.unit, Some("%"));
        assert_eq!(f.value, Value::Float(42.0));
        assert!(f.diagnostics.is_empty());
    }
    #[test]
    fn soh_out_of_range() {
        let f = decode_raw_field(&rf(KnownTag::StateOfHealth as u8, &[0]));
        assert_eq!(f.value, Value::Float(0.0));
        assert!(f.diagnostics.is_empty());

        let f = decode_raw_field(&rf(KnownTag::StateOfHealth as u8, &[100]));
        assert_eq!(f.value, Value::Float(100.0));
        assert!(f.diagnostics.is_empty());

        let f = decode_raw_field(&rf(KnownTag::StateOfHealth as u8, &[101]));
        assert_eq!(f.value, Value::Float(101.0));
        assert_eq!(f.diagnostics[0], Diagnostic::OutOfRange);
    }
    #[test]
    fn soh_invalid_ff() {
        let f = decode_raw_field(&rf(KnownTag::StateOfHealth as u8, &[0xFF]));
        assert_eq!(f.tag, Tag::Known(KnownTag::StateOfHealth));
        assert_eq!(f.unit, Some("%"));
        if let Value::Float(val) = f.value {
            assert!(val.is_nan());
        } else {
            panic!("Expected float");
        }
        assert_eq!(f.diagnostics[0], Diagnostic::InvalidValue);
    }
    #[test]
    fn soh_bad_len() {
        let f = decode_raw_field(&rf(KnownTag::StateOfHealth as u8, &[0x01, 0x02]));
        assert_eq!(f.tag, Tag::Known(KnownTag::StateOfHealth));
        assert_eq!(f.unit, Some("%"));
        assert_eq!(f.value, Value::Raw(vec![0x01, 0x02]));
        assert_eq!(f.diagnostics[0], Diagnostic::UnexpectedLength(2));
    }
    // --- Group E: Battery Pack Current (0xA5)
    #[test]
    fn pack_current_ok() {
        // 0x011C = 284 -> 28.4 A
        let f = decode_raw_field(&rf(KnownTag::BatteryPackCurrent as u8, &[0x01, 0x1C]));
        assert_eq!(f.tag, Tag::Known(KnownTag::BatteryPackCurrent));
        assert_eq!(f.unit, Some("A"));
        assert_eq!(f.value, Value::Float(28.4));
        assert!(f.diagnostics.is_empty());
    }
    #[test]
    fn pack_current_invalid_ffff() {
        let f = decode_raw_field(&rf(KnownTag::BatteryPackCurrent as u8, &[0xFF, 0xFF]));
        assert_eq!(f.tag, Tag::Known(KnownTag::BatteryPackCurrent));
        assert_eq!(f.unit, Some("A"));
        if let Value::Float(val) = f.value {
            assert!(val.is_nan());
        } else {
            panic!("Expected float");
        }
        assert_eq!(f.diagnostics[0], Diagnostic::InvalidValue);
    }
    #[test]
    fn pack_current_bad_len() {
        let f = decode_raw_field(&rf(KnownTag::BatteryPackCurrent as u8, &[0x00]));
        assert_eq!(f.tag, Tag::Known(KnownTag::BatteryPackCurrent));
        assert_eq!(f.unit, Some("A"));
        assert_eq!(f.value, Value::Raw(vec![0x00]));
        assert_eq!(f.diagnostics[0], Diagnostic::UnexpectedLength(1));
    }
    // --- Group F: Battery Pack Voltage (0xA6)
    #[test]
    fn pack_voltage_ok() {
        // 0x0EEF = 3823 -> 382.3 v
        let f = decode_raw_field(&rf(KnownTag::BatteryPackVoltage as u8, &[0x0E, 0xEF]));
        assert_eq!(f.tag, Tag::Known(KnownTag::BatteryPackVoltage));
        assert_eq!(f.unit, Some("V"));
        assert_eq!(f.value, Value::Float(382.30002));
        assert!(f.diagnostics.is_empty());
    }
    #[test]
    fn pack_voltage_invalid_ffff() {
        let f = decode_raw_field(&rf(KnownTag::BatteryPackVoltage as u8, &[0xFF, 0xFF]));
        assert_eq!(f.tag, Tag::Known(KnownTag::BatteryPackVoltage));
        assert_eq!(f.unit, Some("V"));
        if let Value::Float(val) = f.value {
            assert!(val.is_nan());
        } else {
            panic!("Expected float");
        }
        assert_eq!(f.diagnostics[0], Diagnostic::InvalidValue);
    }
    #[test]
    fn pack_voltage_bad_len() {
        let f = decode_raw_field(&rf(KnownTag::BatteryPackVoltage as u8, &[0x00]));
        assert_eq!(f.tag, Tag::Known(KnownTag::BatteryPackVoltage));
        assert_eq!(f.unit, Some("V"));
        assert_eq!(f.value, Value::Raw(vec![0x00]));
        assert_eq!(f.diagnostics[0], Diagnostic::UnexpectedLength(1));
    }
    // --- Group G: Battery Cell Voltage (All / MaxMin)
    #[test]
    fn cell_voltage_all_ok() {
        // 0xC0 -> 3.84 V, 0xBD -> 3.78 V, 0xBE -> 3.80 V
        let f = decode_raw_field(&rf(
            KnownTag::BatteryCellVoltageAll as u8,
            &[0xC0, 0xBD, 0xBE],
        ));
        assert_eq!(f.tag, Tag::Known(KnownTag::BatteryCellVoltageAll));
        assert_eq!(f.unit, Some("V"));
        assert_eq!(f.value, Value::FloatArray(vec![3.84, 3.78, 3.80]));
        assert!(f.diagnostics.is_empty());
    }
    #[test]
    fn cell_voltage_all_ok_with_invalids() {
        // 0xC0 -> 3.84 V, 0xFF -> invalid (NaN), 0xBE -> 3.80 V
        let f = decode_raw_field(&rf(
            KnownTag::BatteryCellVoltageAll as u8,
            &[0xC0, 0xFF, 0xBE],
        ));
        assert_eq!(f.tag, Tag::Known(KnownTag::BatteryCellVoltageAll));
        assert_eq!(f.unit, Some("V"));
        if let Value::FloatArray(arr) = f.value {
            assert_eq!(arr.len(), 3);
            assert_eq!(arr[0], 3.84);
            assert!(arr[1].is_nan());
            assert_eq!(arr[2], 3.80);
        } else {
            panic!("Expected float array");
        }
        assert_eq!(f.diagnostics[0], Diagnostic::InvalidValue);
    }
    #[test]
    fn cell_voltage_all_max_len() {
        let f = decode_raw_field(&rf(KnownTag::BatteryCellVoltageAll as u8, &[0xC0; 65535]));
        assert_eq!(f.tag, Tag::Known(KnownTag::BatteryCellVoltageAll));
        assert_eq!(f.unit, Some("V"));
        assert_eq!(f.value, Value::FloatArray(vec![3.84; 65535]));
        assert!(f.diagnostics.is_empty());
    }
    #[test]
    fn cell_voltage_maxmin_ok() {
        // 0xC0 -> 3.84 V, 0xBD -> 3.78 V
        let f = decode_raw_field(&rf(KnownTag::BatteryCellVoltageMaxMin as u8, &[0xC0, 0xBD]));
        assert_eq!(f.tag, Tag::Known(KnownTag::BatteryCellVoltageMaxMin));
        assert_eq!(f.unit, Some("V"));
        assert_eq!(f.value, Value::FloatArray(vec![3.84, 3.78]));
        assert!(f.diagnostics.is_empty());
    }
    #[test]
    fn cell_voltage_maxmin_warning() {
        // 0xC0 -> 3.84 V, 0xBD -> 3.78 V
        let f = decode_raw_field(&rf(KnownTag::BatteryCellVoltageMaxMin as u8, &[0xBD, 0xC0]));
        assert_eq!(f.tag, Tag::Known(KnownTag::BatteryCellVoltageMaxMin));
        assert_eq!(f.unit, Some("V"));
        assert_eq!(f.value, Value::FloatArray(vec![3.78, 3.84]));
        assert_eq!(f.diagnostics[0], Diagnostic::MinGreaterThanMax);
    }
    #[test]
    fn cell_voltage_maxmin_ok_with_invalids() {
        // 0xC0 -> 3.84 V, 0xFF -> invalid (NaN)
        let f = decode_raw_field(&rf(KnownTag::BatteryCellVoltageMaxMin as u8, &[0xC0, 0xFF]));
        assert_eq!(f.tag, Tag::Known(KnownTag::BatteryCellVoltageMaxMin));
        assert_eq!(f.unit, Some("V"));
        if let Value::FloatArray(arr) = f.value {
            assert_eq!(arr.len(), 2);
            assert_eq!(arr[0], 3.84);
            assert!(arr[1].is_nan());
        } else {
            panic!("Expected float array");
        }
        assert_eq!(f.diagnostics[0], Diagnostic::InvalidValue);
    }
    #[test]
    fn cell_voltage_maxmin_bad_len() {
        let f = decode_raw_field(&rf(KnownTag::BatteryCellVoltageMaxMin as u8, &[0xC0; 3]));
        assert_eq!(f.tag, Tag::Known(KnownTag::BatteryCellVoltageMaxMin));
        assert_eq!(f.unit, Some("V"));
        assert_eq!(f.value, Value::Raw(vec![0xC0; 3]));
        assert_eq!(f.diagnostics[0], Diagnostic::UnexpectedLength(3));
    }
    // --- Group H: Battery Temperature (All / MaxMin)
    #[test]
    fn temperature_all_ok() {
        // 0x3F -> 23 °C (63-40), 0x3D -> 21 °C (61-40), 0xFE -> 214 °C (254-40)
        let f = decode_raw_field(&rf(
            KnownTag::BatteryTemperatureAll as u8,
            &[0x3F, 0x3D, 0xFE],
        ));
        assert_eq!(f.tag, Tag::Known(KnownTag::BatteryTemperatureAll));
        assert_eq!(f.unit, Some("°C"));
        assert_eq!(f.value, Value::FloatArray(vec![23.0, 21.0, 214.0]));
        assert!(f.diagnostics.is_empty());
    }
    #[test]
    fn temperature_all_ok_with_invalids() {
        // 0x3F -> 23 °C (63-40), 0xFF -> NAN (invalid), 0xFE -> 214 °C (254-40)
        let f = decode_raw_field(&rf(
            KnownTag::BatteryTemperatureAll as u8,
            &[0x3F, 0xFF, 0xFE],
        ));
        assert_eq!(f.tag, Tag::Known(KnownTag::BatteryTemperatureAll));
        assert_eq!(f.unit, Some("°C"));
        if let Value::FloatArray(arr) = f.value {
            assert_eq!(arr.len(), 3);
            assert_eq!(arr[0], 23.0);
            assert!(arr[1].is_nan());
            assert_eq!(arr[2], 214.0);
        } else {
            panic!("Expected float array");
        }
        assert_eq!(f.diagnostics[0], Diagnostic::InvalidValue);
    }
    #[test]
    fn temperature_all_max_len() {
        let f = decode_raw_field(&rf(KnownTag::BatteryTemperatureAll as u8, &[0x3F; 255]));
        assert_eq!(f.tag, Tag::Known(KnownTag::BatteryTemperatureAll));
        assert_eq!(f.unit, Some("°C"));
        assert_eq!(f.value, Value::FloatArray(vec![23.0; 255]));
        assert!(f.diagnostics.is_empty());
    }
    #[test]
    fn temperature_maxmin_ok() {
        // 0x3F -> 23 °C (63-40), 0x3D -> 21 °C (61-40)
        let f = decode_raw_field(&rf(KnownTag::BatteryTemperatureMaxMin as u8, &[0x3F, 0x3D]));
        assert_eq!(f.tag, Tag::Known(KnownTag::BatteryTemperatureMaxMin));
        assert_eq!(f.unit, Some("°C"));
        assert_eq!(f.value, Value::FloatArray(vec![23.0, 21.0]));
        assert!(f.diagnostics.is_empty());
    }
    #[test]
    fn temperature_maxmin_warning() {
        // 0x3F -> 23 °C (63-40), 0x3D -> 21 °C (61-40)
        let f = decode_raw_field(&rf(KnownTag::BatteryTemperatureMaxMin as u8, &[0x3D, 0x3F]));
        assert_eq!(f.tag, Tag::Known(KnownTag::BatteryTemperatureMaxMin));
        assert_eq!(f.unit, Some("°C"));
        assert_eq!(f.value, Value::FloatArray(vec![21.0, 23.0]));
        assert_eq!(f.diagnostics[0], Diagnostic::MinGreaterThanMax);
    }
    #[test]
    fn temperature_maxmin_ok_with_invalids() {
        // 0x3F -> 23 °C (63-40), 0xFF -> NAN (invalid)
        let f = decode_raw_field(&rf(KnownTag::BatteryTemperatureMaxMin as u8, &[0x3F, 0xFF]));
        assert_eq!(f.tag, Tag::Known(KnownTag::BatteryTemperatureMaxMin));
        assert_eq!(f.unit, Some("°C"));
        if let Value::FloatArray(arr) = f.value {
            assert_eq!(arr.len(), 2);
            assert_eq!(arr[0], 23.0);
            assert!(arr[1].is_nan());
        } else {
            panic!("Expected float array");
        }
        assert_eq!(f.diagnostics[0], Diagnostic::InvalidValue);
    }
    #[test]
    fn temperature_maxmin_bad_len() {
        let f = decode_raw_field(&rf(KnownTag::BatteryTemperatureMaxMin as u8, &[0x3F; 1]));
        assert_eq!(f.tag, Tag::Known(KnownTag::BatteryTemperatureMaxMin));
        assert_eq!(f.unit, Some("°C"));
        assert_eq!(f.value, Value::Raw(vec![0x3F; 1]));
        assert_eq!(f.diagnostics[0], Diagnostic::UnexpectedLength(1));
    }
    // --- Unknown tag
    #[test]
    fn unknown_tag_raw_with_diag() {
        let f = decode_raw_field(&rf(0xEE, &[0x01, 0x02, 0x03]));
        assert_eq!(f.tag, Tag::Unknown(0xEE));
        assert_eq!(f.value, Value::Raw(vec![0x01, 0x02, 0x03]));
        assert_eq!(f.diagnostics[0], Diagnostic::UnknownTag(0xEE));
    }
}
