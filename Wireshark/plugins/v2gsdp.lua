--
-- Copyright 2025, dSPACE GmbH. All rights reserved.
-- based on v2g-ws-dissectors by Amit Geynis
--
-- See license file (dsV2Gshark_LICENSE.txt)
--
local v2gcommon = require("v2gcommon")

p_sdpreq = Proto("v2gsdp-req", "V2G SECC Discovery Protocol Request")
p_sdpres = Proto("v2gsdp-res", "V2G SECC Discovery Protocol Response")
local p_v2gsdp_info = {
    version = v2gcommon.DS_V2GSHARK_VERSION,
    author = "dSPACE GmbH",
    repository = "https://github.com/dspace-group/dsV2Gshark"
}
set_plugin_info(p_v2gsdp_info)

-- V2G SDP Request
local f_req_sec = ProtoField.uint8("v2gsdp-req.security", "Security", base.HEX)
local f_req_tp = ProtoField.uint8("v2gsdp-req.transportprotocol", "Transport Protocol", base.HEX)
local f_req_emsp_ids = ProtoField.string("v2gsdp-req.emsp", "EMSP IDs")

local WITH_TLS = 0
local NO_TLS = 16

local sec_types = {
    [WITH_TLS] = "Secured with TLS", -- 0x00
    [NO_TLS] = "No transport layer security" -- 0x10
}

p_sdpreq.fields = {f_req_sec, f_req_tp, f_req_emsp_ids}

-- SDP Request dissection function
function p_sdpreq.dissector(buf, pinfo, root)
    pinfo.cols.protocol = "V2GMSG (SDP)"

    -- create subtree
    local subtree = root:add(p_sdpreq, buf(0))

    -- add protocol fields to subtree

    local emsp = pinfo.private["SDP_ESMP"]
    if emsp ~= nil and emsp == true then
        -- else: emsp list is empty
        -- Note: the SDP_RES_EMSP misses the fields 'Security' and 'Transport Protocol',
        -- since EMPS is only useful with PnC (TCP + TLS)
        if buf:len() > 0 then
            subtree:add(f_req_emsp_ids, buf(0))
        end
    else
        -- Security
        local sec_num = buf(0, 1):uint()
        local sec = subtree:add(f_req_sec, buf(0, 1))
        if sec_types[sec_num] ~= nil then
            sec:append_text(" (" .. sec_types[sec_num] .. ")")
            -- Concatenate the info of v2g
            pinfo.cols.info = tostring(pinfo.cols.info) .. ", " .. sec_types[sec_num]
        end

        -- Transport Protocol
        local tp = subtree:add(f_req_tp, buf(1, 1))
        if buf(1, 1):uint() == 0 then
            tp:append_text(" (TCP)")
        end
    end
end

-- V2G SDP Response
local f_res_ipv6 = ProtoField.ipv6("v2gsdp-res.ipv6", "SECC IP Address")
local f_res_port = ProtoField.uint16("v2gsdp-res.port", "SECC Port")
local f_res_sec = ProtoField.uint8("v2gsdp-res.security", "Security", base.HEX)
local f_res_tp = ProtoField.uint8("v2gsdp-res.transportprotocol", "Transport Protocol", base.HEX)
local f_res_emsp_ids = ProtoField.string("v2gsdp-res.emsp", "EMSP IDs")

p_sdpres.fields = {f_res_ipv6, f_res_port, f_res_sec, f_res_tp, f_res_emsp_ids}

-- SDP Response dissection function
function p_sdpres.dissector(buf, pinfo, root)
    pinfo.cols.protocol = "V2GMSG (SDP)"

    -- create subtree
    local subtree = root:add(p_sdpres, buf(0))

    -- add protocol fields to subtree
    -- SECC IPv6
    subtree:add(f_res_ipv6, buf(0, 16))
    -- SECC Port
    subtree:add(f_res_port, buf(16, 2))

    local emsp = pinfo.private["SDP_ESMP"]
    if emsp ~= nil and emsp == true and buf:len() > 18 then
        -- Note: the SDP_RES_EMSP misses the fields 'Security' and 'Transport Protocol',
        -- since EMPS is only useful with PnC (TCP + TLS)
        subtree:add(f_req_emsp_ids, buf(18))
    else
        -- Security
        local sec_num = buf(18, 1):uint()
        local sec = subtree:add(f_res_sec, buf(18, 1))
        if sec_types[sec_num] ~= nil then
            sec:append_text(" (" .. sec_types[sec_num] .. ")")
            -- Concatenate the info of v2g
            pinfo.cols.info = tostring(pinfo.cols.info) .. ", " .. sec_types[sec_num]
        end

        -- Transport Protocol
        local tp = subtree:add(f_res_tp, buf(19, 1))
        if buf(19, 1):uint() == 0 then
            tp:append_text(" (TCP)")
            if sec_num == NO_TLS then
                DissectorTable.get("tcp.port"):add(buf(16, 2):uint(), Dissector.get("v2gtp"))
            elseif sec_num == WITH_TLS then
                DissectorTable.get("tls.port"):add(buf(16, 2):uint(), Dissector.get("v2gtp"))
            end
        end
    end

    if selected_schema_at_packet_nr ~= nil then
        selected_schema_at_packet_nr[pinfo.number] = "urn:iso:15118:2:2010:AppProtocol"
    end
    return buf:len()
end
