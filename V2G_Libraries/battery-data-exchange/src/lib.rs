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
        let bytes = [
            161, 4, 104, 116, 221, 234, 162, 17, 75, 77, 72, 69, 77, 52, 50, 65, 80, 88, 65, 49,
            50, 51, 52, 53, 54, 163, 1, 148,
        ];

        let result = decode(&bytes);
        assert_eq!(result.consumed_bytes, bytes.len());
        assert_eq!(result.fields.len(), 3);
        assert_eq!(
            result.fields[0],
            Field {
                tag: Tag::Known(KnownTag::Timestamp),
                value: Value::U32(1752489450),
                unit: Some("utc_s"),
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
        let diagnostics_without_info: Vec<&Diagnostic> = result
            .diagnostics
            .iter()
            .filter_map(|f| {
                if f.get_severity() == Severity::Info {
                    None
                } else {
                    Some(f)
                }
            })
            .collect();
        assert!(diagnostics_without_info.is_empty());
    }
}
