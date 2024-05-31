@echo off
echo This script updates the version of the plugin
echo.

setlocal EnableDelayedExpansion

:EnterVersion
set /p "newVersion=Enter the new version ['X.X.X']: "
echo %newVersion% | findstr /R "^[0-9][0-9]*.[0-9][0-9]*.[0-9][0-9]*" | findstr /V /R "[a-zA-Z]" > nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    ECHO ERROR - Please enter a version in the format X.X.X
    goto EnterVersion
)

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

:: update v2gcommon.lua
set "FileName=.\Wireshark\plugins\v2gcommon.lua"
del "%TempFile%" 2>nul
for /F delims^=^ eol^= %%A in ('%SystemRoot%\System32\findstr.exe /N "^" "%FileName%"') do (
    set "Line=%%A"
    setlocal EnableDelayedExpansion
    if not "!Line:v2gcommon.DS_V2GSHARK_VERSION=!" == "!Line!" (
        if not "!Line:DO NOT CHANGE=!" == "!Line!" (
            echo v2gcommon.DS_V2GSHARK_VERSION = "%newVersion%" -- DO NOT CHANGE
        ) else echo(!Line:*:=!
    ) else echo(!Line:*:=!
    endlocal
) >>"%TempFile%"
move /y %TempFile% %FileName%

:: update V2GDecoder resource file
set "FileName=.\V2G_Libraries\V2GDecoder\main.rc"
del "%TempFile%" 2>nul
for /F delims^=^ eol^= %%A in ('%SystemRoot%\System32\findstr.exe /N "^" "%FileName%"') do (
    set "Line=%%A"
    setlocal EnableDelayedExpansion
    if not "!Line:#define VER_PRODUCTVERSION =!" == "!Line!" (
        echo #define VER_PRODUCTVERSION          %newVersion:.=,%,0
    ) else if not "!Line:#define VER_PRODUCTVERSION_STR=!" == "!Line!" (
        echo #define VER_PRODUCTVERSION_STR      "%newVersion%.0\0"
    ) else if not "!Line:#define VER_FILEVERSION =!" == "!Line!" (
        echo #define VER_FILEVERSION             %newVersion:.=,%,0
    ) else if not "!Line:#define VER_FILEVERSION_STR=!" == "!Line!" (
        echo #define VER_FILEVERSION_STR         "%newVersion%.0\0"
    ) else echo(!Line:*:=!
    endlocal
) >>"%TempFile%"
move /y %TempFile% %FileName%

:: update CertificateInfo resource file
set "FileName=.\V2G_Libraries\CertificateInfos\main.rc"
del "%TempFile%" 2>nul
for /F delims^=^ eol^= %%A in ('%SystemRoot%\System32\findstr.exe /N "^" "%FileName%"') do (
    set "Line=%%A"
    setlocal EnableDelayedExpansion
    if not "!Line:#define VER_PRODUCTVERSION =!" == "!Line!" (
        echo #define VER_PRODUCTVERSION          %newVersion:.=,%,0
    ) else if not "!Line:#define VER_PRODUCTVERSION_STR=!" == "!Line!" (
        echo #define VER_PRODUCTVERSION_STR      "%newVersion%.0\0"
    ) else if not "!Line:#define VER_FILEVERSION =!" == "!Line!" (
        echo #define VER_FILEVERSION             %newVersion:.=,%,0
    ) else if not "!Line:#define VER_FILEVERSION_STR=!" == "!Line!" (
        echo #define VER_FILEVERSION_STR         "%newVersion%.0\0"
    ) else echo(!Line:*:=!
    endlocal
) >>"%TempFile%"
move /y %TempFile% %FileName%

:EndBatch
endlocal

pause