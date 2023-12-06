@echo off

set matlabPath=%~dp0MATLAB

cd %matlabPath%
matlab -batch build_model