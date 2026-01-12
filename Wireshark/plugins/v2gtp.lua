--
-- Copyright 2025, dSPACE GmbH. All rights reserved.
-- based on v2g-ws-dissectors by Amit Geynis
--
-- See license file (dsV2Gshark_LICENSE.txt)
--
local v2gcommon = require("v2gcommon")

p_v2gtp = Proto("v2gtp", "V2G Transfer Protocol")
local p_v2gtp_info = {
    version = v2gcommon.DS_V2GSHARK_VERSION,
    author = "dSPACE GmbH",
    repository = "https://github.com/dspace-group/dsV2Gshark"
}
set_plugin_info(p_v2gtp_info)

-- Settings
p_v2gtp.prefs["infotext"] = Pref.statictext("dSPACE V2Gshark Wireshark Plugin")
p_v2gtp.prefs["additionalinfo"] = Pref.statictext("powered by chargebyte cbExiGen")
p_v2gtp.prefs["additionalinfo2"] = Pref.statictext("")
p_v2gtp.prefs["additionalinfo3"] = Pref.statictext("You may also check the menu under 'Tools' > 'dSPACE V2Gshark'.")
p_v2gtp.prefs["additionalinfo4"] = Pref.statictext("")
p_v2gtp.prefs["versioninfo"] = Pref.statictext("Version " .. v2gcommon.DS_V2GSHARK_VERSION)

local V2GTP_HDR_LENGTH = 8

local function get_v2gtp_length(buf, pktinfo, offset)
    return buf(offset + 4,4):uint() + V2GTP_HDR_LENGTH
end

local f_pv = ProtoField.uint8("v2gtp.protoversion", "Protocol Version", base.HEX)
local f_ipv = ProtoField.uint8("v2gtp.inverseprotoversion", "Inverse Protocol Version", base.HEX)
local f_pt = ProtoField.uint16("v2gtp.payloadtype", "Payload Type", base.HEX)
local f_len = ProtoField.uint32("v2gtp.length", "Payload Length", base.DEC)

local V2G = 32769
local I20_MAIN = 32770
local I20_AC = 32771
local I20_DC = 32772
local I20_ACDP = 32773
local I20_WPT = 32774
-- 32775 - 33024 reserved
local I20_SCHEDULE_RENEG = 33025 -- Note: not tested yet. ISO-20 support is expirimental in this version!
local I20_METER_CONF = 33026 -- Note: not tested yet. ISO-20 support is expirimental in this version!
local I20_ACDP_SYS_STATUS = 33027 -- Note: not tested yet. ISO-20 support is expirimental in this version!
local I20_PARKING_STATUS = 33028 -- Note: not tested yet. ISO-20 support is expirimental in this version!
-- 33029 - 36863 reserved
local SDP_REQ = 36864
local SDP_RES = 36865
local SDP_REQ_W = 36866
local SDP_RES_W = 36867
local SDP_REQ_EMSP = 36868
local SDP_RES_EMSP = 36869

local payload_types = {
    [V2G] = "ISO 15118-2/DIN/SAP", -- 0x8001
    [I20_MAIN] = "ISO 15118-20 Main Stream",
    [I20_AC] = "ISO 15118-20 Main AC",
    [I20_DC] = "ISO 15118-20 Main DC",
    [I20_ACDP] = "ISO 15118-20 ACDP",
    [I20_WPT] = "ISO 15118-20 WPT",
    [I20_SCHEDULE_RENEG] = "ISO 15118-20 Schedule Renegotiation", -- 0x8101
    [I20_METER_CONF] = "ISO 15118-20 Metering Confirmation",
    [I20_ACDP_SYS_STATUS] = "ISO 15118-20 ACDP System Status",
    [I20_PARKING_STATUS] = "ISO 15118-20 Parking Status",
    [SDP_REQ] = "SDP request message", -- 0x9000
    [SDP_RES] = "SDP response message", -- 0x9001
    [SDP_REQ_W] = "SDP request message wireless", -- 0x9002,
    [SDP_RES_W] = "SDP response message wireless", -- 0x9003,
    [SDP_REQ_EMSP] = "SDP EMSP request message",
    [SDP_RES_EMSP] = "SDP EMSP response message"
}

p_v2gtp.fields = {f_pv, f_ipv, f_pt, f_len}

