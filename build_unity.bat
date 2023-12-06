@echo off

set projectpath=.\Unity\aceleracao
set buildFolder=.\UnityBuild
set buildpath=%buildFolder%\aceleracao.exe
set logpath=%buildFolder%\buildlog.txt

set unityPath=C:\Program Files\Unity\Hub\Editor\2022.3.10f1\Editor\Unity.exe

if not exist %buildFolder% (
    mkdir %buildFolder%
)

"%unityPath%" -batchmode -projectpath %projectpath% -buildWindows64Player %buildpath% -logFile %logpath% -buildTarget Win64 -standaloneBuildSubtarget Player

rem echo Build Finished

rem "C:\Program Files\Unity\Hub\Editor\2022.3.10f1\Editor\Unity.exe" -quit -batchmode -projectpath .\Unity\aceleracao -buildWindowsPlayer .\UnityBuild\aceleracao.exe