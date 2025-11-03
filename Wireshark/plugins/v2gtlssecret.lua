--
-- Copyright 2025, dSPACE GmbH. All rights reserved.
--
-- this plugin allows live decryption of V2G messages using UDP disclosure messages
--
-- See license file (dsV2Gshark_LICENSE.txt)
--
local v2gcommon = require("v2gcommon")

local MSG_SIZE_MIN = 175
local MSG_SIZE_MAX = 1800

local SECRET_LABELS = {
    CLIENT_RANDOM                     = "master secret",
    CLIENT_HANDSHAKE_TRAFFIC_SECRET   = "client handshake traffic secret",
    SERVER_HANDSHAKE_TRAFFIC_SECRET   = "server handshake traffic secret",
    EXPORTER_SECRET                   = "exporter secret",
    CLIENT_TRAFFIC_SECRET_            = "client traffic secret",
    SERVER_TRAFFIC_SECRET_            = "server traffic secret",
}


p_v2gtlssecret = Proto("v2gtlssecret", "V2G TLS secret")
local p_v2gtlssecret_info = {
    version = v2gcommon.DS_V2GSHARK_VERSION,
    author = "dSPACE GmbH",
    repository = "https://github.com/dspace-group/dsV2Gshark"
}
set_plugin_info(p_v2gtlssecret_info)

local min_wireshark_version = "3.5.0"

local f_cr = ProtoField.string("v2gtlssecret.clientrandom", "NSS Key Log", base.ASCII)

local ef_io_error =
    ProtoExpert.new("tls_secret.io_error", "Failed to open keylog-file!", expert.group.DECRYPTION, expert.severity.WARN)
local ef_decrypt_error =
    ProtoExpert.new("tls_secret.decrypt_error", "Decryption Error", expert.group.DECRYPTION, expert.severity.WARN)
local ef_bad_version =
    ProtoExpert.new(
    "tls_secret.bad_version",
    "To use the TLS disclosure message to decrypt the application data Wireshark/Tshark version " ..
        tostring(min_wireshark_version) .. " or higher is required.",
    expert.group.DECRYPTION,
    expert.severity.WARN
)

local tmpDir = os.getenv("TEMP")
if tmpDir == nil then
    tmpDir = "/tmp/"
end
local tls_secret_path = tmpDir .. "/wireshark_v2g_tls_keylogfile.txt"

local frame_numbers = {} -- save the numbers of the frames including TLS secrets

p_v2gtlssecret.fields = {f_cr}
p_v2gtlssecret.experts = {ef_io_error, ef_decrypt_error, ef_bad_version}

local function split_string(str)
    local parts = {}
    for part in str:gmatch "[^ \r\n]+" do
        table.insert(parts, part)
    end
    return parts
end

local function add_expert_info(message, tree, pinfo, expertinfo)
    local oldInfo = tostring(pinfo.cols.info)
    if string.len(oldInfo) < 9 or oldInfo:sub(0, 9) ~= "[WARNING]" then
        tree:add_proto_expert_info(expertinfo, message)
        pinfo.cols.info = "[WARNING] " .. oldInfo
    end
end

local v2gtlssecret_dissector = function(buf, pinfo, root)
    if buf:len() < MSG_SIZE_MIN or buf:len() > MSG_SIZE_MAX then
        return 0
    end

    local str = buf:raw()
    local tls_secret_list = {} -- stores secret string [1] and start position in payload [2]
    local info_strings = {}

    -- one UDP packet may contain several lines, check each line
    for startpos, line in str:gmatch "()([^\r\n\0]+)" do
        -- check if this is really a secret
        local match = line:match "^([%u_]+)%d* %x+ %x+$"
        if match == nil then
            return 0
        end

        local label = SECRET_LABELS[match]
        if label and line:len() > 100 and line:len() < 300 then
            table.insert(info_strings, label)
            table.insert(tls_secret_list, {line, startpos})
        end
    end

    if #tls_secret_list == 0 then
        return 0
    end

    local subtree = root:add(p_v2gtlssecret, buf(byte_offset))
    for _, v in ipairs(tls_secret_list) do
        subtree:add(f_cr, buf(v[2] - 1, v[1]:len()))
    end

    -- set info column
    pinfo.cols.info = "TLS disclosure message for " .. table.concat(info_strings, ", ")

    if v2gcommon.check_version(min_wireshark_version) == false then
        subtree:add_proto_expert_info(ef_bad_version)
        pinfo.cols.info = "[ERROR]" .. tostring(pinfo.cols.info)
        return buf:len()
    end

    -- check if path to 'keylog_file' is not set, use default path defined in this script
    if get_preference("tls.keylog_file") == "" then
        set_preference("tls.keylog_file", tls_secret_path)
        apply_preferences()
    end

    -- write TLS secret only once and restart dissector once
    local already_visited = false
    for _, v in ipairs(frame_numbers) do
        if v == pinfo.number then
            already_visited = true
        end
    end

    -- write TLS secret to file
    if already_visited == false then
        -- check if the TLS secrets are already in the file
        local file, _, _ = io.open(get_preference("tls.keylog_file"), "r")
        if file ~= nil then
            local file_content = file:read("*a")
            file:close(file)

            for idx = #tls_secret_list, 1, -1 do
                local to_be_removed = false
                local splitted_from_packet = split_string(tls_secret_list[idx][1])
                for line in file_content:gmatch "[^\r\n]+" do
                    local splitted_from_file = split_string(tostring(line))
                    if #splitted_from_packet == 3 and #splitted_from_file == 3 then
                        if
                            splitted_from_file[1] == splitted_from_packet[1] and
                                splitted_from_file[2] == splitted_from_packet[2]
                         then
                            if splitted_from_file[3] == splitted_from_packet[3] then
                                to_be_removed = true
                            else
                                add_expert_info(
                                    'CLIENT RANDOM part of secret is not unique! ("' .. splitted_from_packet[2] .. '")',
                                    subtree,
                                    pinfo,
                                    ef_decrypt_error
                                )
                            end
                        end
                    end
                end
                if to_be_removed then
                    table.remove(tls_secret_list, idx)
                end
                if #tls_secret_list == 0 then
                    break
                end
            end
        end

        -- write TLS secret only once
        if #tls_secret_list > 0 then
            local err_str
            file, err_str, _ = io.open(get_preference("tls.keylog_file"), "a")
            if file == nil then
                add_expert_info(err_str, subtree, pinfo, ef_io_error)
            else
                for _, tls_secret in ipairs(tls_secret_list) do
                    file:write(tls_secret[1] .. "\n")
                end
                table.insert(frame_numbers, pinfo.number) -- add frame number to table
                file:close(file)

                -- start TLS dissector again to decrypt application data
                if gui_enabled() then
                    redissect_packets()
                else
                    reload_lua_plugins()
                end
            end
        end
    end -- end if 'already_visited'
    return buf:len()
end

function p_v2gtlssecret.dissector(buf, pinfo, root)
    return v2gtlssecret_dissector(buf, pinfo, root)
end

-- initialization routine
function p_v2gtlssecret.init()
    frame_numbers = {}
end
p_v2gtlssecret:register_heuristic("udp", v2gtlssecret_dissector)
