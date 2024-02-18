@echo off

set matlabPath=%~dp0MATLAB

cd %matlabPath%

set clean=clean_folder.bat

call %clean%

matlab -batch build_model

set zipFile=c_coder.zip
set unzipFolder=c_coder

set bin=PlatformController\bin
set include=PlatformController\include


mkdir %unzipFolder%
xcopy %zipFile% %unzipFolder%
cd %unzipFolder%
tar -xf %zipFile%
cd ..

move %unzipFolder%\MATLAB\c_coder_win64.lib %bin%
move %unzipFolder%\MATLAB\c_coder_win64.dll %bin%

mkdir %include%\MATLAB
Xcopy %unzipFolder%\MATLAB\*.* %include%\MATLAB /E /H /C /I /q

move %unzipFolder%\R2021b\simulink\include\rtw_solver.h %include%\MATLAB\c_coder_ert_shrlib_rtw
move %unzipFolder%\R2021b\simulink\include\rtw_continuous.h %include%\MATLAB\c_coder_ert_shrlib_rtw

cd ..