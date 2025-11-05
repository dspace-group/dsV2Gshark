--
-- Copyright 2025, dSPACE GmbH. All rights reserved.
--
-- This dissector adds functionality to the standard HomePlug AV dissector
-- to allow displaying CP State indication packets
--
-- See license file (dsV2Gshark_LICENSE.txt)
--
local ETHERNET_LAYER_SIZE = 14
local VLAN_8021Q_SIZE = 4
local HPAV_HEADER_v10_SIZE = 6
local HPAV_HEADER_v11_SIZE = 8
local VLAN_ETHERNET_TYPE = 0x8100
local HPAV_ETHERNET_TYPE = 0x88e1

local SCS_DIAG_VERSION = 1

local v2gcommon = require("v2gcommon")

p_hpav_scs = Proto("homeplug-scs", "HomePlug AV protocol SCS Extension")
local p_hpav_scs_info = {
    version = v2gcommon.DS_V2GSHARK_VERSION,
    author = "dSPACE GmbH",
    repository = "https://github.com/dspace-group/dsV2Gshark"
}
set_plugin_info(p_hpav_scs_info)

local f_freq = ProtoField.int16("homeplug-scs.freq", "Frequency", base.DEC)
local f_dutycycle = ProtoField.float("homeplug-scs.dutycycle", "Duty cycle", base.DEC)
local f_voltage = ProtoField.float("homeplug-scs.voltage", "Voltage", base.DEC)
local f_cpstate = ProtoField.int8("homeplug-scs.cpstate", "CP State")
local f_acmax = ProtoField.string("homeplug-scs.ac_max", "AC max current")
local f_result = ProtoField.string("homeplug-scs.result", "Result")
local f_info = ProtoField.string("homeplug-scs.info", "Info")
local f_version = ProtoField.int8("homeplug-scs.version", "dSPACE SCS Diagnostic Message - Version")
local f_attenuation = ProtoField.string("homeplug-scs.attenuation", "Attenuation")
local f_attenuation_groups = ProtoField.int8("homeplug-scs.attenuation_groups", "Number of Groups", base.DEC)
local f_src_mac = ProtoField.ether("homeplug-scs.src_mac", "Source Mac")

p_hpav_scs.fields = {f_freq, f_dutycycle, f_voltage, f_cpstate, f_acmax, f_result, f_info, f_version, f_attenuation, f_attenuation_groups, f_src_mac}

local fe_eth_src = Field.new("eth.src")
local fe_hp_mmtype = Field.new("homeplug_av.mmhdr.mmtype")

local function extract_cp_info_spidcom(buf)
    local freq = buf(9, 2):le_int()
    local dutycycle = buf(11, 2):le_int() / 10
    local voltage = buf(13, 2):le_int() / 1000
    local result = buf(8, 1):int()
    return freq, dutycycle, voltage, result
end

local function extract_cp_info_iotecha(buf)
    local freq = buf(15, 2):le_int()
    local dutycycle = buf(14, 1):le_int()
    local voltage = buf(17, 2):le_int() / 1000
    return freq, dutycycle, voltage, -1
end

local function get_ac_max_current(dutycycle)
    if dutycycle < 8 then
        return -1
    elseif dutycycle < 10 then
        return 6
    elseif dutycycle < 85 then
        return dutycycle * 0.6
    elseif dutycycle < 96 then
        return (dutycycle - 64) * 2.5
    elseif dutycycle < 97 then
        return 80
    else
        return -1
    end
end

