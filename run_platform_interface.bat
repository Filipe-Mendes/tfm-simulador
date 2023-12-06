@echo off

set exePath=.\MATLAB\PlatformController\bin\Debug
set exeName=PlatformController.exe

set dllPath=.\MATLAB
set dllName=c_coder_win64.dll

set serverIP=127.0.0.1
set serverPort=55001

set clientIP=127.0.0.1
set clientPort=55001

set mock=mock


if not exist %exePath%\%exeName% (
    echo PlatformController executable does not exist. Please build C# project.
	exit /b
)

if not exist %dllPath%\%dllName% (
    echo PlatformController library does not exist. Please generate C dll.
	exit /b
)


if "%1"=="" goto noArg 

if %1== %mock% goto mockArg

echo Argument not recognized
exit /b 0

:noArg
%exePath%\%exeName% %serverIP% %serverPort% %clientIP% %clientPort% 

exit /b 0


:mockArg
%exePath%\%exeName% %serverIP% %serverPort% %clientIP% %clientPort% %mock%

exit /b 0