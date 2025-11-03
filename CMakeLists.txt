cmake_minimum_required(VERSION 3.22)
project(snake_game C)

set(CMAKE_C_STANDARD 23) 
set(CMAKE_C_STANDARD_REQUIRED True)

# Platform detection for WebAssembly
if (DEFINED PLATFORM)
    if (PLATFORM STREQUAL "Web")
        set(WEB TRUE)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3")
    endif()
endif()

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
    src/gui/menu.c
    src/gui/game_over.c
    src/array-list/d_array_list.c
)

# Link against the imported target provided by find_package
# This automatically handles include directories and library paths
target_link_libraries(snake_game PRIVATE raylib)

# WebAssembly specific settings
if (WEB)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    
    # Set WebAssembly-specific compiler and linker flags
    set_target_properties(snake_game PROPERTIES
        LINK_FLAGS "-s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1 --shell-file ${CMAKE_SOURCE_DIR}/shell.html"
    )
    
    # Additional optimization flags for release builds
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_link_options(snake_game PRIVATE
            -O3
            -s ALLOW_MEMORY_GROWTH=1
        )
    endif()

endif()