-- PDU dissection function
local function v2gtp_pdu_dissect(buf, pinfo, root)
    if buf(V2GTP_HDR_LENGTH):len() ~= buf(4,4):uint() then return 0 end

    local p_type_num = buf(2, 2):uint()
    local prev_proto = tostring(pinfo.cols.protocol)

    pinfo.cols.protocol = "V2G TP"

    -- Delete irrelevant info from previous protocol
    if prev_proto ~= tostring(pinfo.cols.protocol) then
        pinfo.cols.info = ""
    end

    -- create subtree
    --
    local subtree = root:add(p_v2gtp, buf(0))

    -- add protocol fields to subtree

    -- Protocol Version
    subtree:add(f_pv, buf(0, 1))
    -- Inverse Protocol Version
    subtree:add(f_ipv, buf(1, 1))

    -- Payload type
    local p_type = subtree:add(f_pt, buf(2, 2))
    if payload_types[p_type_num] ~= nil then
        p_type:append_text(" (" .. payload_types[p_type_num] .. ")")
        -- Concatenate the info of v2g
        if tostring(pinfo.cols.info) ~= "" then
            pinfo.cols.info = tostring(pinfo.cols.info) .. ", " .. payload_types[p_type_num]
        else
            pinfo.cols.info = payload_types[p_type_num]
        end
    else
        p_type:append_text(" (Unknown)")
    end

    -- Length
    subtree:add(f_len, buf(4, 4))

    -- Wireless
    if p_type_num == SDP_REQ_W or p_type_num == SDP_RES_W then
        pinfo.private["SDP_WIRELESS"] = "true"
    else
        pinfo.private["SDP_WIRELESS"] = "false"
    end

    -- EMSP
    if p_type_num == SDP_REQ_EMSP or p_type_num == SDP_RES_EMSP then
        pinfo.private["SDP_EMSP"] = true
    else
        pinfo.private["SDP_EMSP"] = false
    end

    -- EXI / SDP payload --
    --
    if buf:len() > V2GTP_HDR_LENGTH then
        if p_type_num == SDP_REQ or p_type_num == SDP_REQ_W then
            return Dissector.get("v2gsdp-req"):call(buf(V2GTP_HDR_LENGTH):tvb(), pinfo, root)
        elseif p_type_num == SDP_RES or p_type_num == SDP_RES_W then
            return Dissector.get("v2gsdp-res"):call(buf(V2GTP_HDR_LENGTH):tvb(), pinfo, root)
        elseif p_type_num == V2G then
            -- do not set schema for 8001 payloads, s.t. it is derived from the SAP
            return Dissector.get("v2gmsg"):call(buf(V2GTP_HDR_LENGTH):tvb(), pinfo, root)
        elseif p_type_num == I20_MAIN then
            pinfo.private["Schema"] = "urn:iso:std:iso:15118:-20:CommonMessages"
            return Dissector.get("v2gmsg"):call(buf(V2GTP_HDR_LENGTH):tvb(), pinfo, root)
        elseif p_type_num == I20_AC then
            pinfo.private["Schema"] = "urn:iso:std:iso:15118:-20:AC"
            return Dissector.get("v2gmsg"):call(buf(V2GTP_HDR_LENGTH):tvb(), pinfo, root)
        elseif p_type_num == I20_DC then
            pinfo.private["Schema"] = "urn:iso:std:iso:15118:-20:DC"
            return Dissector.get("v2gmsg"):call(buf(V2GTP_HDR_LENGTH):tvb(), pinfo, root)
        elseif p_type_num == I20_ACDP then
            pinfo.private["Schema"] = "urn:iso:std:iso:15118:-20:ACDP"
            return Dissector.get("v2gmsg"):call(buf(V2GTP_HDR_LENGTH):tvb(), pinfo, root)
        elseif p_type_num == I20_WPT then
            pinfo.private["Schema"] = "urn:iso:std:iso:15118:-20:WPT"
            return Dissector.get("v2gmsg"):call(buf(V2GTP_HDR_LENGTH):tvb(), pinfo, root)
        elseif p_type_num == I20_SCHEDULE_RENEG then
            -- the schema must be derived from the SAP in this case. TODO: test this as soon as sidestreams are used
            return Dissector.get("v2gmsg"):call(buf(V2GTP_HDR_LENGTH):tvb(), pinfo, root)
        elseif p_type_num == I20_METER_CONF then
            pinfo.private["Schema"] = "urn:iso:std:iso:15118:-20:CommonMessages" -- Meter Conf Sidestream uses common messages only
            return Dissector.get("v2gmsg"):call(buf(V2GTP_HDR_LENGTH):tvb(), pinfo, root)
        elseif p_type_num == I20_ACDP_SYS_STATUS then
            pinfo.private["Schema"] = "urn:iso:std:iso:15118:-20:ACDP"
            return Dissector.get("v2gmsg"):call(buf(V2GTP_HDR_LENGTH):tvb(), pinfo, root)
        elseif p_type_num == I20_PARKING_STATUS then
            pinfo.private["Schema"] = "urn:iso:std:iso:15118:-20:CommonMessages"
            return Dissector.get("v2gmsg"):call(buf(V2GTP_HDR_LENGTH):tvb(), pinfo, root)
        else
            pinfo.cols.info = "Unknown or unsupported V2GTP message. Type 0x" .. buf(2, 2)
            return 0
        end
    end
end


local v2gtp_dissector = function(buf, pinfo, root)
    -- plausibility checks
    if buf:len() < V2GTP_HDR_LENGTH then return 0 end
    if tostring(buf(0, 2)) ~= "01fe" then return 0 end

    -- if above TCP we need to assemble the PDU
    if pinfo.port_type == 2 then
        dissect_tcp_pdus(buf, root, V2GTP_HDR_LENGTH, get_v2gtp_length, v2gtp_pdu_dissect)
    else
        return v2gtp_pdu_dissect(buf, pinfo, root)
    end
end

function p_v2gtp.dissector(buf, pinfo, root)
    return v2gtp_dissector(buf, pinfo, root)
end

-- initialization routine
function p_v2gtp.init()
    DissectorTable.get("udp.port"):add(15118, p_v2gtp) -- register for SDP
end
-- register outside init() as heuristic dissector to handle missing SDP messages
p_v2gtp:register_heuristic("tcp", v2gtp_dissector)
p_v2gtp:register_heuristic("tls", v2gtp_dissector)
