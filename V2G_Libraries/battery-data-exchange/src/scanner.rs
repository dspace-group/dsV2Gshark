//! Structural scanner: **bytes → tokens** (no per-tag semantics).
//!
//! Parse the raw byte slice into a sequence of structural tokens (e.g., TLV items),
//! preserving precise byte ranges for both the whole token and its value region.

use nom::{
    IResult, Parser,
    bytes::complete::take,
    multi::many0,
    number::complete::{be_u16, u8},
};
use num_traits::ToPrimitive;
use std::ops::Range;

use crate::{Diagnostic, KnownTag};

#[derive(Debug, Clone)]
pub struct RawField<'a> {
    pub tag: u8,
    pub value: &'a [u8],
    pub range: Range<usize>,
}

#[derive(Debug, Clone)]
pub struct ScannerResult<'a> {
    pub fields: Vec<RawField<'a>>,
    pub diagnostics: Vec<Diagnostic>,
}

/// Parse one Tag-Length-Value field
fn parse_field(input: &[u8]) -> IResult<&[u8], RawField<'_>> {
    let start = input.as_ptr() as usize;

    let (input, tag) = u8(input)?;
    let (input, len) = if tag
        == KnownTag::BatteryCellVoltageAll
            .to_u8()
            .expect("Expected u8")
    {
        // special handling for "Battery Cell Voltage" (tag 0xA7) => length field has two bytes
        be_u16(input)?
    } else {
        let (input, len) = u8(input)?;
        (input, u16::from(len))
    };
    let (input, value) = take(len)(input)?;

    let end = input.as_ptr() as usize;
    let range = start..end;

    Ok((input, RawField { tag, value, range }))
}

fn parse_all_fields(input: &[u8]) -> IResult<&[u8], Vec<RawField<'_>>> {
    many0(parse_field).parse(input)
}

/// Normalize the range values so that it is 0-based
fn normalize_ranges(fields: &mut [RawField], original_data: &[u8]) {
    let start_pos = original_data.as_ptr() as usize;
    for f in fields.iter_mut() {
        f.range = (f.range.start - start_pos)..(f.range.end - start_pos);
    }
}

/// Parse the raw byte slice into a sequence of raw tag-value fields.
/// The value is not decoded and represented as a raw byte slice.
pub fn parse(input: &[u8]) -> ScannerResult<'_> {
    match parse_all_fields(input) {
        Ok((remaining, mut fields)) => {
            normalize_ranges(&mut fields, input);
            let diagnostics = if remaining.is_empty() {
                vec![]
            } else {
                vec![Diagnostic::RemainingBytes(remaining.len())]
            };
            ScannerResult {
                fields,
                diagnostics,
            }
        }
        Err(err) => ScannerResult {
            fields: vec![],
            diagnostics: vec![Diagnostic::ParseError(err.to_string())],
        },
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn basic() {
        let data = [0xC1, 1, 42];

        let result = parse(&data);
        assert_eq!(result.diagnostics.len(), 0);

        let fields = result.fields;
        assert_eq!(fields.len(), 1);
        assert_eq!(fields[0].tag, 0xC1);
        assert_eq!(fields[0].value, &[42]);
        assert_eq!(fields[0].range, 0..3);
    }

    #[test]
    fn special_tag() {
        let data = [0xA7, 0, 1, 42];

        let result = parse(&data);
        assert_eq!(result.diagnostics.len(), 0);

        let fields = result.fields;
        assert_eq!(fields.len(), 1);
        assert_eq!(fields[0].tag, 0xA7);
        assert_eq!(fields[0].value, &[42]);
        assert_eq!(fields[0].range, 0..4);
    }

    #[test]
    fn two_fields() {
        let data = [0xC1, 1, 42, 0xA3, 1, 43];

        let result = parse(&data);
        assert_eq!(result.diagnostics.len(), 0);

        let fields = result.fields;
        assert_eq!(fields.len(), 2);
        assert_eq!(fields[0].tag, 0xC1);
        assert_eq!(fields[0].value, &[42]);
        assert_eq!(fields[0].range, 0..3);
        assert_eq!(fields[1].tag, 0xA3);
        assert_eq!(fields[1].value, &[43]);
        assert_eq!(fields[1].range, 3..6);
    }

    #[test]
    fn len0() {
        let data = [0xC1, 0];

        let result = parse(&data);
        assert_eq!(result.diagnostics.len(), 0);

        let fields = result.fields;
        assert_eq!(fields.len(), 1);
        assert_eq!(fields[0].tag, 0xC1);
        assert_eq!(fields[0].value, &[]);
        assert_eq!(fields[0].range, 0..2);
    }

    #[test]
    fn remaining() {
        let data = [0xC1, 1, 42, 11];

        let result = parse(&data);
        assert_eq!(result.diagnostics.len(), 1);
        assert_eq!(result.diagnostics[0], Diagnostic::RemainingBytes(1));

        let fields = result.fields;
        assert_eq!(fields.len(), 1);
    }

    #[test]
    fn wrong_format() {
        let data = [0xC1, 2, 42];

        let result = parse(&data);
        assert_eq!(result.diagnostics.len(), 1);
        assert_eq!(result.diagnostics[0], Diagnostic::RemainingBytes(3));
        let fields = result.fields;
        assert_eq!(fields.len(), 0);
    }
}
