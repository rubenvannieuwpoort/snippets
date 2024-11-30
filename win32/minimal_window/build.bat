@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall" x64
mkdir build
pushd build
cl /Zi ../src/main.cpp user32.lib gdi32.lib
popd
pause