local function get_cp_state(freq, dutycycle, voltage)
    local StateA = 12
    local StateB = 9
    local StateC = 6
    local StateD = 3
    local StateEF = 0
    local Tolerance = 1

    if (dutycycle == 0 or dutycycle == 100) and freq > 0 then
        return "-"
    end

    local cp_state_out
    if voltage <= (StateA + Tolerance) and voltage >= (StateA - Tolerance) then
        cp_state_out = "A"
    elseif voltage <= (StateB + Tolerance) and voltage >= (StateB - Tolerance) then
        cp_state_out = "B"
    elseif voltage <= (StateC + Tolerance) and voltage >= (StateC - Tolerance) then
        cp_state_out = "C"
    elseif voltage <= (StateD + Tolerance) and voltage >= (StateD - Tolerance) then
        cp_state_out = "D"
    elseif voltage <= (StateEF + Tolerance) then
        return "E/F"
    else
        return "-"
    end

    local pwm_active = dutycycle > 0 and dutycycle < 100 and freq > 950 and freq < 1050
    if pwm_active then
        return cp_state_out .. "2"
    else
        return cp_state_out .. "1"
    end
end

local function cp_state_to_int(cp_state)
    --- used for I/O Graph plotting of CP State
    if cp_state == "A1" then
        return 1
    elseif cp_state == "A2" then
        return 2
    elseif cp_state == "B1" then
        return 3
    elseif cp_state == "B2" then
        return 4
    elseif cp_state == "C1" then
        return 5
    elseif cp_state == "C2" then
        return 6
    elseif cp_state == "D1" then
        return 7
    elseif cp_state == "D2" then
        return 8
    elseif cp_state == "E/F" then
        return -1
    end
    return 0
end

local function is_spidcom_cp_packet(buf)
    -- packet format by SPIDCOM Technologies SA
    if buf:len() < 8 then
        return false
    end
    local mac_mme_type = buf(1, 2):le_uint()
    local mme_vendor = buf(5, 3):uint()
    return mme_vendor == 0x0013D7 and mac_mme_type == 0xA10E
end

local function is_iotecha_cp_packet(buf)
    -- packet format by ST/IoTecha
    if buf:len() < 8 then
        return false
    end
    local mac_mme_type = buf(1, 2):le_uint()
    local mme_vendor = buf(5, 3):uint()
    return mme_vendor == 0x0080E1 and mac_mme_type == 0xA22E
end

local function is_qualcomm_atten_char(buf)
    -- Qualcomm VS_ATTENUATION_CHARACTERISTICS
    if buf:len() < 6 then
        return false
    end
    local mac_mme_type = buf(1, 2):le_uint()
    local mme_vendor = buf(3, 3):uint() -- note: hpav v1.0 does not have fragment infos
    return (mme_vendor == 0x00B052 or mme_vendor == 0x000000) and mac_mme_type == 0xA14E
end

local function is_dSPACE_scs_diag_packet(buf)
    -- dSPACE SCS Diag packet
    if buf:len() < 8 then
        return false
    end
    local mac_mme_type = buf(1, 2):le_uint()
    local mme_vendor = buf(5, 3):uint()
    return mme_vendor == 0x644D70 and mac_mme_type == 0x8002
end

local function needs_dissection(buf)
    return  is_iotecha_cp_packet(buf) or
            is_spidcom_cp_packet(buf) or
            is_qualcomm_atten_char(buf) or
            is_dSPACE_scs_diag_packet(buf)
end

local function dissect_cp_state_ind(buf, pinfo, root, freq, dutycycle, voltage, result)
    local subtree = root:add(p_hpav_scs, buf(0))

    local elem_frequency = subtree:add(f_freq, freq)
    elem_frequency:append_text("Hz")
    -- frequency bitmask: 001
    if result == 1 or result == 3 or result == 5 or result == 7 then
        elem_frequency:append_text(" (changed)")
    end

    local elem_dutycycle = subtree:add(f_dutycycle, dutycycle)
    elem_dutycycle:append_text("%")
    -- duty cycle bitmask: 010
    if result == 2 or result == 3 or result == 6 or result == 7 then
        elem_dutycycle:append_text(" (changed)")
    end

    local elem_voltage = subtree:add(f_voltage, voltage)
    elem_voltage:append_text("V")
    -- voltage bitmask: 100
    if result == 4 or result == 5 or result == 6 or result == 7 then
        elem_voltage:append_text(" (changed)")
    end

    local cp_state = get_cp_state(freq, dutycycle, voltage)
    subtree:add(f_cpstate, cp_state_to_int(cp_state)):set_text("CP State: " .. cp_state) -- store as int to allow plotting

    local ac_max_current = get_ac_max_current(dutycycle)
    if ac_max_current ~= -1 then
        subtree:add(f_acmax, ac_max_current):append_text("A")
        pinfo.cols.info = "CP State: " .. cp_state .. " [AC max current: " .. ac_max_current .. "A]"
    else
        pinfo.cols.info = "CP State: " .. cp_state
    end
    pinfo.cols.protocol = "HomePlug AV (Ext)"
    return buf:len()
