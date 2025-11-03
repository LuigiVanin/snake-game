#!/bin/bash

# Build script for WebAssembly using Emscripten
# This script compiles the snake game to run in a web browser

echo "Building Snake Game for WebAssembly..."

# Check if emscripten is installed
if ! command -v emcc &> /dev/null; then
    echo "Error: Emscripten (emcc) not found!"
    echo "Please install Emscripten first:"
    echo "  git clone https://github.com/emscripten-core/emsdk.git"
    echo "  cd emsdk"
    echo "  ./emsdk install latest"
    echo "  ./emsdk activate latest"
    echo "  source ./emsdk_env.sh"
    exit 1
fi

# Create web build directory
mkdir -p build-web

# Configure with Emscripten toolchain
echo "Configuring CMake with Emscripten..."
emcmake cmake -B build-web \
    -DPLATFORM=Web \
    -DCMAKE_BUILD_TYPE=Release

# Build
echo "Compiling..."
cd build-web
emmake make

echo ""
echo "Build complete!"
echo "Output files are in: build-web/"
echo ""
echo "To test locally, run:"
echo "  python3 -m http.server 8000 --directory build-web"
echo "Then open: http://localhost:8000/snake_game.html"

