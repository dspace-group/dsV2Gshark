--
-- Copyright 2024, dSPACE GmbH. All rights reserved.
--
-- this plugin adds support for V2G Messages for
-- - DIN 70121
-- - ISO 15118-2
-- - ISO 15118-20
--
-- powered by chargebyte cbexigen
--
-- See license file (dsV2Gshark_LICENSE.txt)
--

local v2gcommon = require("v2gcommon")

p_v2gmsg = Proto("v2gmsg", "V2G Message")
local p_v2gmsg_info = {
    version = v2gcommon.DS_V2GSHARK_VERSION,
    author = "dSPACE GmbH",
    description = "Dissector for V2G Messages (DIN 70121, ISO15118-2, ISO15118-20)"
}
set_plugin_info(p_v2gmsg_info)

-- Load C-Decoder
local v2g_decoder = require("v2gLuaDecoder")
v2g_decoder.initValidator()
local cert_info_extractor = require("v2gX509CertInfos")

-- Buffer for all decoded messages. Maps packetID -> xml string (or nil)
local xml_buffer = {}

local validation_buffer = {} -- maps packetID -> nil if valid, error string if invalid

-- Buffer to determine the schema
local last_schema_list_SAP_req = {} -- maps schema_ID (given by SAP-Req) to ProtocolNamespace
local decoded_error_code = {} -- maps (decoded) packet number to decode error code (0 = success)
local decoded_with_schema_namespace = {} -- maps (decoded) packet number to ProtocolNamespace that was used
local decoded_with_auto_schema_detection = {} -- maps (decoded) packet number to Boolean
selected_schema_at_packet_nr = {} -- maps packet number of SAP res to ProtocolNamespace. This var is also accessed in the v2gsdp dissector

-- Wireshark: ProtoFields init
local f_entry = ProtoField.string("v2gmsg.entry", " ")
local f_schema = ProtoField.string("v2gmsg.schema", "Schema", base.ASCII)
local f_exi = ProtoField.string("v2gmsg.exi", "EXI", base.ASCII)
local f_xml = ProtoField.string("v2gmsg.xml", "Decoded XML", base.ASCII)
local f_msg = ProtoField.string("v2gmsg.msgname", "Message", base.ASCII)
local f_validation = ProtoField.string("v2gmsg.validation", "Message Validation", base.ASCII)

p_v2gmsg.fields = {f_schema, f_exi, f_msg, f_entry, f_xml, f_validation}

local values_to_plot = {
    -- common
    "EVTargetVoltage",
    "EVTargetCurrent",
    "EVSEPresentVoltage",
    "EVSEPresentCurrent",
    -- DIN/ISO2:
    "EVRESSSOC",
    "EVRESSSOC",
    "EVMaximumVoltageLimit",
    "EVMaximumCurrentLimit",
    "EVSEMaximumVoltageLimit",
    "EVSEMaximumCurrentLimit",
    -- ISO20
    "EVPresentVoltage",
    "PresentSOC",
    "EVMaximumVoltage",
    "EVMinimumVoltage",
    "EVMaximumChargeCurrent",
    "EVSEMaximumVoltage",
    "EVSEMaximumChargeCurrent"
}
local f_plot_fields = {} -- maps value name to iograph-field
for k, value in pairs(values_to_plot) do
    f_plot_fields[value] = ProtoField.double("v2gmsg.xml.iograph." .. value, "I/O Graph Value")
    table.insert(p_v2gmsg.fields, f_plot_fields[value])
end

local MAX_FIELD_STR_LEN = 150

local ef_warning_generic = ProtoExpert.new("v2gmsg.warning", "V2G Warning", expert.group.PROTOCOL, expert.severity.WARN)
local ef_warning_validation =
    ProtoExpert.new(
    "v2gmsg.warning.validation",
    "V2G-Message validation failed",
    expert.group.PROTOCOL,
    expert.severity.WARN
)
local ef_error_generic = ProtoExpert.new("v2gmsg.error", "V2G Error", expert.group.UNDECODED, expert.severity.ERROR)
p_v2gmsg.experts = {ef_warning_generic, ef_warning_validation, ef_error_generic}

