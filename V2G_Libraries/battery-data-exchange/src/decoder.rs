//! Semantic decoder: **tokens → typed fields + per-field diagnostics**.
//!
//! Interpret each `RawField` according to the protocol schema (by tag), producing a
//! `Field` with typed `Value`s, units, and precise byte ranges. This stage
//! emits per-field diagnostics for issues within a token’s semantics:
//! wrong length for this tag, invalid UTF‑8, unknown enum variant, suspicious but
//! decodable values (as WARN).

use crate::Field;
use crate::scanner::RawField;

/// Decode a `RawField` into a `Field` and emit diagnostics on decoding issues.
pub fn decode_raw_field(raw: &RawField) -> Field {
    todo!()
}
