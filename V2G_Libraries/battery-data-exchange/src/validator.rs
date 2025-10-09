//! Cross-field validators: **fields -> additional diagnostics** (no bytes parsed here).
//!
//! Enforce relationships between fields that require seeing more than one decoded value.
//! Also enforce the per-spec frame composition (“CASE” matching).
//!
//! References (Battery Data Exchange Protocol 2025-05-27):
//! - §3.1 table (Groups/Tags/Lengths/Ranges/Units)
//! - §3.3 (CASE 1 / CASE 2 / CASE 3 frame compositions)
//!
use crate::{Diagnostic, Field, KnownTag, Tag};

/// Logical group as per §3.1 table.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum TagGroup {
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
}

impl KnownTag {
    fn group(self) -> TagGroup {
        #[allow(clippy::enum_glob_use)]
        use KnownTag::*;
        match self {
            Timestamp | SessionDuration | Counter => TagGroup::A,
            Vin | BatteryId | EncryptedVin => TagGroup::B,
            StateOfCharge => TagGroup::C,
            StateOfHealth => TagGroup::D,
            BatteryPackCurrent => TagGroup::E,
            BatteryPackVoltage => TagGroup::F,
            BatteryCellVoltageAll | BatteryCellVoltageMaxMin => TagGroup::G,
            BatteryTemperatureAll | BatteryTemperatureMaxMin => TagGroup::H,
        }
    }
}

