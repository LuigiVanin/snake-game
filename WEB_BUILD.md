# Building Snake Game for WebAssembly 🌐

This guide explains how to compile and run your Snake Game in a web browser using WebAssembly.

## Prerequisites

You need to install **Emscripten**, the WebAssembly compiler toolchain.

### Installing Emscripten

```bash
# Clone the Emscripten SDK
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk

# Install and activate the latest version
./emsdk install latest
./emsdk activate latest

# Set up environment variables (run this in each new terminal session)
source ./emsdk_env.sh
```

After running `source ./emsdk_env.sh`, verify the installation:

```bash
emcc --version
```

You should see the Emscripten compiler version information.

## Building for Web

Once Emscripten is installed and activated in your terminal:

```bash
# Make the build script executable (first time only)
chmod +x build-web.sh

# Build the WebAssembly version
./build-web.sh
```

This will create a `build-web` directory containing:
- `snake_game.html` - The main HTML file
- `snake_game.js` - JavaScript glue code
- `snake_game.wasm` - The WebAssembly binary
- `snake_game.data` - Asset files (if any)

## Running the Game

You need to serve the files through a web server (not just open the HTML file) due to browser security restrictions.

### Option 1: Python HTTP Server (Recommended)

```bash
# Serve from the build-web directory
python3 -m http.server 8000 --directory build-web
```

Then open your browser to: **http://localhost:8000/snake_game.html**

### Option 2: Node.js HTTP Server

```bash
# Install http-server globally (one time)
npm install -g http-server

# Serve the files
cd build-web
http-server -p 8000
```

Then open: **http://localhost:8000/snake_game.html**

### Option 3: PHP Built-in Server

```bash
cd build-web
php -S localhost:8000
```

Then open: **http://localhost:8000/snake_game.html**

## Game Controls

- **Arrow Keys (↑↓←→)**: Move the snake
- **Enter**: Select menu options
- **P**: Pause game

## Troubleshooting

### "emcc: command not found"

You need to activate Emscripten in your current terminal:
```bash
cd path/to/emsdk
source ./emsdk_env.sh
```

### Black Screen or Loading Forever

1. Check the browser console (F12) for error messages
2. Make sure you're serving through a web server, not opening the file directly
3. Try a different browser (Chrome or Firefox recommended)

### Performance Issues

The game should run smoothly in modern browsers. If you experience lag:
1. Close other browser tabs
2. Try a different browser
3. Check if hardware acceleration is enabled in browser settings

## File Structure

```
snake-game/
├── build-web.sh          # WebAssembly build script
├── shell.html            # HTML template for the game
├── build-web/            # Output directory (generated)
│   ├── snake_game.html   # Main HTML file
│   ├── snake_game.js     # JavaScript glue code
│   └── snake_game.wasm   # WebAssembly binary
└── src/                  # Source code
```

## Deploying to a Website

To host your game on a website:

1. Build the game: `./build-web.sh`
2. Upload the entire `build-web` directory to your web host
3. Access `snake_game.html` through your website URL

You can deploy to:
- **GitHub Pages**: Commit build-web contents to gh-pages branch
- **Netlify**: Drag and drop the build-web folder
- **Vercel**: Deploy from your repository
- **Any static hosting service**

## Advanced: Customizing the HTML Template

The `shell.html` file is the template used for the game page. You can customize:
- Colors and styling (CSS in `<style>` section)
- Layout and text
- Loading messages
- Control instructions

After making changes, rebuild with `./build-web.sh` to see them in action.

## Differences from Desktop Version

The WebAssembly version has some differences:
- Runs in a browser instead of native window
- Uses browser's rendering engine
- Performance depends on browser and hardware
- No file system access (for security)

The gameplay is identical to the desktop version!

## Need Help?

If you encounter issues:
1. Check the browser console (F12) for errors
2. Verify Emscripten is properly installed and activated
3. Make sure you're using a modern browser (Chrome, Firefox, Edge, Safari)
4. Try rebuilding: `rm -rf build-web && ./build-web.sh`

