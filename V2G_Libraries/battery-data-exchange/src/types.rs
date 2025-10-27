//! Shared data model for the decoder pipeline
//!
//! This module is intentionally free of parsing/validation logic.
//! All stages (tag scanning, per-tag decode, cross-field validate) depend on this.

use num_derive::{FromPrimitive, ToPrimitive};
use num_traits::FromPrimitive;
use std::fmt::Write;
use std::{fmt::Display, ops::Range};

#[derive(Debug, PartialEq, Eq, Clone)]
pub enum Diagnostic {
    ParseError(String),
    RemainingBytes(usize),
    UnknownTag(u8),
    UnexpectedLength(usize),
    OutOfRange,
    StringDecodingError,
    MinGreaterThanMax,
    InvalidValue,
    FrameCompositionError(String),
    Info(String),
}

impl Diagnostic {
    #[must_use]
    pub fn get_severity(&self) -> Severity {
        match self {
            Diagnostic::ParseError(_)
            | Diagnostic::RemainingBytes(_)
            | Diagnostic::UnexpectedLength(_)
            | Diagnostic::FrameCompositionError(_)
            | Diagnostic::UnknownTag(_) => Severity::Error,
            Diagnostic::OutOfRange
            | Diagnostic::StringDecodingError
            | Diagnostic::MinGreaterThanMax => Severity::Warning,
            Diagnostic::InvalidValue | Diagnostic::Info(_) => Severity::Info,
        }
    }
}

impl Display for Diagnostic {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Self::ParseError(msg) => write!(f, "Parse error: {msg}"),
            Self::RemainingBytes(n) => write!(f, "Remaining unparsed bytes: {n}"),
            Self::UnknownTag(tag) => write!(f, "Unknown tag: 0x{tag:02X}"),
            Self::UnexpectedLength(len) => write!(f, "Unexpected length: {len}"),
            Self::OutOfRange => write!(f, "Value out of range"),
            Self::StringDecodingError => write!(f, "Cannot decode input as ASCII string"),
            Self::MinGreaterThanMax => write!(f, "Minimum is greater than maximum"),
            Self::InvalidValue => write!(f, "Invalid value encountered"),
            Self::FrameCompositionError(msg) => write!(f, "Validate error: {msg}"),
            Self::Info(msg) => write!(f, "{msg}"),
        }
    }
}

#[derive(Debug, PartialEq, Eq, PartialOrd, Ord)]
pub enum Severity {
    Error,
    Warning,
    Info,
}

#[derive(Debug, PartialEq, Eq, Clone)]
pub enum DecodeOutcome {
    /// at least one error in the diagnostics
    Error,
    ///  at least one warning in the diagnostics, no errors
    Warning,
    /// no diagnostics, or only informational notes
    Ok,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, FromPrimitive, ToPrimitive)]
pub enum KnownTag {
    Timestamp = 0xA1,
    SessionDuration = 0xB1,
    Counter = 0xC1,
    Vin = 0xA2,
    BatteryId = 0xB2,
    EncryptedVin = 0xC2,
    StateOfCharge = 0xA3,
    StateOfHealth = 0xA4,
    BatteryPackCurrent = 0xA5,
    BatteryPackVoltage = 0xA6,
    BatteryCellVoltageAll = 0xA7,
    BatteryCellVoltageMaxMin = 0xB7,
    BatteryTemperatureAll = 0xA8,
    BatteryTemperatureMaxMin = 0xB8,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Tag {
    Known(KnownTag),
    Unknown(u8),
}

impl core::convert::From<u8> for Tag {
    fn from(v: u8) -> Self {
        match KnownTag::from_u8(v) {
            Some(tag) => Self::Known(tag),
            None => Self::Unknown(v),
        }
    }
}

impl core::fmt::Display for Tag {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        match self {
            Tag::Known(tag) => match tag {
                KnownTag::Timestamp => write!(f, "Timestamp"),
                KnownTag::SessionDuration => write!(f, "Session Duration"),
                KnownTag::Counter => write!(f, "Counter"),
                KnownTag::Vin => write!(f, "VIN"),
                KnownTag::BatteryId => write!(f, "Battery ID"),
                KnownTag::EncryptedVin => write!(f, "Encrypted VIN"),
                KnownTag::StateOfCharge => write!(f, "SoC"),
                KnownTag::StateOfHealth => write!(f, "SoH"),
                KnownTag::BatteryPackCurrent => write!(f, "Battery Pack Current"),
                KnownTag::BatteryPackVoltage => write!(f, "Battery Pack Voltage"),
                KnownTag::BatteryCellVoltageAll => write!(f, "Battery Cell Voltage (All)"),
                KnownTag::BatteryCellVoltageMaxMin => write!(f, "Battery Cell Voltage (Max/Min)"),
                KnownTag::BatteryTemperatureAll => write!(f, "Battery Temperature (All)"),
                KnownTag::BatteryTemperatureMaxMin => write!(f, "Battery Temperature (Max/Min)"),
            },
            Tag::Unknown(t) => write!(f, "[Unknown tag 0x{t:02X}]"),
        }
    }
}

