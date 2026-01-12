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
local f_req_p2ps = ProtoField.uint16("v2gsdp-req.p2psppd", "P2PS/PPD", base.HEX)
local f_req_p2ps_flag_ppd_on_infrastructure = ProtoField.bool("v2gsdp-req.p2psppd.ppd_on_infrastructure", "PPD on Infrastructure", 16, nil, 0x0100, "PPD on Infrastructure")
local f_req_p2ps_flag_ppd_on_ev = ProtoField.bool("v2gsdp-req.p2psppd.ppd_on_ev", "PPD on EV", 16, nil, 0x0200, "PPD on EV")
local f_req_p2ps_flag_wpt_lf_on_infrastructure = ProtoField.bool("v2gsdp-req.p2psppd.wpt_lf_on_infrastructure", "WPT_LF on Infrastructure", 16, nil, 0x0400, "WPT_LF on Infrastructure")
local f_req_p2ps_flag_wpt_lf_on_ev = ProtoField.bool("v2gsdp-req.p2psppd.wpt_lf_on_ev", "WPT_LF on EV", 16, nil, 0x0800, "WPT_LF on EV")
local f_req_p2ps_flag_wpt_cam_on_ev = ProtoField.bool("v2gsdp-req.p2psppd.wpt_cam_on_ev", "WPT_Cam on EV", 16, nil, 0x1000, "WPT_Cam on EV")
local f_req_p2ps_flag_acd_u_infrared = ProtoField.bool("v2gsdp-req.p2psppd.acd_u_infrared", "ACD_U_Infrared", 16, nil, 0x2000, "ACD_U_Infrared")
local f_req_p2ps_flag_acd_directed_wlan = ProtoField.bool("v2gsdp-req.p2psppd.acd_directed_wlan", "ACD_directed_WLAN", 16, nil, 0x4000, "ACD_directed_WLAN")
local f_req_ct = ProtoField.uint8("v2gsdp-req.couplingtype", "Coupling Type", base.HEX)
local f_req_evid = ProtoField.string("v2gsdp-req.evid", "EVID", base.ASCII)
local f_req_evseid = ProtoField.string("v2gsdp-req.evseid", "EVSEID", base.ASCII)

local WITH_TLS = 0
local NO_TLS = 16

local sec_types = {
    [WITH_TLS] = "Secured with TLS", -- 0x00
    [NO_TLS] = "No transport layer security" -- 0x10
}

local coupling_types = {
    [0x00] = "Configuration according to IEC 61851-23-1 and EN 50696:2021, Annex A.2 (infrastructure mounted inverse pantograph, cross rail contacts)",
    [0x01] = "Configuration according to IEC 61851-23-1 and EN 50696:2021, Annex A.3 (infrastructure mounted inverse pantograph, in line contacts)",
    [0x02] = "Configuration according to IEC 61851-23-1 and EN 50696:2021, Annex A.4 (infrastructure mounted pantograph, contact dome)",
    [0x03] = "Configuration according to IEC 61851-23-1 and EN 50696:2021, Annex B EV mounted pantograph",
    [0x04] = "Configuration according to IEC 61851-23-1 and EN 50696:2021, Annex C, ACD mounted underneath the EV",
    [0x05] = "Configuration according to IEC 61851-23-1 and EN 50696:2021, Annex D, ACD mounted on infrastructure to the side or roof of EV",
    [0x10] = "WPT (IEC 61980)",
    [0x20] = "ACD-U (Manipulator on Infrastructure)",
    [0x21] = "ACD-U (Manipulator on EV)",
    [0x30] = "ACD-S",
    [0x40] = "Conductive manual",
    [0xff] = "n.a."
}

local diagstatus_types = {
    [0x00] = "ongoing",
    [0x01] = "finished with EVSEID",
    [0x02] = "finished without EVSEID",
    [0x10] = "Error - no SECC"
}

p_sdpreq.fields = {f_req_sec, f_req_tp, f_req_emsp_ids,
    f_req_p2ps,
    f_req_p2ps_flag_ppd_on_infrastructure,
    f_req_p2ps_flag_ppd_on_ev,
    f_req_p2ps_flag_wpt_lf_on_infrastructure,
    f_req_p2ps_flag_wpt_lf_on_ev,
    f_req_p2ps_flag_wpt_cam_on_ev,
    f_req_p2ps_flag_acd_u_infrared,
    f_req_p2ps_flag_acd_directed_wlan,
    f_req_ct,
    f_req_evid,
    f_req_evseid
}

