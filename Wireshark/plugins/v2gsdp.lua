--
-- Copyright 2024, dSPACE GmbH. All rights reserved.
-- based on v2g-ws-dissectors by Amit Geynis
--
-- See license file (dsV2Gshark_LICENSE.txt)
--

p_sdpreq = Proto("v2gsdp-req","V2G SECC Discovery Protocol Request")
p_sdpres = Proto("v2gsdp-res","V2G SECC Discovery Protocol Response")
local p_v2gsdp_info = {
    version = DS_V2GSHARK_VERSION,
    author = "dSPACE GmbH",
}
set_plugin_info(p_v2gsdp_info)


-- V2G SDP Request
local f_sec = ProtoField.uint8("v2gsdp-req.security","Security",base.HEX)
local f_tp  = ProtoField.uint8("v2gsdp-req.transportprotocol","Transport Protocol",base.HEX)

local WITH_TLS = 0
local NO_TLS = 16

local sec_types = {
    [WITH_TLS]  = "Secured with TLS",              -- 0x00
    [NO_TLS]    = "No transport layer security",   -- 0x10
}

p_sdpreq.fields = {f_sec,f_tp}

-- SDP Request dissection function
function p_sdpreq.dissector(buf,pinfo,root)
    pinfo.cols.protocol = "V2GMSG (SDP)"

    -- create subtree
    subtree = root:add(p_sdpreq,buf(0))

    -- add protocol fields to subtree

    -- Security
    local sec_num = buf(0,1):uint()
    local sec = subtree:add(f_sec,buf(0,1))
    if sec_types[sec_num] ~= nil then
        sec:append_text(" (" .. sec_types[sec_num] ..")")
        -- Concatenate the info of v2g
        pinfo.cols.info = tostring(pinfo.cols.info) .. ", " .. sec_types[sec_num]
    end

    -- Transport Protocol
    local tp = subtree:add(f_tp,buf(1,1))
    if buf(1,1):uint() == 0 then
        tp:append_text(" (TCP)")
    end
end

-- V2G SDP Response
local f_ipv6   = ProtoField.ipv6("v2gsdp-res.ipv6","SECC IP Address")
local f_port = ProtoField.uint16("v2gsdp-res.port","SECC Port")
local f_res_sec = ProtoField.uint8("v2gsdp-res.security","Security",base.HEX)
local f_res_tp  = ProtoField.uint8("v2gsdp-res.transportprotocol","Transport Protocol",base.HEX)

p_sdpres.fields = {f_ipv6,f_port,f_res_sec,f_res_tp}

-- SDP Response dissection function
function p_sdpres.dissector(buf,pinfo,root)
    pinfo.cols.protocol = "V2GMSG (SDP)"

    -- create subtree
    local subtree = root:add(p_sdpres,buf(0))

    -- add protocol fields to subtree
    -- SECC IPv6
    subtree:add(f_ipv6,buf(0,16))
    -- SECC Port
    subtree:add(f_port,buf(16,2))

    -- Security
    local sec_num = buf(18,1):uint()
    local sec = subtree:add(f_res_sec,buf(18,1))
    if sec_types[sec_num] ~= nil then
        sec:append_text(" (" .. sec_types[sec_num] ..")")
        -- Concatenate the info of v2g
        pinfo.cols.info = tostring(pinfo.cols.info) .. ", " .. sec_types[sec_num]
    end

    -- Transport Protocol
    local tp = subtree:add(f_res_tp,buf(19,1))
    if buf(19,1):uint() == 0 then
        tp:append_text(" (TCP)")
        if sec_num == NO_TLS then
            DissectorTable.get("tcp.port"):add(buf(16,2):uint(),Dissector.get("v2gtp"))
        elseif sec_num == WITH_TLS then
            DissectorTable.get("tls.port"):add(buf(16,2):uint(),Dissector.get("v2gtp"))
        end
    end

    if selected_schema_at_packet_nr ~= nil then
        selected_schema_at_packet_nr[pinfo.number] = "urn:iso:15118:2:2010:AppProtocol"
    end
end
