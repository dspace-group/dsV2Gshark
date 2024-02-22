@echo off
echo This script updates the version of the plugin (lua files and installer)
echo.

set /p "newVersion=Enter the new version: "

setlocal EnableExtensions DisableDelayedExpansion

set "TempFile=test.tmp"

:: update InstallerScript.iss
set "FileName=.\Installer\InstallerScript.iss"
del "%TempFile%" 2>nul
for /F delims^=^ eol^= %%A in ('%SystemRoot%\System32\findstr.exe /N "^" "%FileName%"') do (
    set "Line=%%A"
    setlocal EnableDelayedExpansion
    if not "!Line:#define AppVer=!" == "!Line!" (
        echo #define AppVer "%newVersion%"
    ) else echo(!Line:*:=!
    endlocal
) >>"%TempFile%"
move /y %TempFile% %FileName%

:: update v2gmsg.lua
set "FileName=.\Wireshark\plugins\v2gmsg.lua"
del "%TempFile%" 2>nul
for /F delims^=^ eol^= %%A in ('%SystemRoot%\System32\findstr.exe /N "^" "%FileName%"') do (
    set "Line=%%A"
    setlocal EnableDelayedExpansion
    if not "!Line:DS_V2GSHARK_VERSION=!" == "!Line!" (
        if not "!Line:DO NOT CHANGE=!" == "!Line!" (
            echo DS_V2GSHARK_VERSION = "%newVersion%" -- DO NOT CHANGE
        ) else echo(!Line:*:=!
    ) else echo(!Line:*:=!
    endlocal
) >>"%TempFile%"
move /y %TempFile% %FileName%

:EndBatch
endlocal

pause