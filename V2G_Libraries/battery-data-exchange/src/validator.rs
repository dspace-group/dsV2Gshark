//! Cross-field validators: **fields → additional diagnostics** (no bytes parsed here).
//!
//! Enforce relationships between fields that require seeing more than one decoded value.
use crate::{Diagnostic, Field, KnownTag, Tag};

/// Run cross-field validations.
pub fn validate(fields: &[Field]) -> Vec<Diagnostic> {
    let mut diagnostics = Vec::new();

    let tags: Vec<KnownTag> = fields
        .iter()
        .filter_map(|f| {
            if let Tag::Known(t) = f.tag {
                Some(t)
            } else {
                None
            }
        })
        .collect();
    // let groups : Vec<TagGroup> = tags
    //     .iter()
    //     .map(|t| todo!("Implement `fn group(&self) -> TagGroup` for KnownTag and call it here"))
    //     .collect();

    //TODO check for duplicated tags or groups, check order of tags, check case A+B+C, check ...
    diagnostics
}
