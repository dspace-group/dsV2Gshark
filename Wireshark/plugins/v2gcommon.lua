--
-- Copyright 2024, dSPACE GmbH. All rights reserved.
--
-- See license file (dsV2Gshark_LICENSE.txt)
--

-- do OS specific stuff, required to properly load v2g libs
local plugins_path  -- path to the plugins directory of this script
local lib_pattern
if package.config:sub(1, 1) == "\\" then
    -- WINDOWS
    plugins_path = debug.getinfo(1, "S").source:sub(2):match("(.*[/\\])") or "./"
    lib_pattern = "?.dll"
else
    -- UNIX
    plugins_path = debug.getinfo(1, "S").source:sub(2):match("(.*/)") or "./"
    lib_pattern = "?.so"
end
local wireshark_path = plugins_path .. "../"
if not string.find(plugins_path, package.path) then
    -- extend path (where to load .lua files)
    package.path = package.path .. ";" .. plugins_path .. "?.lua"
end
if not string.find(wireshark_path, package.cpath) then
    -- extend cpath (where to load .so files)
    package.cpath = package.cpath .. ";" .. wireshark_path .. lib_pattern .. ";" .. plugins_path .. lib_pattern
end

local v2gcommon = {}

v2gcommon.DS_V2GSHARK_VERSION = "1.3.1" -- DO NOT CHANGE

return v2gcommon
