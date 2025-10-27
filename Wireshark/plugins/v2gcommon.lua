--
-- Copyright 2025, dSPACE GmbH. All rights reserved.
--
-- See license file (dsV2Gshark_LICENSE.txt)
--
local v2gcommon = {}

function v2gcommon.is_windows()
    return package.config:sub(1, 1) == "\\"
end

function v2gcommon.get_plugins_file_path()
    -- returns the full path to the directory where this plugin is located,
    -- i.e. the personal plugin directory or the global plugin directory
    if v2gcommon.is_windows() then
        return debug.getinfo(1, "S").source:sub(2):match("(.*[/\\])") or "./"
    else
        return debug.getinfo(1, "S").source:sub(2):match("(.*/)") or "./"
    end
end

function v2gcommon.load_v2gLib()
    -- returns v2gLib object or nil if not found
    local library_module = "luaopen_v2gLib"
    local library_base_file = "v2gLib"
    local library_file
    if _VERSION == "Lua 5.1" then
        library_file = library_base_file .. "_51"
    elseif _VERSION == "Lua 5.2" then
        library_file = library_base_file .. "_52"
    elseif _VERSION == "Lua 5.3" then
        library_file = library_base_file .. "_53"
    elseif _VERSION == "Lua 5.4" then
        library_file = library_base_file .. "_54"
    end
    if v2gcommon.is_windows() == false then
        library_file = library_file .. ".so"
        library_base_file = library_base_file .. ".so"
    end

    local plugins_path = v2gcommon.get_plugins_file_path()
    local lib_path_candidates = {
        library_file,
        plugins_path .. library_file,
        plugins_path .. "../" .. library_file,
        library_base_file,
        plugins_path .. library_base_file,
        plugins_path .. "../" .. library_base_file
    }

    local v2g_lib
    for _, path in ipairs(lib_path_candidates) do
        v2g_lib = package.loadlib(path, library_module)
        if v2g_lib then break end
    end
    if not v2g_lib then
        print("Could not find V2G Library!")
        return nil
    else
        v2g_lib = v2g_lib()
        v2g_lib.initValidator()
        return v2g_lib
    end
end

-- verify tshark/wireshark version is compatible
function v2gcommon.check_version(required_version)
    local major_req, minor_req, micro_req = required_version:match("(%d+)%.(%d+)%.(%d+)")
    local major, minor, micro = get_version():match("(%d+)%.(%d+)%.(%d+)")

    if
        (tonumber(major) < tonumber(major_req)) or
            ((tonumber(major) == tonumber(major_req)) and (tonumber(minor) < tonumber(minor_req))) or
            ((tonumber(major) == tonumber(major_req)) and (tonumber(minor) == tonumber(minor_req)) and
                (tonumber(micro) < tonumber(micro_req)))
     then
        return false
    else
        return true
    end
end

function v2gcommon.add_expert_info(message, tree, pinfo, expertinfo)
    tree:add_proto_expert_info(expertinfo, message)
    local oldInfo = tostring(pinfo.cols.info)
    if oldInfo:sub(1, 3) ~= "[!]" then
        pinfo.cols.info = "[!] " .. oldInfo
    end
end

v2gcommon.DS_V2GSHARK_VERSION = "1.5.1" -- DO NOT CHANGE

-- extend path (where to load .lua files)
if not string.find(v2gcommon.get_plugins_file_path(), package.path) then
    package.path = package.path .. ";" .. v2gcommon.get_plugins_file_path() .. "?.lua"
end

return v2gcommon
