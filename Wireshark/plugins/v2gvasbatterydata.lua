local v2gcommon = require("v2gcommon")

p_vasbatterydata = Proto("v2gvasbatterydata", "V2G Battery Data Exchange Protocol")

local p_vasbatterydata_info = {
    version = v2gcommon.DS_V2GSHARK_VERSION,
    author = "dSPACE GmbH",
    repository = "https://github.com/dspace-group/dsV2Gshark"
}
set_plugin_info(p_vasbatterydata_info)

local min_wireshark_version = "4.4.0" -- battery data lib is built for Lua 5.4

-- Diagnostics
local f_diag = ProtoField.string("v2gvasbatterydata.diag", "Diagnostics")
local f_diag_bytes = ProtoField.string("v2gvasbatterydata.diag.bytes", "Raw Bytes")
local f_diag_consumed_bytes = ProtoField.uint32("v2gvasbatterydata.diag_consumed_bytes", "Decoded Bytes", base.DEC)
local f_diag_decode_result = ProtoField.string("v2gvasbatterydata.diag_decode_result", "Decode Result")
local f_diag_msg = ProtoField.string("v2gvasbatterydata.diag.message", "Diagnostic Message")

-- Per-field info
local f_field = ProtoField.string("v2gvasbatterydata.field", "Field")
local f_field_diag_msg = ProtoField.string("v2gvasbatterydata.field.diag.message", "Field Diagnostic Message")

-- store numerical field values for io-graph
local f_fields_value = {
    -- (Group A)
    ["Timestamp"] = ProtoField.uint32("v2gvasbatterydata.field.value.timestamp", "Timestamp Numerical Value", base.DEC),
    ["Session Duration"] = ProtoField.uint32(
        "v2gvasbatterydata.field.value.sessionduration",
        "Session Duration Numerical Value",
        base.DEC
    ),
    ["Counter"] = ProtoField.uint16("v2gvasbatterydata.field.value.counter", "Counter Numerical Value", base.DEC),
    -- (Group C)
    ["SoC"] = ProtoField.float("v2gvasbatterydata.field.value.soc", "SoC Numerical Value", base.DEC),
    -- (Group D)
    ["SoH"] = ProtoField.float("v2gvasbatterydata.field.value.soh", "SoH Numerical Value", base.DEC),
    -- (Group E)
    ["Battery Pack Current"] = ProtoField.float(
        "v2gvasbatterydata.field.value.batpackcurrent",
        "Battery Pack Current Numerical Value",
        base.DEC
    ),
    -- (Group F)
    ["Battery Pack Voltage"] = ProtoField.float(
        "v2gvasbatterydata.field.value.batpackvoltage",
        "Battery Pack Voltage Numerical Value",
        base.DEC
    )
}

p_vasbatterydata.fields = {
    f_diag,
    f_diag_bytes,
    f_diag_consumed_bytes,
    f_diag_decode_result,
    f_diag_msg,
    f_field,
    f_field_diag_msg
}
for _, value in pairs(f_fields_value) do
    table.insert(p_vasbatterydata.fields, value)
end

local ef_error_plugin =
    ProtoExpert.new("v2gvasbatterydata.error.plugin", "V2G Error", expert.group.PROTOCOL, expert.severity.ERROR)
local ef_warning_decoder =
    ProtoExpert.new("v2gvasbatterydata.warning.decoder", "V2G Warning", expert.group.PROTOCOL, expert.severity.WARN)
local ef_warning_diagnostic =
    ProtoExpert.new("v2gvasbatterydata.warning.diag", "V2G Warning", expert.group.PROTOCOL, expert.severity.WARN)
local ef_error_diagnostic =
    ProtoExpert.new("v2gvasbatterydata.error.diag", "V2G Error", expert.group.PROTOCOL, expert.severity.ERROR)
p_vasbatterydata.experts = {ef_error_plugin, ef_warning_decoder, ef_error_diagnostic, ef_warning_diagnostic}

local function load_decoder_lib()
    local so_path = v2gcommon.get_plugins_file_path() .. "../battery_data_exchange"
    local ok_loader, loader = pcall(package.loadlib, so_path, "luaopen_battery_data_exchange")
    if not ok_loader or not loader then
        return nil, ("Failed to load 'battery_data_exchange' from '%s'"):format(so_path)
    end
    local ok_lib, lib = pcall(loader)
    if not ok_lib or type(lib) ~= "table" then
        return nil, "Loaded module initializer returned no library table"
    end
    if type(lib.decode) ~= "function" then
        return nil, "Library does not export a 'decode' function"
    end
    return lib, nil
end

local function add_diagnostic_messages(tree, pinfo, list, f_diag_type)
    if type(list) ~= "table" then
        return
    end
    for i, d in ipairs(list) do
        local severity = tostring(d.severity or "")
        local base_msg = ("Diagnostic Message #%d (%s): "):format(i, severity)
        local msg = (d and d.message and tostring(d.message) or "")
        local node = tree:add(f_diag_type, msg)
        node:set_text(base_msg .. msg)
        if severity == "Warning" then
            v2gcommon.add_expert_info(msg, node, pinfo, ef_warning_diagnostic)
        elseif severity == "Error" then
            v2gcommon.add_expert_info(msg, node, pinfo, ef_error_diagnostic)
        end
    end
end

