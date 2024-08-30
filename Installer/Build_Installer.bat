:: Script to create the installer. Make sure the v2gLib is built before.
:: Should be run in MinGW Bash (e.g. git-bash)
:: note: Inno Setup must be installed and added to Path

@echo off
:: copy v2gLib binaries
cd "%~dp0../V2G_Libraries/"
copy "v2gLib\bin\v2gLib*.dll" "%~dp0..\Wireshark\"
if %ERRORLEVEL% NEQ 0 goto :failed

:: prepare installer readme
cd "%~dp0"
set "README_REPO=..\README.md"
set "README_INSTALLER=dsV2Gshark_README.txt"
findstr /V /B /C:"![" /C:"[![" %README_REPO% > %README_INSTALLER%

:: create installer
cd "%~dp0"
call iscc.exe InstallerScript.iss
if %ERRORLEVEL% NEQ 0 goto :failed
move "%README_INSTALLER%" "%~dp0Output\%README_INSTALLER%"

goto :success

:failed
cd "%~dp0"
echo An error occured!
pause
exit /B 1

:success
echo SUCCESS
pause
cd "%~dp0"