end

local function dissect_qc_atten_char(buf, pinfo, root)
    local subtree = root:add(p_hpav_scs, buf(0))

    -- source MAC
    subtree:add(f_src_mac, buf(0,6))

    -- attenuation
    local sum_attenuation = 0
    local num_groups = buf(6, 1)
    subtree:add(f_attenuation_groups, num_groups)
    for i = 1, num_groups:uint(), 1 do
        local group_attenuation = buf(15 + i,1)
        sum_attenuation = sum_attenuation + group_attenuation:uint()
        subtree:add(f_attenuation, group_attenuation):set_text("Attenuation #" .. i .. ": " .. group_attenuation:uint() .. " dB")
    end

    local average = string.format("%.2f", sum_attenuation / num_groups:uint()):gsub(",", ".")
    pinfo.cols.info = "VS_ATTENUATION_CHARACTERISTICS, Groups: " .. num_groups:uint() .. ", Average: " .. average .. " dB"
    pinfo.cols.protocol = "HomePlug AV (Ext)"
    return buf:len()
end

local function dissect_dSPACE_scs_diag(buf_without_hpav, pinfo, root)
    local subtree = root:add(p_hpav_scs, buf_without_hpav(0))
    -- packet format: "dSPACE SCS Diag|dsV2Gshark|v<version>|<info>|<json>"
    local prefix, tool, version, info, json_str = string.match(buf_without_hpav():string(), "^([^|]+)|([^|]+)|v([0-9]+)|([^|]+)|({.+})$")
    if not (prefix and tool and info and json_str and version) or (prefix ~= "dSPACE SCS Diag") or (tool ~= "dsV2Gshark") then
        pinfo.cols.info = "Invalid SCS diagnostic packet"
        subtree:add(f_info, "The format of this packet is errorneous. Is dsV2Gshark up to date?")
        return 0
    end

    local scs_diag_tree = subtree:add(f_version, tonumber(version))

    if tonumber(version) > SCS_DIAG_VERSION  then
        pinfo.cols.info = "Unsupported SCS diagnostic packet. Please update dsV2Gshark!"
        subtree:add(f_info, "Please update your dSPACE V2Gshark Wireshark Plugin")
        return 0
    end

    local pos_json_start = string.len(prefix) + string.len(tool) + string.len(version) + string.len(info) + 5 -- 4 separators, 1 'v'
    local json_dissector = Dissector.get("json")
    if json_dissector ~= nil then
        local consumed = json_dissector:call(buf_without_hpav(pos_json_start):tvb(), pinfo, scs_diag_tree)
        pinfo.cols.info = info
        pinfo.cols.protocol = "HomePlug AV (SCS)"
        return consumed
    end
    return 0
end

local function dissect_hpav_scs(buf, pinfo, root)
    local consumed = 0
    -- check hpav message type
    local freq, dutycycle, voltage, result
    if is_spidcom_cp_packet(buf) then
        freq, dutycycle, voltage, result = extract_cp_info_spidcom(buf)
        consumed = dissect_cp_state_ind(buf, pinfo, root, freq, dutycycle, voltage, result)
    elseif is_iotecha_cp_packet(buf) then
        freq, dutycycle, voltage, result = extract_cp_info_iotecha(buf)
        consumed = dissect_cp_state_ind(buf, pinfo, root, freq, dutycycle, voltage, result)
    elseif is_dSPACE_scs_diag_packet(buf) then
        consumed = HPAV_HEADER_v11_SIZE + dissect_dSPACE_scs_diag(buf(HPAV_HEADER_v11_SIZE):tvb(), pinfo, root)
    elseif is_qualcomm_atten_char(buf) then
        consumed = HPAV_HEADER_v10_SIZE + dissect_qc_atten_char(buf(HPAV_HEADER_v10_SIZE):tvb(), pinfo, root)
    end

    return consumed
