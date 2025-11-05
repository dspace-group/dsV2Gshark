--
-- Copyright 2025, dSPACE GmbH. All rights reserved.
--
-- Adds Menu at "Tools" -> "dSPACE V2Gshark"
--
-- See license file (dsV2Gshark_LICENSE.txt)
--

local v2gcommon = require("v2gcommon")

local info = {
    version = v2gcommon.DS_V2GSHARK_VERSION,
    author = "dSPACE GmbH",
    description = "Adds dsV2Gshark menu entry",
    repository = "https://github.com/dspace-group/dsV2Gshark"
}
set_plugin_info(info)

-- Only useful with the GUI (Wireshark, not tshark)
if not gui_enabled() then
    return
end

local BASE_DIR = v2gcommon.get_plugins_file_path() .. ".." .. package.config:sub(1, 1) .. "dsV2Gshark_examples"

local function list_pcaps()
    local files = {}
    local ok, iter = pcall(Dir.open, BASE_DIR)
    if not ok or not iter then
        return files
    end
    for name in iter do
        local n = name:lower()
        if n:match("%.pcap$") or n:match("%.pcapng$") then
            table.insert(files, name)
        end
    end
    table.sort(files)
    return files
end

register_menu(
    "dSPACE V2Gshark/Example V2G Traces/ [ Open Examples Folder ]", -- leading space for menu order
    function()
        local ok, exists = pcall(Dir.exists, BASE_DIR)
        if ok and exists == true then
            browser_open_data_file(BASE_DIR)
        else
            report_failure(("Examples folder was not found or is not accessible:\n%s"):format(tostring(BASE_DIR)))
        end
    end,
    MENU_TOOLS_UNSORTED
)

local files = list_pcaps()
if #files == 0 then
    register_menu(
        "dSPACE V2Gshark/Example V2G Traces/(no PCAPs found)",
        function()
            report_failure("No .pcap/.pcapng files found!")
        end,
        MENU_TOOLS_UNSORTED
    )
else
    for _, fname in ipairs(files) do
        local fullpath = BASE_DIR .. "/" .. fname
        register_menu(
            "dSPACE V2Gshark/Example V2G Traces/" .. fname,
            function()
                open_capture_file(fullpath)
            end,
            MENU_TOOLS_UNSORTED
        )
    end
end

local function show_about_popup()
    local tw = TextWindow.new("About - dSPACE V2Gshark Plugin")

    local ws_ver = get_version and get_version() or "(unknown)"
    local plugin_dir = v2gcommon.get_plugins_file_path()

    local lines = {
        "dSPACE V2Gshark Wireshark Plugin",
        "---------------------------------",
        ("Version    : %s"):format(tostring(info.version)),
        ("Author     : %s"):format(tostring(info.author)),
        ("Wireshark  : %s"):format(ws_ver),
        ("Plugin Dir : %s"):format(plugin_dir),
        ("Repository : %s"):format(tostring(info.repository))
    }

    tw:set(table.concat(lines, "\n"))

    -- Buttons
    tw:add_button(
        "Open GitHub Repository",
        function()
            browser_open_url(info.repository)
        end
    )
end

register_menu("dSPACE V2Gshark/About...", show_about_popup, MENU_TOOLS_UNSORTED)

register_menu(
    "dSPACE V2Gshark/Open dsV2Gshark on GitHub",
    function()
        browser_open_url(info.repository)
    end,
    MENU_TOOLS_UNSORTED
)
