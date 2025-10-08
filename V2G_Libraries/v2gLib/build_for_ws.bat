:: Script to build v2gLib. Takes the path to installed Wireshark as parameter
:: Will create a new v2gLib for each Lua version found in the given directory
:: You may run this script multiple times with different arguments to support more Wireshark versions
:: Should be run in MinGW Bash (e.g. git-bash)

@echo off
setlocal enabledelayedexpansion

if "%~1"=="" (
    echo Please provide the path to your Wireshark installation
    exit /b 1
)

if not exist "%~1" (
    echo The directory "%~1" does not exist.
    exit /b 1
)

set "dir=%~1"
set "highest_version=0"
set "highest_file="

:: Check if the directory exists
if not exist "%dir%" (
    echo Directory does not exist: %dir%
    goto :eof
)

:: Loop over all Lua binaries
for /f "delims=" %%F in ('dir /b /a-d "%dir%\lua*.dll" 2^>nul') do (
    set "fullpath=%dir%\%%F"
    set "filename=%%F"
    set "version=!filename:~3,-4!"
    set "cleanversion=!version:.=!"

    echo Detected Lua !cleanversion! in %dir%

    :: create v2gLib for detected Lua version
    set LFLAGS_WIRESHARK_DIR=-L"%dir%"
    set IFLAGS_LUA=-I"../Third_Party/lua/lua-!cleanversion!/include"
    set BINARY_OUT_NAME=v2gLib_!cleanversion!.dll
    if !cleanversion! EQU 51 (
        set LFLAGS_LUA=-llua5.1
    ) else (
        set LFLAGS_LUA=-llua!cleanversion!
    )

    make clean-obj all

    if %ERRORLEVEL% NEQ 0 (
        echo failed to build v2gLib for !cleanversion!!
        exit /B 1
    ) else (
        echo successfully built v2gLib for Lua !cleanversion!!
    )
)

echo Lua libs built successfully!
endlocal