local schema_namespace_to_schema_ID = {}
schema_namespace_to_schema_ID["urn:iso:15118:2:2010:AppProtocol"] = "SAP"
schema_namespace_to_schema_ID["urn:din:70121:2012:MsgDef"] = "DIN"
schema_namespace_to_schema_ID["urn:iso:15118:2:2013:MsgDef"] = "ISO-2"
schema_namespace_to_schema_ID["urn:iso:std:iso:15118:-20:CommonMessages"] = "ISO-20 CM"
schema_namespace_to_schema_ID["urn:iso:std:iso:15118:-20:DC"] = "ISO-20 DC"
schema_namespace_to_schema_ID["urn:iso:std:iso:15118:-20:AC"] = "ISO-20 AC"
schema_namespace_to_schema_ID["urn:iso:std:iso:15118:-20:ACDP"] = "ISO-20 ACDP"
schema_namespace_to_schema_ID["urn:iso:std:iso:15118:-20:WPT"] = "ISO-20 WPT"

-- reset everything on init (e.g., if new pcap is opened on same instance)
function p_v2gmsg.init()
    xml_buffer = {}
    validation_buffer = {}
    last_schema_list_SAP_req = {}
    selected_schema_at_packet_nr = {}
    decoded_with_auto_schema_detection = {}
    decoded_with_schema_namespace = {}
    decoded_error_code = {}
end

local function decode_v2g_message(schema, exi_string, packet_number)
    local xml_out
    local xml_schema

    decoded_with_auto_schema_detection[packet_number] = false
    xml_out, xml_schema, errn = v2g_decoder.decodeV2GExi(schema, exi_string)
    if errn ~= 0 then -- on error use autoprotocol mode
        local xml_out_auto, xml_schema_auto
        xml_out_auto, xml_schema_auto, errn_auto = v2g_decoder.decodeV2GAuto(exi_string)
        if xml_out_auto ~= nil then
            decoded_with_auto_schema_detection[packet_number] = true
            xml_out = xml_out_auto
            xml_schema = xml_schema_auto
            errn = errn_auto
        end
    end

    decoded_with_schema_namespace[packet_number] = xml_schema
    decoded_error_code[packet_number] = errn
    return xml_out
end

local function add_expert_info(message, tree, pinfo, expertinfo)
    tree:add_proto_expert_info(expertinfo, message)
    local oldInfo = tostring(pinfo.cols.info)
    if oldInfo:sub(0, 3) ~= "[!]" then
        pinfo.cols.info = "[!] " .. oldInfo
    end
end

