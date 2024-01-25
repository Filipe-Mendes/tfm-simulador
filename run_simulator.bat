@echo off
setlocal enabledelayedexpansion

set exePath=.\Unity\Build
set exeName=PlatformController.exe

%exePath%\%exeName%

exit /b 0