-- SDP Request dissection function
function p_sdpreq.dissector(buf, pinfo, root)
    pinfo.cols.protocol = "V2GMSG (SDP)"

    -- create subtree
    local subtree = root:add(p_sdpreq, buf(0))

    -- add protocol fields to subtree

    local emsp = pinfo.private["SDP_EMSP"]
    if emsp ~= nil and emsp == "true" then
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

        local wireless = pinfo.private["SDP_WIRELESS"]
        if wireless ~= nil and wireless == "true" then
            local p2ps_num = buf(2,2):uint()
            local p2ps = subtree:add(f_req_p2ps, buf(2,2))
            local p2ps_flag_ppd_on_infrastructure = subtree:add(f_req_p2ps_flag_ppd_on_infrastructure, buf(2,2))
            local p2ps_flag_ppd_on_ev = subtree:add(f_req_p2ps_flag_ppd_on_ev, buf(2,2))
            local p2ps_flag_wpt_lf_on_infrastructure = subtree:add(f_req_p2ps_flag_wpt_lf_on_infrastructure, buf(2,2))
            local p2ps_flag_wpt_lf_on_ev = subtree:add(f_req_p2ps_flag_wpt_lf_on_ev, buf(2,2))
            local p2ps_flag_wpt_cam_on_ev = subtree:add(f_req_p2ps_flag_wpt_cam_on_ev, buf(2,2))
            local p2ps_flag_acd_u_infrared = subtree:add(f_req_p2ps_flag_acd_u_infrared, buf(2,2))
            local p2ps_flag_acd_directed_wlan = subtree:add(f_req_p2ps_flag_acd_directed_wlan, buf(2,2))
            local coupling_num = buf(4,1):uint()
            local coupling = subtree:add(f_req_ct, buf(4,1))
            if coupling_types[coupling_num] ~= nil then
                coupling:append_text(" (" .. coupling_types[coupling_num] .. ")")
            end

            local evidstr = buf(5,20):string()
            local evid = subtree:add(f_req_evid, buf(5,20))
            if (string.len(evidstr) > 0) then
                pinfo.cols.info = tostring(pinfo.cols.info) .. ", EVID: " .. evidstr
            end
            local evseidstr = buf(25,36):string()
            if (string.len(evseidstr) > 0) then
                pinfo.cols.info = tostring(pinfo.cols.info) .. ", EVSEID: " .. evseidstr
            end
            local evseid = subtree:add(f_req_evseid, buf(25,36))
        end
    end
end

-- V2G SDP Response
local f_res_ipv6 = ProtoField.ipv6("v2gsdp-res.ipv6", "SECC IP Address")
local f_res_port = ProtoField.uint16("v2gsdp-res.port", "SECC Port")
local f_res_sec = ProtoField.uint8("v2gsdp-res.security", "Security", base.HEX)
local f_res_tp = ProtoField.uint8("v2gsdp-res.transportprotocol", "Transport Protocol", base.HEX)
local f_res_emsp_ids = ProtoField.string("v2gsdp-res.emsp", "EMSP IDs")
local f_res_diagstatus = ProtoField.uint8("v2gsdp-res.diagstatus", "DiagStatus", base.HEX)
local f_res_couplingtype = ProtoField.uint8("v2gsdp-res.couplingtype", "Coupling Type", base.HEX)
local f_res_evseid = ProtoField.string("v2gsdp-res.evseid", "EVSEID", base.ASCII)

p_sdpres.fields = {f_res_ipv6, f_res_port, f_res_sec, f_res_tp, f_res_emsp_ids,
    f_res_diagstatus,
    f_res_couplingtype,
    f_res_evseid
}

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

    local emsp = pinfo.private["SDP_EMSP"]
    if emsp ~= nil and emsp == "true" and buf:len() > 18 then
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

        local wireless = pinfo.private["SDP_WIRELESS"]
        if wireless ~= nil and wireless == "true" then
            local diagstatus_num = buf(20,1):uint()
            local diagstatus = subtree:add(f_res_diagstatus, buf(20,1))
            if diagstatus_types[diagstatus_num] ~= nil then
                diagstatus:append_text(" (" .. diagstatus_types[diagstatus_num] .. ")")
            end

            local coupling_num = buf(21,1):uint()
            local coupling = subtree:add(f_res_couplingtype, buf(21,1))
            if coupling_types[coupling_num] ~= nil then
                coupling:append_text(" (" .. coupling_types[coupling_num] .. ")")
            end

            local evseidstr = buf(22,36):string()
            local evseid = subtree:add(f_res_evseid, buf(22,36))
            if (string.len(evseidstr) > 0) then
                pinfo.cols.info = tostring(pinfo.cols.info) .. ", EVSEID: " .. evseidstr
            end
        end
    end

    if selected_schema_at_packet_nr ~= nil then
        selected_schema_at_packet_nr[pinfo.number] = "urn:iso:15118:2:2010:AppProtocol"
    end
    return buf:len()
end
