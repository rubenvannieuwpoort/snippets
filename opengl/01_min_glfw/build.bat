@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall" x64
mkdir build
pushd build
cl /Zi C:\glfw3\lib-vc2017\glfw3.lib opengl32.lib user32.lib gdi32.lib shell32.lib ../src/main.cpp /I C:\glfw3\include /MD
popd
pause