end

function p_hpav_scs.dissector(buf, pinfo, root)
    local processed_data = 0

    -- call default hpav dissector to add additional information
    local hpav_dissector = Dissector.get("homeplug-av")
    if hpav_dissector ~= nil then
        processed_data = hpav_dissector:call(buf, pinfo, root)
    end

    -- store MACs for 'Role' column
    local mac_src = fe_eth_src()
    local mmtype = fe_hp_mmtype()
    if mac_src and mmtype then
        if tostring(mmtype) == "0x6064" then  -- CM_SLAC_PARM.REQ
            _G.__evrole_macs_ev[tostring(mac_src)] = true
        elseif tostring(mmtype) == "0x6065" then  -- CM_SLAC_PARM.CNF
            _G.__evrole_macs_evse[tostring(mac_src)] = true
        end
    end

    return processed_data + dissect_hpav_scs(buf, pinfo, root)
end

local heuristic_hpav_dissector = function(buf, pinfo, root)
    -- heuristic dissector on ethernet level. We need to check
    -- whether this is a correct HPAV SCS packet or not. Only used in
    -- Wireshark < 4.0.0

    -- check size
    if buf:len() < ETHERNET_LAYER_SIZE + HPAV_HEADER_v10_SIZE then
        return 0
    end

    -- check eth type
    local vlan_id = nil
    local bytes_to_skip = 0
    local eth_type = buf(12, 2):uint()
    if eth_type == VLAN_ETHERNET_TYPE then -- handle VLAN layer
        bytes_to_skip = bytes_to_skip + VLAN_8021Q_SIZE
        vlan_id = buf(14, 2):uint()
        eth_type = buf(16, 2):uint()
    end
    if eth_type == HPAV_ETHERNET_TYPE then
        bytes_to_skip = bytes_to_skip + ETHERNET_LAYER_SIZE
    else
        return 0  -- not a HPAV packet
    end

    buf = buf(bytes_to_skip):tvb() -- skip eth header

    if not needs_dissection(buf) then
        -- this will trigger default dissection (eth + hpav)
        return 0
    end

    -- fake Eth layer
    eth_tree = root:add(
        "Ethernet II,",
        "Src: " .. tostring(pinfo.src) .. ", Dst: " .. tostring(pinfo.dst)
    )
    eth_tree:add("Destination:", tostring(pinfo.dst))
    eth_tree:add("Source:", tostring(pinfo.src))
    eth_tree:add("Type:", "Homeplug AV (0x88e1)")
    eth_tree:add("[ Note:", "Default Ethernet dissection skipped for this packet! For more details, update to Wireshark 4.x or deactivate homeplug-scs (Ctrl+Shift+E) ]")

    -- fake optional VLAN layer
    if vlan_id ~= nil then
        vlan_tree = root:add("802.1Q Virtual LAN, (...), ID:", vlan_id)
        vlan_tree:add("[ Note:", "Default VLAN dissection skipped for this packet! For more details, update to Wireshark 4.x or deactivate homeplug-scs (Ctrl+Shift+E) ]")
    end

    return dissect_hpav_scs(buf, pinfo, root)
end

if v2gcommon.check_version("4.0.0") then
    DissectorTable.get("ethertype"):add(0x88e1, p_hpav_scs)
else
    -- Use heuristic dissector for old wireshark versions.
    -- Otherwise, the HPAV dissector for non-scs packets is overridden.
    p_hpav_scs:register_heuristic("eth", heuristic_hpav_dissector)
end