local function add_xml_table_to_tree(xml_table, tree_out, dissector_field, pinfo)
    local new_element
    if xml_table.value ~= "" then
        -- special handling for certificates
        if xml_table.name == "Certificate" or xml_table.name == "OEMProvisioningCert" then
            local cert_element = tree_out:add(dissector_field, xml_table.value)
            if string.len(xml_table.value) > 150 then -- cut too long strings
                cert_element:set_text(xml_table.name .. ": " .. xml_table.value:sub(0, 150) .. "(...)")
            else
                cert_element:set_text(xml_table.name .. ": " .. xml_table.value)
            end

            local valid,
                subj,
                issuer,
                version,
                serial,
                not_before,
                not_after,
                sig_algo,
                sig_value,
                pk_algo,
                spk_curve,
                spk_pub,
                v3_constraint,
                v3_constraint_CA,
                v3_key_usage,
                v3_key_usage_crit,
                v3_sk_ID,
                v3_sk_ID_crit = cert_info_extractor.getX509Infos(xml_table.value)
            if valid then
                cert_element:add(dissector_field, subj):set_text("Subject: " .. subj)
                cert_element:add(dissector_field, issuer):set_text("Issuer: " .. issuer)
                cert_element:add(dissector_field, version):set_text(
                    "Version: v" .. (version + 1) .. " (" .. version .. ")"
                ) -- certificate version is always +1 according to the standard
                cert_element:add(dissector_field, serial):set_text("Serial Number: 0x" .. serial)
                cert_element:add(dissector_field, not_before):set_text("Not Valid Before: " .. not_before)
                cert_element:add(dissector_field, not_after):set_text("Not Valid After: " .. not_after)
                cert_element:add(dissector_field, sig_algo):set_text("Signature Algorithm: " .. sig_algo)
                cert_element:add(dissector_field, sig_value):set_text("Signature Value: " .. sig_value)
                cert_element:add(dissector_field, pk_algo):set_text("Public Key Algorithm: " .. pk_algo)
                cert_element:add(dissector_field, spk_curve):set_text("Subject Public Key - Curve: " .. spk_curve)
                cert_element:add(dissector_field, spk_pub):set_text("Subject Public Key - RAW: " .. spk_pub)
                local x509_v3_element = cert_element:add(dissector_field, "X509v3")
                x509_v3_element:set_text("X509v3")
                x509_v3_element:add(dissector_field, v3_constraint):set_text("Basic Constraint: " .. v3_constraint)
                x509_v3_element:add(dissector_field, v3_constraint_CA):set_text(
                    "Basic Constraint CA: " .. v3_constraint_CA
                )
                x509_v3_element:add(dissector_field, v3_key_usage_crit):set_text("Key Usage: " .. v3_key_usage_crit)
                x509_v3_element:add(dissector_field, v3_key_usage):set_text("Key Usage: " .. v3_key_usage)
                x509_v3_element:add(dissector_field, v3_sk_ID_crit):set_text("Subject Key ID: " .. v3_sk_ID_crit)
                x509_v3_element:add(dissector_field, v3_sk_ID):set_text("Subject Key ID: " .. v3_sk_ID)
            else
                add_expert_info("INVALID CERTIFICATE", cert_element, pinfo, ef_warning_generic)
            end
        else
            new_element = tree_out:add(dissector_field, xml_table.value)
            new_element:set_text(xml_table.name .. ": " .. xml_table.value)
        end
    else
        new_element = tree_out:add(dissector_field, xml_table.name)
        new_element:set_text(xml_table.name)
    end

    -- physical value type (15118-2/DIN)
    local calc_value = nil
    if
        #xml_table.children == 3 and xml_table.children[1].name == "Multiplier" and xml_table.children[2].name == "Unit" and
            xml_table.children[3].name == "Value"
     then
        -- 15118-2 physical value type
        calc_value = tonumber(xml_table.children[3].value) * 10 ^ tonumber(xml_table.children[1].value)

        local unit = xml_table.children[2].value
        if calc_value > 1000 and (unit == "W" or unit == "Wh") then
            unit = "k" .. unit
            calc_value = calc_value / 1000
        end

        if unit == "s" then
            local h = math.floor(calc_value / 3600)
            local m = math.floor((calc_value - h * 3600) / 60)
            local s = calc_value % 60
            local appendix
            if
                pcall(
                    function()
                        appendix = string.format(": %02d:%02d:%02d [hh:mm:ss]", h, m, s)
                    end
                ) == false
             then
                appendix = ": ?"
                add_expert_info("INVALID FORMAT", new_element, pinfo, ef_warning_generic)
            end
            new_element:append_text(appendix)
        else
            local appendix
            if
                pcall(
                    function()
                        appendix = string.format(": %s%s", tostring(calc_value):gsub(",", "."), unit)
                    end
                ) == false
             then
                appendix = ": ?"
                add_expert_info("INVALID FORMAT", new_element, pinfo, ef_warning_generic)
            end
            new_element:append_text(appendix)
        end
    end

    -- rational number type (15118-20 + DIN without unnit)
    if
        #xml_table.children == 2 and
            (xml_table.children[1].name == "Exponent" or xml_table.children[1].name == "Multiplier") and
            xml_table.children[2].name == "Value"
     then
        calc_value = tonumber(xml_table.children[2].value) * 10 ^ tonumber(xml_table.children[1].value)
        new_element:append_text(": " .. tostring(calc_value):gsub(",", "."))
    end

    -- add I/O Graph fields
    for name, field in pairs(f_plot_fields) do
        if name == xml_table.name then
            if calc_value ~= nil then
                tree_out:add(field, calc_value).hidden = true
            else
                tree_out:add(field, xml_table.value).hidden = true
            end
            break
        end
    end

    if xml_table.attributes ~= "" then
        local att_element = new_element:add(dissector_field, xml_table.attributes)
        if string.len(xml_table.attributes) > MAX_FIELD_STR_LEN then -- cut too long attributes
            xml_table.attributes = xml_table.attributes:sub(0, MAX_FIELD_STR_LEN) .. "(...)"
        end
        att_element:set_text("[XML Attributes: " .. xml_table.attributes .. "]")
    end

    for _, c in ipairs(xml_table.children) do
        add_xml_table_to_tree(c, new_element, dissector_field, pinfo)
    end
end

