@echo off

set zip=.\c_coder
set shrlib=.\c_coder_ert_shrlib_rtw
set folder1=.\slprj
set win=c_coder_win64
set cm=.\PlatformController\include\MATLAB
set cs=.\PlatformController\include\c_coder_ert_shrlib_rtw

if exist %zip% (
	rmdir /s /q %zip%
)

if exist %zip%.zip (
	del /q %zip%.zip
)

if exist %shrlib% (
	rmdir /s /q %shrlib%
)

if exist %folder1% (
	rmdir /s /q %folder1%
)

if exist %win%.dll (
	del /q %win%.dll
)

if exist %win%.lib (
	del /q %win%.lib
)

if exist %cm%\ (
	rmdir /s /q %cm%
)

if exist %cs%\ (
	rmdir /s /q %cs%
)


exit /b 0