//! Lua bindings for the decoder result.
//!
//! Expose a minimal Lua-facing API that accepts raw bytes,
//! returns a Lua table mirroring `DecodeResult`.

use crate::{DecodeResult, Diagnostic, Field, Value};
use mlua::prelude::*;
use mlua::{UserData, UserDataFields};

impl IntoLua for Value {
    fn into_lua(self, lua: &Lua) -> LuaResult<LuaValue> {
        match self {
            Self::U16(v) => v.into_lua(lua),
            Self::U32(v) => v.into_lua(lua),
            Self::Float(v) => v.into_lua(lua),
            // lua datatypes are only required for plotting, in other cases we use display_string
            Self::Str(_) | Self::FloatArray(_) | Self::Raw(_) | Self::None => Ok(mlua::Value::Nil),
        }
    }
}

impl UserData for Diagnostic {
    fn add_fields<F: UserDataFields<Self>>(fields: &mut F) {
        fields.add_field_method_get("severity", |_, this| {
            Ok(format!("{:?}", this.get_severity()))
        });
        fields.add_field_method_get("message", |_, this| Ok(this.to_string()));
    }
}

impl UserData for Field {
    fn add_fields<F: UserDataFields<Self>>(fields: &mut F) {
        fields.add_field_method_get("description", |_, this| Ok(this.tag.to_string()));
        fields.add_field_method_get("value", |lua, this| this.value.clone().into_lua(lua));
        fields.add_field_method_get("display_string", |_, this| Ok(this.to_display_string()));
        fields.add_field_method_get("byte_offset", |_, this| Ok(this.range.start));
        fields.add_field_method_get("byte_length", |_, this| Ok(this.range.len()));
        fields.add_field_method_get("diagnostics", |lua, this| {
            data_array_to_lua_table(lua, &this.diagnostics)
        });
    }
}

impl UserData for DecodeResult {
    fn add_fields<F: UserDataFields<Self>>(fields: &mut F) {
        fields.add_field_method_get("consumed_bytes", |_, this| Ok(this.consumed_bytes));
        fields.add_field_method_get("decode_outcome", |_, this| {
            Ok(format!("{:?}", this.decode_outcome()))
        });
        fields.add_field_method_get("fields", |lua, this| {
            data_array_to_lua_table(lua, &this.fields)
        });
        fields.add_field_method_get("diagnostics", |lua, this| {
            data_array_to_lua_table(lua, &this.diagnostics)
        });
    }
}

fn data_array_to_lua_table<T>(lua: &Lua, array: &[T]) -> LuaResult<LuaTable>
where
    T: UserData + Clone + 'static,
{
    let table = lua.create_table()?;
    for (i, item) in array.iter().enumerate() {
        table.set(i + 1, lua.create_userdata(item.clone())?)?;
    }
    Ok(table)
}
fn lua_table_to_vec(t: &mlua::Table) -> LuaResult<Vec<u8>> {
    let len = t.raw_len();
    let mut out = Vec::with_capacity(len);
    // Only consider array-part 1..len to avoid sparse table pitfalls
    for i in 1..=len {
        let b: u8 = t.get(i)?;
        out.push(b);
    }
    Ok(out)
}

/// Decode function exported to Lua
///
/// Example usage in lua console:
/// ```lua
/// lib = require("battery_data_exchange")
/// -- Example Data
/// -- TimeStamp  : 1752489450s
/// -- VIN        : KMHEM42APXA123456
/// -- SoC        : 74,0%
/// local bytes = {161,4,104,116,221,234,162,17,75,77,72,69,77,52,50,65,80,88,65,49,50,51,52,53,54,163,1,148}
/// local ok, val = pcall(lib.decode, bytes)
/// print(ok, val)
/// print(val.fields[2].value)
/// ```
pub fn decode(_: &Lua, bytes: LuaValue) -> LuaResult<DecodeResult> {
    let byte_vec = match bytes {
        LuaValue::String(s) => s.as_bytes().to_vec(),
        LuaValue::Table(t) => lua_table_to_vec(&t)?,
        other => {
            return Err(mlua::Error::FromLuaConversionError {
                from: other.type_name(),
                to: "byte array (string) or table of bytes".to_string(),
                message: Some(
                    "expected a Lua string of bytes or a sequential table of 0..255".into(),
                ),
            });
        }
    };

    Ok(crate::decode(&byte_vec))
}

#[mlua::lua_module]
fn battery_data_exchange(lua: &Lua) -> LuaResult<LuaTable> {
    let exports = lua.create_table()?;
    exports.set("decode", lua.create_function(decode)?)?;
    Ok(exports)
}