-- If we are in sniffing mode, we may miss the ServiceDetailRes.
-- Therefore, we use an additional heuristic dissector and check specific bytes
local heuristic_hpav_dissector = function(buf, pinfo, root)
    local buflen = buf:len()
    -- We check the first 3 fields (A, B, C) to match the structure.
    -- These are required in all 3 CASEs.
    if buflen < 10 then -- valid packet has at least 10 bytes
        return 0
    end

    local consumed_bytes = 0
    -- Group A (4-6 bytes)
    local tagA = buf(consumed_bytes, 1):uint()
    local lenA = buf(consumed_bytes + 1, 1):uint()
    if (tagA == 0xA1 or tagA == 0xB1) and lenA == 0x04 then
        consumed_bytes = consumed_bytes + 6
    elseif tagA == 0xC1 and lenA == 0x02 then
        consumed_bytes = consumed_bytes + 4
    else
        return 0
    end

    -- Group B (3-259 bytes)
    if buflen < consumed_bytes + 3 then
        return 0
    end
    local tagB = buf(consumed_bytes, 1):uint()
    local lenB = buf(consumed_bytes + 1, 1):uint()
    if tagB == 0xA2 or tagB == 0xB2 or tagB == 0xC2 then
        if tagB == 0xA2 and lenB ~= 0x11 then
            return 0 -- VIN has fixed 0x11 length
        end
        consumed_bytes = consumed_bytes + 2 + lenB
    else
        return 0
    end

    -- Group C (3 bytes)
    if buflen < consumed_bytes + 3 then
        return 0
    end
    local tagC = buf(consumed_bytes, 1):uint()
    local lenC = buf(consumed_bytes + 1, 1):uint()
    if tagC == 0xA3 and lenC == 0x01 then
        DissectorTable.get("tcp.port"):add(pinfo.dst_port, p_vasbatterydata)
        return p_vasbatterydata.dissector(buf, pinfo, root)
    end

    return 0
end
p_vasbatterydata:register_heuristic("tcp", heuristic_hpav_dissector)

local function make_warning_dissector(warning_text)
    return function(buf, pinfo, root)
        pinfo.cols.protocol = "V2GBatteryData"
        pinfo.cols.info = warning_text
        local ti = root:add(p_vasbatterydata, buf(0))
        v2gcommon.add_expert_info(warning_text, ti, pinfo, ef_error_plugin)
        return 0
    end
end

if v2gcommon.check_version(min_wireshark_version) == false then
    p_vasbatterydata.dissector =
        make_warning_dissector(("Wireshark >= %s required to decode V2G Battery Data"):format(min_wireshark_version))
    return
end

local battery_data_lib, load_err = load_decoder_lib()
if not battery_data_lib then
    p_vasbatterydata.dissector = make_warning_dissector("Battery Data decoder not available: " .. tostring(load_err))
    return
end

function p_vasbatterydata.dissector(buf, pinfo, root)
    local buflen = buf:len()

    local ok, decoded = pcall(battery_data_lib.decode, buf:raw())
    if not ok then
        local ti = root:add(p_vasbatterydata, buf(0))
        v2gcommon.add_expert_info(
            "Decoding failed" .. (ok and "" or (": " .. tostring(decoded))),
            ti,
            pinfo,
            ef_error_plugin
        )
        return 0
    end

    local consumed = tonumber(decoded.consumed_bytes) or buflen
    if consumed <= 0 then
        -- most likely not to be a battery data packet
        return 0
    end
    if consumed < 0 or consumed > buflen then
        consumed = buflen
    end
    pinfo.cols.protocol = "V2GBatteryData"

    local subtree = root:add(p_vasbatterydata, buf(0, consumed))
    pinfo.cols.info = "Battery Data"

    -- Diagnostics
    local diagtree = subtree:add(f_diag, "")
    diagtree:set_text("[Diagnostics]")
    diagtree:add(f_diag_bytes, "0x" .. buf(0, consumed))
    diagtree:add(f_diag_consumed_bytes, consumed)
    diagtree:add(f_diag_decode_result, tostring(decoded.decode_outcome or "unknown"))
    add_diagnostic_messages(diagtree, pinfo, decoded.diagnostics, f_diag_msg)

    -- Fields
    if type(decoded.fields) == "table" then
        pinfo.cols.info = tostring(pinfo.cols.info) .. " ["
        for i, fld in ipairs(decoded.fields) do
            local off = tonumber(fld.byte_offset) or 0
            local flen = tonumber(fld.byte_length) or 0

            -- Bounds safety
            if off < 0 then
                off = 0
            end
            if flen < 0 then
                flen = 0
            end
            if off + flen > buflen then
                flen = math.max(0, buflen - off)
            end

            local desc = fld.description and tostring(fld.description) or ("Field #" .. i)
            local bytes_range = buf(off, flen)

            local field_info_str = ("%s: %s"):format(desc, tostring(fld.display_string))
            if i > 1 then
                pinfo.cols.info = tostring(pinfo.cols.info) .. ", "
            end
            pinfo.cols.info = tostring(pinfo.cols.info) .. field_info_str

            local field_node = subtree:add(f_field, bytes_range)
            field_node:set_text(field_info_str)
            if fld.value ~= nil and type(fld.value) == "number" then
                field_node:add(f_fields_value[desc], fld.value).hidden = true
            end

            -- Per-field diagnostics
            add_diagnostic_messages(field_node, pinfo, fld.diagnostics, f_field_diag_msg)
        end
        pinfo.cols.info = tostring(pinfo.cols.info) .. "]"
    end

    return consumed
end
