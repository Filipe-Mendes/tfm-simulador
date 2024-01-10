@echo off

set matlabPath=%~dp0MATLAB

cd %matlabPath%

matlab -batch build_model

set zipFile=c_coder.zip
set unzipFolder=c_coder

set bin=PlatformController\bin
set include=PlatformController\include

if exist %unzipFolder% (
	del %unzipFolder%
)

mkdir %unzipFolder%
xcopy %zipFile% %unzipFolder%
cd %unzipFolder%
tar -xf %zipFile%
cd ..

move %unzipFolder%\MATLAB\c_coder_win64.lib %bin%
move %unzipFolder%\MATLAB\c_coder_win64.dll %bin%

move %unzipFolder%\MATLAB %include%

move %unzipFolder%\R2021b\simulink\include\rtw_solver.h %include%\c_coder_ert_shrlib_rtw
move %unzipFolder%\R2021b\simulink\include\rtw_continuous.h %include%\c_coder_ert_shrlib_rtw

cd ..