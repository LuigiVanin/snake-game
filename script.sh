#!/bin/bash

debug_opt=""
# Check if --debug is in the arguments
for arg in "$@"; do
  if [ "$arg" = "--debug" ]; then
    debug_opt="-D CMAKE_BUILD_TYPE=Debug"
    break
  fi
done

action="$1"
if [ "$1" = "--debug" ] && [ -n "$2" ]; then
  action="$2"
fi

if [ "$action" = "--build" ]; then
  echo "Configuring CMake with: -D CMAKE_C_COMPILER=clang ${debug_opt} . -B ./build"
  cmake -D CMAKE_C_COMPILER=clang ${debug_opt} . -B ./build
  make -C ./build

elif [ "$action" = "--run" ]; then
  make -C ./build
  ./build/snake_game

else 
  # Default action: configure, build, and run
  echo "Configuring CMake with: -D CMAKE_C_COMPILER=clang ${debug_opt} . -B ./build (default action)"
  cmake -D CMAKE_C_COMPILER=clang ${debug_opt} . -B ./build
  
  make -C ./build  
  ./build/snake_game
fi