cmake_minimum_required(VERSION 3.22)
project(snake_game C)

set(CMAKE_C_STANDARD 23) 
set(CMAKE_C_STANDARD_REQUIRED True)

include(FetchContent)

function(add_git_dependency libName gitURL gitTag)
    FetchContent_Declare(${libName}
        GIT_REPOSITORY ${gitURL}
        GIT_TAG        ${gitTag}
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
    )
    FetchContent_MakeAvailable(${libName})
    target_compile_options(${libName} PRIVATE "-w")
endfunction()

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
add_git_dependency(
    raylib
    https://github.com/raysan5/raylib.git
    5.5
)

add_executable(
    snake_game 
    src/main.c 
    src/game.c
    src/map.c 
    src/snake.c
    src/food.c
    src/gui/pause.c
    src/array-list/d_array_list.c
)

# Link against the imported target provided by find_package
# This automatically handles include directories and library paths
target_link_libraries(snake_game PRIVATE raylib)