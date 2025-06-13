# Snake Game

A classic Snake game implementation written entirely in C using the Raylib graphics library. The game features smooth gameplay, collision detection, pause functionality, and increasing difficulty as you progress.

> [!WARNING] 
> This game was developed in the Linux operating System, compatibility with the windows sytem is not suported :/

## Features

- **Classic Snake Gameplay**: Control the snake to eat food and grow longer
- **Collision Detection**: Snake wraps around screen edges and detects self-collision
- **Progressive Difficulty**: Game speed increases as you eat more food
- **Pause System**: Pause and resume the game with an interactive menu
- **Clean Graphics**: Simple, clean visual design with grid-based movement

## Prerequisites

Before building and running the game, ensure you have the following installed:

- **CMake** (version 3.22 or higher)
- **Clang** compiler
- **Make** build tool
- **Git** (for fetching dependencies)

### Linux Dependencies

On Ubuntu/Debian systems, you'll also need these libraries:
```bash
sudo apt update
sudo apt install build-essential cmake clang git
sudo apt install libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
```

## Building and Running

The project includes a convenient shell script that handles building and running the game.

### Quick Start

To build and run the game in one command:
```bash
./script.sh
```

### Available Commands

The `script.sh` script supports several options:

#### Build Only
```bash
./script.sh --build
```

#### Run Only (assumes already built)
```bash
./script.sh --run
```

#### Debug Mode
Build and run with debug symbols:
```bash
./script.sh --debug
```

Build only in debug mode:
```bash
./script.sh --debug --build
```

### Manual Build (Alternative)

If you prefer to build manually using CMake:

```bash
# Configure the project
cmake -D CMAKE_C_COMPILER=clang . -B ./build

# Build the project
make -C ./build

# Run the game
./build/snake_game
```

For debug builds:
```bash
cmake -D CMAKE_C_COMPILER=clang -D CMAKE_BUILD_TYPE=Debug . -B ./build
make -C ./build
./build/snake_game
```

## How to Play

### Controls

- **Arrow Keys** or **WASD**: Control snake direction
  - `W` / `↑`: Move Up
  - `A` / `←`: Move Left  
  - `S` / `↓`: Move Down
  - `D` / `→`: Move Right
- **Space**: Pause/Resume the game
- **Enter**: Select option in pause menu (when paused)
- **↑/↓**: Navigate pause menu options

## Project Structure

```
├── src/
│   ├── main.c              # Main game loop and initialization
│   ├── game.c/.h           # Core game logic and state management
│   ├── snake.c/.h          # Snake entity and behavior
│   ├── food.c/.h           # Food entity and generation
│   ├── map.c/.h            # Game map and tile system
│   ├── gui/
│   │   └── pause.c/.h      # Pause menu implementation
│   └── array-list/
│       └── d_array_list.c  # Dynamic array implementation
├── CMakeLists.txt          # CMake build configuration
├── script.sh              # Build and run script
├── .clangd                 # Language server configuration
├── .gitignore              # Git ignore rules
└── license.md              # MIT License
```

### Dependencies

The project automatically fetches and builds Raylib as a dependency through CMake's FetchContent module. No manual dependency installation is required.

## License

This project is licensed under the MIT License. See [license.md](license.md) for details.

## Troubleshooting

### Build Issues

If you encounter build issues:

1. Ensure all prerequisites are installed
2. Try cleaning the build directory: `rm -rf build/`
3. Run the build command again: `./script.sh --build`

### Runtime Issues

- **Black screen**: Ensure your system supports OpenGL
- **Input not working**: Try running in a different terminal or environment
- **Performance issues**: The game is designed to run at 60 FPS; check system resources

## Contributing

Feel free to fork this project and submit pull requests for improvements, bug fixes, or new features!