mod decoder;
mod lua_bindings;
mod scanner;
mod types;
mod validator;
pub use types::*;

#[must_use]
/// Decode one frame from a byte slice.
pub fn decode(input: &[u8]) -> DecodeResult {
    let scanned = scanner::parse(input);
    let fields: Vec<Field> = scanned
        .fields
        .iter()
        .map(decoder::decode_raw_field)
        .collect();

    let mut diagnostics = scanned.diagnostics;
    diagnostics.extend(validator::validate(&fields));

    // Consumed = end of the last field range (0 if none)
    let consumed_bytes = fields.iter().map(|f| f.range.end).max().unwrap_or(0);

    DecodeResult {
        consumed_bytes,
        fields,
        diagnostics,
    }
}
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn basic() {
        let bytes =
            hex::decode("a1046874ddeaa2114b4d48454d343241505841313233343536a30194").unwrap();

        let result = decode(&bytes);
        assert_eq!(result.consumed_bytes, bytes.len());
        assert_eq!(result.fields.len(), 3);
        assert_eq!(
            result.fields[0],
            Field {
                tag: Tag::Known(KnownTag::Timestamp),
                value: Value::U32(1752489450),
                unit: Some("s"),
                range: 0..6,
                diagnostics: vec![]
            }
        );
        assert_eq!(
            result.fields[1],
            Field {
                tag: Tag::Known(KnownTag::Vin),
                value: Value::Str("KMHEM42APXA123456".into()),
                unit: None,
                range: 6..25,
                diagnostics: vec![]
            }
        );
        assert_eq!(
            result.fields[2],
            Field {
                tag: Tag::Known(KnownTag::StateOfCharge),
                value: Value::Float(74.0),
                unit: Some("%"),
                range: 25..28,
                diagnostics: vec![]
            }
        );

        for d in result.diagnostics {
            assert_eq!(d.get_severity(), Severity::Info);
        }
    }

    #[test]
    fn advanced() {
        let bytes = hex::decode(
            "a1046874ddeaa2114b4d48454d343241505841313233343536a30194a401fea502011ca6020eefb702c0bdb8023f3d",
        )
        .unwrap();

        let result = decode(&bytes);
        assert_eq!(result.consumed_bytes, bytes.len());
        assert_eq!(result.fields.len(), 8);
        assert_eq!(
            result.fields[0],
            Field {
                tag: Tag::Known(KnownTag::Timestamp),
                value: Value::U32(1752489450),
                unit: Some("s"),
                range: 0..6,
                diagnostics: vec![]
            }
        );
        assert_eq!(
            result.fields[1],
            Field {
                tag: Tag::Known(KnownTag::Vin),
                value: Value::Str("KMHEM42APXA123456".into()),
                unit: None,
                range: 6..25,
                diagnostics: vec![]
            }
        );
        assert_eq!(
            result.fields[2],
            Field {
                tag: Tag::Known(KnownTag::StateOfCharge),
                value: Value::Float(74.0),
                unit: Some("%"),
                range: 25..28,
                diagnostics: vec![]
            }
        );
        assert_eq!(
            result.fields[3],
            Field {
                tag: Tag::Known(KnownTag::StateOfHealth),
                value: Value::Float(254.0),
                unit: Some("%"),
                range: 28..31,
                diagnostics: vec![Diagnostic::OutOfRange]
            }
        );
        assert_eq!(
            result.fields[4],
            Field {
                tag: Tag::Known(KnownTag::BatteryPackCurrent),
                value: Value::Float(28.4),
                unit: Some("A"),
                range: 31..35,
                diagnostics: vec![]
            }
        );
        assert_eq!(
            result.fields[5],
            Field {
                tag: Tag::Known(KnownTag::BatteryPackVoltage),
                value: Value::Float(382.30002),
                unit: Some("V"),
                range: 35..39,
                diagnostics: vec![]
            }
        );
        assert_eq!(
            result.fields[6],
            Field {
                tag: Tag::Known(KnownTag::BatteryCellVoltageMaxMin),
                value: Value::FloatArray(vec![3.84, 3.78]),
                unit: Some("V"),
                range: 39..43,
                diagnostics: vec![]
            }
        );
        assert_eq!(
            result.fields[7],
            Field {
                tag: Tag::Known(KnownTag::BatteryTemperatureMaxMin),
                value: Value::FloatArray(vec![23.0, 21.0]),
                unit: Some("°C"),
                range: 43..47,
                diagnostics: vec![]
            }
        );

        for d in result.diagnostics {
            assert_eq!(d.get_severity(), Severity::Info);
        }
    }
}
