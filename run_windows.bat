@echo off

rem Compile source files
echo Compiling...
g++ -std=c++11 -o http_server http_server.cpp main.cpp

rem Check if compilation successful
if %errorlevel% equ 0 (
    echo Compilation successful.
    echo Starting HTTP server...

    rem Run the compiled HTTP server
    .\http_server
) else (
    echo Compilation failed.
)