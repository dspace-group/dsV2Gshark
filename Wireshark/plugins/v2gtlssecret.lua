--
-- Copyright 2024, dSPACE GmbH. All rights reserved.
--
-- this plugin allows live decryption of V2G messages using UDP disclosure messages
--
-- See license file (dsV2Gshark_LICENSE.txt)
--

p_v2gtlssecret = Proto("v2gtlssecret","V2G TLS secret")
local p_v2gtlssecret_info = {
    version = DS_V2GSHARK_VERSION,
    author = "dSPACE GmbH"
}
set_plugin_info(p_v2gtlssecret_info)

local min_wireshark_version = "3.5.0"

local f_cr  = ProtoField.string("v2gtlssecret.clientrandom","Client Random",base.ASCII)

local ef_io_error = ProtoExpert.new("tls_secret", "Failed to open keylog-file!", expert.group.DECRYPTION, expert.severity.WARN)
local ef_bad_version = ProtoExpert.new("tls_secret", "To use the TLS disclosure message to decrypt the application data Wireshark/Tshark version " .. tostring(min_wireshark_version) .. " or higher is required.", expert.group.DECRYPTION, expert.severity.WARN)

local tls_secret_path = os.getenv("TEMP") .. "\\wireshark_v2g_tls_keylogfile.txt"

local TLS_CR = 0

local payload_types = {
	[TLS_CR]                   = "TLS master secret disclosure message (client random)",
}

local client_random_string_hex = "434c49454e545f52414e444f4d" -- String "CLIENT_RANDOM" as hex
local frame_numbers = {} -- save the numbers of the frames including TLS secrets

p_v2gtlssecret.fields = {f_cr}
p_v2gtlssecret.experts = {ef_io_error, ef_bad_version}


-- verify tshark/wireshark version is compatible
local function check_version(required_version)
    major_req, minor_req, micro_req = required_version:match("(%d+)%.(%d+)%.(%d+)")
    major, minor, micro = get_version():match("(%d+)%.(%d+)%.(%d+)")

    if (tonumber(major) < tonumber(major_req)) or
         ((tonumber(major) == tonumber(major_req)) and (tonumber(minor) < tonumber(minor_req))) or
         ((tonumber(major) == tonumber(major_req)) and (tonumber(minor) == tonumber(minor_req)) and (tonumber(micro) < tonumber(micro_req))) then
        return false
    else
        return true
    end
end

-- init hex-to-char table
local hex_to_char = {}
for idx = 0, 255 do
    hex_to_char[("%02X"):format(idx)] = string.char(idx)
    hex_to_char[("%02x"):format(idx)] = string.char(idx)
end

local function byte_array_to_string(ByteArray)
    local str = ByteArray:bytes():tohex()
    return str:gsub("(..)", hex_to_char)
end

-- PDU dissection function
function p_v2gtlssecret.dissector(buf,pinfo,root)
    -- payload starts with 'CLIENT_RANDOM' (TLS 1.2)
    local p_type_num
    if buf:len() == 175 and tostring(buf(0,13)) == client_random_string_hex then
        p_type_num = TLS_CR
    else
        return 0
    end

    -- set info column
    pinfo.cols.info = payload_types[p_type_num]

    -- get string from byte array
    local tls_secret = byte_array_to_string(buf(0))

    -- add data to subtree
    local subtree = root:add(p_v2gtlssecret,buf(0))
    subtree:add(f_cr,buf(0)):set_text(tostring(tls_secret))

    if check_version(min_wireshark_version) == false then
        subtree:add_proto_expert_info(ef_bad_version)
        pinfo.cols.info = "[ERROR]" .. tostring(pinfo.cols.info)
        return
    end

    -- check if path to 'keylog_file' is not set, use default path defined in this script
    if get_preference("tls.keylog_file") == "" then
        set_preference("tls.keylog_file", tls_secret_path)
        apply_preferences()
    end

    -- write TLS secret only once and restart dissector once
    local already_visited = false
    for _,v in ipairs(frame_numbers) do
        if v == pinfo.number then
            already_visited = true
        end
    end

    -- write TLS secret to file
    if already_visited == false then
        -- check if the TLS secret is already in the file
        local file, _, _ = io.open(get_preference("tls.keylog_file"), "r")
        local secret_exists_in_file = false
        if file ~= nil then
            for line in file:lines() do
                local tls_secret_of_file = tostring(line)
                if tls_secret == tls_secret_of_file then
                    secret_exists_in_file = true
                    break
                end
            end
            file:close(file)
        end

        -- write TLS secret only once
        if secret_exists_in_file == false then
            local err_str
            file, err_str, _ = io.open(get_preference("tls.keylog_file"), "a")
            if file == nil then
                subtree:add_proto_expert_info(ef_io_error, err_str)
                pinfo.cols.info = "[ERROR] " .. tostring(pinfo.cols.info)
            else
                file:write(tls_secret .. "\n")
                table.insert(frame_numbers, pinfo.number) -- add frame number to table
                file:close(file)

                -- start TLS dissector again to decrypt application data
                if gui_enabled() then
                    redissect_packets()
                else
                    reload_lua_plugins()
                end
            end
        end -- end if 'secret_exists_in_file'
    end -- end if 'already_visited'
end -- end function 'p_v2gtlssecret.dissector'

-- initialization routine
function p_v2gtlssecret.init()
    -- register tls secret ports
    DissectorTable.get("udp.port"):add(p_v2gmsg.prefs["portrange_tlssecret"], p_v2gtlssecret)
end
