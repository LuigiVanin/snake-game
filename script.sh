if [ "$1" = "--build" ]; then
  cmake -D CMAKE_C_COMPILER=clang . -B ./build
  
  make -C ./build
elif [ "$1" = "--run" ]; then
  make -C ./build
  ./build/snake_game
else 
  cmake -D CMAKE_C_COMPILER=clang . -B ./build
  make -C ./build
  ./build/snake_game
fi