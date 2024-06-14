#!/bin/bash

# Compile source files
echo "Compiling..."
g++ -std=c++11 -o executable/http_server beriw-lib/http_server.cpp main.cpp

# Check if compilation successful
if [ $? -eq 0 ]; then
    echo "Compilation successful."
    echo "Starting HTTP server..."

    # Run the compiled HTTP server
    ./executable/http_server
else
    echo "Compilation failed."
fi