#[derive(Clone, Debug, PartialEq)]
pub enum Value {
    U16(u16),
    U32(u32),
    Float(f32),
    Str(String),
    FloatArray(Vec<f32>),
    Raw(Vec<u8>),
    None,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Field {
    pub tag: Tag,
    pub value: Value,
    pub unit: Option<&'static str>,
    /// Range of this field in the original input array
    pub range: Range<usize>,
    /// Diagnostics tied to a specific field
    pub diagnostics: Vec<Diagnostic>,
}

impl Field {
    /// Human-friendly value + unit rendering.
    #[must_use]
    pub fn to_display_string(&self) -> String {
        fn with_unit<S: Display>(s: S, unit: Option<&'static str>) -> String {
            match unit {
                Some(u) if !u.is_empty() => format!("{s}\u{202F}{u}"),
                _ => s.to_string(),
            }
        }
        fn fmt_float(f: f32) -> String {
            if f.is_nan() {
                "---".into()
            } else {
                format!("{f:.2}")
            }
        }
        fn fmt_float_array(values: &[f32], unit: Option<&'static str>) -> String {
            format!(
                "[{}]",
                values
                    .iter()
                    .map(|v| with_unit(fmt_float(*v), unit))
                    .collect::<Vec<_>>()
                    .join(", ")
            )
        }

        match &self.value {
            Value::U16(v) => with_unit(v, self.unit),
            Value::U32(v) => with_unit(v, self.unit),
            Value::Float(v) => with_unit(fmt_float(*v), self.unit),
            Value::FloatArray(vals) => fmt_float_array(vals, self.unit),
            Value::Str(s) => s.clone(),
            Value::Raw(bytes) => format!(
                "0x{}",
                bytes.iter().fold(String::new(), |mut output, b| {
                    let _ = write!(output, "{b:02x}");
                    output
                })
            ),
            Value::None => String::from("---"),
        }
    }
}

pub struct DecodeResult {
    /// Total bytes consumed from the start of the provided buffer.
    pub consumed_bytes: usize,
    /// Top-level fields (in order of appearance).
    pub fields: Vec<Field>,
    /// Diagnostics not tied to a specific field (or applicable to the entire frame/section).
    pub diagnostics: Vec<Diagnostic>,
}

impl DecodeResult {
    /// Computes highest severity across all diagnostics for this result.
    #[must_use]
    pub fn decode_outcome(&self) -> DecodeOutcome {
        let max_severity = self
            .fields
            .iter()
            .flat_map(|f| &f.diagnostics)
            .chain(&self.diagnostics)
            .map(Diagnostic::get_severity)
            .min();
        match max_severity {
            Some(Severity::Error) => DecodeOutcome::Error,
            Some(Severity::Warning) => DecodeOutcome::Warning,
            _ => DecodeOutcome::Ok,
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn decode_outcome() {
        let mut result = DecodeResult {
            consumed_bytes: 42,
            fields: vec![
                Field {
                    tag: Tag::Unknown(42),
                    value: crate::Value::None,
                    unit: None,
                    range: 0..1,
                    diagnostics: vec![],
                },
                Field {
                    tag: Tag::Unknown(42),
                    value: crate::Value::None,
                    unit: None,
                    range: 0..1,
                    diagnostics: vec![],
                },
            ],
            diagnostics: vec![],
        };
        assert_eq!(result.decode_outcome(), DecodeOutcome::Ok);

        result.fields[0].diagnostics.push(Diagnostic::InvalidValue);
        assert_eq!(result.decode_outcome(), DecodeOutcome::Ok);

        result.diagnostics.push(Diagnostic::OutOfRange);
        assert_eq!(result.decode_outcome(), DecodeOutcome::Warning);

        result.fields[1]
            .diagnostics
            .push(Diagnostic::UnexpectedLength(1));
        assert_eq!(result.decode_outcome(), DecodeOutcome::Error);
    }

    #[test]
    fn display_string() {
        let mut field = Field {
            tag: Tag::Unknown(42),
            value: crate::Value::None,
            unit: None,
            range: 0..1,
            diagnostics: vec![],
        };

        assert_eq!(field.to_display_string(), "---");

        field.unit = Some("A");
        assert_eq!(field.to_display_string(), "---");

        field.value = Value::Str(String::from("test"));
        assert_eq!(field.to_display_string(), "test");

        field.value = Value::U16(16);
        assert_eq!(field.to_display_string(), "16\u{202f}A");

        field.value = Value::U32(32);
        assert_eq!(field.to_display_string(), "32\u{202f}A");

        field.value = Value::Float(1.234_567_8);
        assert_eq!(field.to_display_string(), "1.23\u{202f}A");

        field.value = Value::Float(f32::NAN);
        assert_eq!(field.to_display_string(), "---\u{202f}A");

        field.unit = None;
        assert_eq!(field.to_display_string(), "---");

        field.value = Value::FloatArray(vec![1.234_567, 2.345_678_9]);
        assert_eq!(field.to_display_string(), "[1.23, 2.35]");

        field.unit = Some("°C");
        assert_eq!(
            field.to_display_string(),
            "[1.23\u{202f}°C, 2.35\u{202f}°C]"
        );

        field.value = Value::Raw(vec![0xde, 0xad, 0xbe, 0xef]);
        assert_eq!(field.to_display_string(), "0xdeadbeef");
    }
}
