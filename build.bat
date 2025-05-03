@echo off
setlocal enabledelayedexpansion

REM =================== Здесь нужно задать путь до Qt, без скобок

set QT_PATH=D:\QT\6.9.0\msvc2022_64

REM ==================

if not exist build (
    mkdir build
)

cd build

cmake .. -DCMAKE_PREFIX_PATH="%QT_PATH%"

cmake --build . --config Debug

"%QT_PATH%\bin\windeployqt.exe" bin\gui_translator.exe --debug

cd ..

