:: Script to build DLLs and create Installer. Should be run in MinGW Bash (e.g. git-bash)

make -C CertificateInfos dll
if %ERRORLEVEL% NEQ 0 goto :failed
make -C V2GDecoder dll
if %ERRORLEVEL% NEQ 0 goto :failed
goto :success

:failed
echo failed to build lua libs!
pause
exit /B 1

:success
echo Lua libs built successfully!