local function parse_XML(xml_string)
    local xml_table = {name = "root", attributes = "", parent = nil, children = {}, value = ""}
    local current_element = xml_table

    for op, tag, attr, unary, val in string.gmatch(xml_string:gsub("\n", ""), "<(%/?)([%w_:-]+)(.-)(%/?)>([^<]*)") do
        if op == "/" then
            -- close the current element
            current_element = current_element.parent
        else
            -- cut prefix from element name
            local clean_name = tag
            local prefix_at = tag:find(":")
            if prefix_at ~= nil then
                clean_name = tag:sub(prefix_at + 1)
            end

            -- create new element
            local element = {name = clean_name, attributes = attr, parent = current_element, children = {}, value = val}
            current_element.children[#current_element.children + 1] = element
            if unary ~= "/" then
                -- Set the current element to the new element
                current_element = element
            end
        end
    end
    return xml_table.children[1]
end

local function process_SAP(data, packet_number)
    for sap_type in data:gmatch "<[^:]+:supportedAppProtocol([^ >]+)" do
        -- the SAP-req contains a list of protocols from which one is selected in the SAP-Res by the concrete ID
        if sap_type == "Req" then
            for protocol_entry in data:gmatch "<AppProtocol>(.-)</AppProtocol>" do
                local proto_namespace = protocol_entry:match "<ProtocolNamespace>(.-)</ProtocolNamespace>"
                local proto_ID = protocol_entry:match "<SchemaID>(.-)</SchemaID>"
                if proto_namespace ~= nil and proto_ID ~= nil then
                    last_schema_list_SAP_req[proto_ID] = proto_namespace
                -- else: the request is invalid
                end
            end
        elseif sap_type == "Res" and selected_schema_at_packet_nr[packet_number] == nil then
            local selected_ID = data:match "<SchemaID>(.-)</SchemaID>"
            if selected_ID ~= nil then
                selected_schema_at_packet_nr[packet_number] = last_schema_list_SAP_req[selected_ID]
                last_schema_list_SAP_req = {}
            -- else: the response is invalid
            end
        end
    end
end

local function get_message_name(data)
    local message_name = data:match "><(.-)[ >]" -- SAP / -20

    if message_name ~= nil then
        local prefix_at = message_name:find(":") -- cut prefix
        if prefix_at ~= nil then
            message_name = message_name:sub(prefix_at + 1)
        end
        if message_name == "V2G_Message" then
            message_name = data:match "Body><(.-)[/ >]" -- ISO-2/DIN
            prefix_at = message_name:find(":") -- cut prefix
            if prefix_at ~= nil then
                message_name = message_name:sub(prefix_at + 1)
            end
        end
    end

    return message_name
end

-- Dissection function
function p_v2gmsg.dissector(buf, pinfo, root)
    pinfo.cols.protocol = "V2GMSG"
    pinfo.cols.info = "V2GMESSAGE FAILURE: Unknown error occured" -- default 'INFO'-field

    local subtree = root:add(p_v2gmsg, buf(0)) -- highlights all remaining bytes

    local iso20_warn_tree = subtree:add(f_entry, ""):set_text("WARNING: Preliminary ISO 15118-20 support!")
    iso20_warn_tree.hidden = true -- only shown in ISO 15118-20 messages

    local metadata_tree = subtree:add(f_entry, ""):set_text("Metadata")

    local buf_as_hex = buf:bytes():tohex() -- exi as hex string
    metadata_tree:add(f_exi, buf_as_hex)

    if not pinfo.visited then
        -- this packet has not been decoded yet. Do it now and store the data inside xml_buffer

        -- retrieve schema info
        local schema_namespace = pinfo.private["Schema"]
        if schema_namespace == nil then -- if no schema is given, use the schema of the last SAP-messages
            schema_namespace = "urn:iso:15118:2:2010:AppProtocol" -- use SAP as default schema
            local last_closest = 0
            for k, v in pairs(selected_schema_at_packet_nr) do -- note: pairs are not sorted!
                if k < pinfo.number and last_closest < k then
                    schema_namespace = v
                    last_closest = k
                end
            end
        end

        -- decode exi
        local xml_data = decode_v2g_message(schema_namespace, buf_as_hex, pinfo.number)

        if xml_data == nil then
            -- decoding failed
            pinfo.cols.info = "V2GMSG - Decoding failed"
            add_expert_info(
                "Decoding failed! Is the schema and payload-type correct?",
                subtree,
                pinfo,
                ef_error_generic
            )
            return
        end

        local message_name = get_message_name(xml_data)
        if message_name ~= nil then
            -- we only have to set the info field here, everything else will be done on next dissector call
            pinfo.cols.info = message_name

            -- store decoded xml
            xml_buffer[pinfo.number] = xml_data

            -- resolve & store schema if this is an SAP-msg
            process_SAP(xml_data, pinfo.number)

            -- validate XML
            local decoded_schema = decoded_with_schema_namespace[pinfo.number]
            if decoded_schema ~= nil then
                local error_msg = validation_buffer[pinfo.number]
                if error_msg == nil then
                    -- msg not validated yet
                    local is_valid
                    is_valid, error_msg = v2g_decoder.validateXml(xml_data, decoded_schema)
                    if not is_valid then
                        validation_buffer[pinfo.number] = error_msg
                    end
                end
                if validation_buffer[pinfo.number] ~= nil then
                    add_expert_info(
                        "This message is invalid: " .. validation_buffer[pinfo.number]:sub(1, -2),
                        subtree,
                        pinfo,
                        ef_warning_validation
                    )
                end
            end
        end
    end

    if pinfo.visited or not gui_enabled() then -- in GUI mode we process the data on the second call for a better performance
        -- packet already decoded, get the xml data from the buffer
        local xml_data = xml_buffer[pinfo.number]

        if xml_data == nil then
            -- decoding failed
            pinfo.cols.info = "V2GMSG - Decoding failed"
            add_expert_info(
                "Decoding failed! Is the schema and payload-type correct?",
                subtree,
                pinfo,
                ef_error_generic
            )
            return
        end

        -- get the message name and write it to the info cols
        local message_name = get_message_name(xml_data)
        if message_name ~= nil then
            pinfo.cols.info = message_name
            metadata_tree:add(f_msg, message_name)

            if message_name == "supportedAppProtocolReq" or message_name == "supportedAppProtocolRes" then
                -- re-process SAP. This is required in case of a delayed capture start (i.e. SAP-req missed)
                if selected_schema_at_packet_nr[pinfo.number] == nil then
                    process_SAP(xml_data, pinfo.number)
                end
            end
        end

        -- add XML data
        ByteArray.tvb(ByteArray.new(xml_data, true), "XML Data")
        metadata_tree:add(f_xml, xml_data)

        local decoded_schema = decoded_with_schema_namespace[pinfo.number]
        if decoded_schema ~= nil then
            -- check decode error
            if decoded_error_code[pinfo.number] ~= 0 then
                add_expert_info(
                    "Decoding failed (" ..
                        decoded_error_code[pinfo.number] .. ")! The decoded message is partially or completely invalid!",
                    subtree,
                    pinfo,
                    ef_error_generic
                )
            end

            -- add validation error message if available
            if validation_buffer[pinfo.number] ~= nil then
                validation_tree =
                    metadata_tree:add(f_validation, "Failed! " .. validation_buffer[pinfo.number]:sub(1, -2))
                add_expert_info(
                    "This message is invalid: " .. validation_buffer[pinfo.number]:sub(1, -2),
                    validation_tree,
                    pinfo,
                    ef_warning_validation
                )
            else
                metadata_tree:add(f_validation, "Successful")
            end

            -- add schema_ID to protocol name
            local schema_ID = schema_namespace_to_schema_ID[decoded_schema]
            if decoded_with_auto_schema_detection[pinfo.number] then
                pinfo.cols.protocol = "V2GMSG (" .. schema_ID .. " ?)"
                metadata_tree:add(f_schema, "Automatically detected (" .. decoded_schema .. ")")
            elseif schema_ID ~= nil then
                pinfo.cols.protocol = "V2GMSG (" .. schema_ID .. ")"
                metadata_tree:add(f_schema, decoded_schema)
            end
            if schema_ID:sub(0, 6) == "ISO-20" then
                -- show warning for ISO 15118-20 messages. To be removed as soon as the decoder is finalized
                iso20_warn_tree.hidden = false
            end

            -- parse the xml data and add it to the tree
            add_xml_table_to_tree(parse_XML(xml_data), subtree, f_entry, pinfo)
        else
            iso20_warn_tree.hidden = false -- always show the warning on decode errors
            pinfo.cols.protocol = "V2GMSG (Decode Error)"
            metadata_tree:add(f_schema, "Decode Error")
            metadata_tree:add(f_validation, "Skipped (Decode Error)")
            add_expert_info(
                "Decoding failed! The decoded message is partially or completely invalid!",
                subtree,
                pinfo,
                ef_error_generic
            )
            add_xml_table_to_tree(parse_XML(xml_data), subtree, f_entry, pinfo)
        end
    end
end