/// Run cross-field validations.
///
/// Returns top-level diagnostics.
pub fn validate(fields: &[Field]) -> Vec<Diagnostic> {
    let mut diags: Vec<Diagnostic> = Vec::new();

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
    let groups: Vec<TagGroup> = tags.iter().map(|t| t.group()).collect();

    match groups.as_slice() {
        [
            TagGroup::A,
            TagGroup::B,
            TagGroup::C,
            TagGroup::D,
            TagGroup::E,
            TagGroup::F,
            TagGroup::G,
            TagGroup::H,
        ] => {
            if tags[6] == KnownTag::BatteryCellVoltageMaxMin
                && tags[7] == KnownTag::BatteryTemperatureAll
            {
                // Case 1 or Case 2 (Start/Stop)
                diags.push(Diagnostic::Info(
                    "Frame matches Case 1 or Case 2 (Start/Stop)".to_string(),
                ));
            } else {
                // Case 1
                diags.push(Diagnostic::Info("Frame matches Case 1".to_string()));
            }
        }
        [TagGroup::A, TagGroup::B, TagGroup::C] => diags.push(Diagnostic::Info(
            "Frame matches Case 2 (Periodic) or Case 3".to_string(),
        )),
        _ => diags.push(Diagnostic::FrameCompositionError(format!(
            "Frame does not match any allowed CASE composition per §3.3. Groups are {groups:?}",
        ))),
    }

    diags
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::{Diagnostic, Field, KnownTag, Tag, Value};

    /// Helper: construct a `Field`
    fn f(tag: KnownTag) -> Field {
        Field {
            tag: Tag::Known(tag),
            value: Value::None, // dummy
            unit: None,         // dummy
            range: 0..1,        // dummy
            diagnostics: vec![],
        }
    }

    fn has_validate_error_contains(diags: &[Diagnostic], needle: &str) -> bool {
        diags.iter().any(|d| match d {
            Diagnostic::FrameCompositionError(s) => s.contains(needle),
            _ => false,
        })
    }

    // -------------------------
    // CASE COMPOSITION TESTS
    // -------------------------

    #[test]
    fn case1_valid_all_groups_present() {
        let fields = vec![
            // A
            f(KnownTag::Timestamp),
            // B
            f(KnownTag::Vin),
            // C..F
            f(KnownTag::StateOfCharge),
            f(KnownTag::StateOfHealth),
            f(KnownTag::BatteryPackCurrent),
            f(KnownTag::BatteryPackVoltage),
            // G (All)
            f(KnownTag::BatteryCellVoltageAll),
            // H (Max/Min)
            f(KnownTag::BatteryTemperatureMaxMin),
        ];
        let diags = validate(&fields);
        assert_eq!(
            diags[0],
            Diagnostic::Info("Frame matches Case 1".to_string())
        );
        assert_eq!(diags.len(), 1);
    }

    #[test]
    fn case2_periodic_valid_minimal_abc_only() {
        let fields = vec![
            // A (use Counter)
            f(KnownTag::Counter),
            // B
            f(KnownTag::BatteryId),
            // C
            f(KnownTag::StateOfCharge),
        ];
        let diags = validate(&fields);
        assert_eq!(
            diags[0],
            Diagnostic::Info("Frame matches Case 2 (Periodic) or Case 3".to_string())
        );
        assert_eq!(diags.len(), 1);
    }

    #[test]
    fn case2_start_stop_valid_full_with_g_maxmin_h_all() {
        let fields = vec![
            // A
            f(KnownTag::SessionDuration),
            // B
            f(KnownTag::EncryptedVin),
            // C..F
            f(KnownTag::StateOfCharge),
            f(KnownTag::StateOfHealth),
            f(KnownTag::BatteryPackCurrent),
            f(KnownTag::BatteryPackVoltage),
            // G must be Max/Min
            f(KnownTag::BatteryCellVoltageMaxMin),
            // H must be All (length 1..255)
            f(KnownTag::BatteryTemperatureAll),
        ];
        let diags = validate(&fields);
        assert_eq!(
            diags[0],
            Diagnostic::Info("Frame matches Case 1 or Case 2 (Start/Stop)".to_string())
        );
        assert_eq!(diags.len(), 1);
    }

    #[test]
    fn no_case_error_when_missing_c_group() {
        // A,B present, C missing -> should produce a "no CASE" parse error.
        let fields = vec![f(KnownTag::Timestamp), f(KnownTag::Vin)];
        let diags = validate(&fields);
        assert!(
            has_validate_error_contains(&diags, "does not match any allowed CASE"),
            "Expected a CASE composition error, got: {:?}",
            diags
        );
    }

    #[test]
    fn group_order_error() {
        // A, C, B
        let fields = vec![
            // A (use Counter)
            f(KnownTag::Counter),
            // C
            f(KnownTag::StateOfCharge),
            // B
            f(KnownTag::BatteryId),
        ];
        let diags = validate(&fields);
        assert!(
            has_validate_error_contains(&diags, "does not match any allowed CASE"),
            "Expected a CASE composition error, got: {:?}",
            diags
        );
    }

    #[test]
    fn group_multiplicity_errors_for_a_b_g_h() {
        // Two items from Group A
        let mut fields = vec![
            f(KnownTag::Timestamp),
            f(KnownTag::Counter),
            // B (one)
            f(KnownTag::BatteryId),
            // C minimal to avoid CASE error overshadowing
            f(KnownTag::StateOfCharge),
        ];
        let diags = validate(&fields);
        assert!(
            has_validate_error_contains(&diags, "does not match any allowed CASE"),
            "Expected Group A multiplicity error, got: {:?}",
            diags
        );

        // Two items from Group B
        fields = vec![
            f(KnownTag::Counter),
            f(KnownTag::Vin),
            f(KnownTag::BatteryId),
            f(KnownTag::StateOfCharge),
        ];
        let diags = validate(&fields);
        assert!(
            has_validate_error_contains(&diags, "does not match any allowed CASE"),
            "Expected Group B multiplicity error, got: {:?}",
            diags
        );

        // Two items from Group G
        fields = vec![
            f(KnownTag::Counter),
            f(KnownTag::Vin),
            f(KnownTag::StateOfCharge),
            f(KnownTag::BatteryCellVoltageAll),
            f(KnownTag::BatteryCellVoltageMaxMin),
        ];
        let diags = validate(&fields);
        assert!(
            has_validate_error_contains(&diags, "does not match any allowed CASE"),
            "Expected Group G multiplicity error, got: {:?}",
            diags
        );

        // Two items from Group H
        fields = vec![
            f(KnownTag::Counter),
            f(KnownTag::BatteryId),
            f(KnownTag::StateOfCharge),
            f(KnownTag::BatteryTemperatureAll),
            f(KnownTag::BatteryTemperatureMaxMin),
        ];
        let diags = validate(&fields);
        assert!(
            has_validate_error_contains(&diags, "does not match any allowed CASE"),
            "Expected Group H multiplicity error, got: {:?}",
            diags
        );
    }
}
