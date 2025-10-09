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
