@echo off
setlocal enabledelayedexpansion

set makePath=.\MATLAB\PlatformController

set exePath=.\MATLAB\PlatformController\bin
set exeName=PlatformController.exe

set dllPath=.\MATLAB
set dllName=c_coder_win64.dll

set configFile=platform_tcp_parameters.txt


for /f "tokens=1,* delims==" %%a in (%configFile%) do (
    set "variable=%%a"
    set "value=%%b"
    set !variable!=!value!
)

cd %makePath%
make
cd ../..

if not exist %dllPath%\%dllName% (
    echo PlatformController library does not exist. Please generate C dll.
	exit /b
)

%exePath%\%exeName% %OPEN_PORT% %PLATFORM_IP% %PLATFORM_PORT% %MOCK%

exit /b 0