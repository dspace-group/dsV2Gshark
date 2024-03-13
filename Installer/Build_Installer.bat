:: Script to build DLLs and create Installer. Should be run in MinGW Bash (e.g. git-bash)
:: note: Inno Setup must be installed and added to Path

@echo off
:: create DLLs
cd "%~dp0../V2G_Libraries/"
call build_all_win.bat
if %ERRORLEVEL% NEQ 0 goto :failed
copy "CertificateInfos\bin\v2gX509CertInfos.dll" "%~dp0..\Wireshark\"
if %ERRORLEVEL% NEQ 0 goto :failed
copy "V2GDecoder\bin\v2gLuaDecoder.dll" "%~dp0..\Wireshark\"
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