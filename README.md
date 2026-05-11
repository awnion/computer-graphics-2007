# MG OpenGL 2007

An old computer graphics coursework project built with OpenGL/GLUT. The source code is kept as close to the original as practical; the changes are limited to macOS compatibility and building with `make`.

<p>
  <a href="https://chatgpt.com/?q=Explore%20this%20C%2B%2B17%20OpenGL%2FGLUT%20coursework%20repo%3A%20https%3A%2F%2Fgithub.com%2Fawnion%2Fcomputer-graphics-2007.%20Build%20with%20make%2C%20run%20with%20make%20run.%20Focus%20on%20README.md%20and%20src%2FappMG."><img alt="Open in ChatGPT" src="https://img.shields.io/badge/Open%20in-ChatGPT-10A37F?style=for-the-badge&logo=openai&logoColor=white"></a>
  <a href="https://chatgpt.com/codex?prompt=Explore%20this%20C%2B%2B17%20OpenGL%2FGLUT%20coursework%20repo%3A%20https%3A%2F%2Fgithub.com%2Fawnion%2Fcomputer-graphics-2007.%20Build%20with%20make%2C%20run%20with%20make%20run.%20Focus%20on%20README.md%20and%20src%2FappMG.&amp;originUrl=https%3A%2F%2Fgithub.com%2Fawnion%2Fcomputer-graphics-2007"><img alt="Open in Codex" src="https://img.shields.io/badge/Open%20in-Codex-3B82F6?style=for-the-badge&logo=openai&logoColor=white"></a>
  <a href="https://claude.ai/new?q=Explore%20this%20C%2B%2B17%20OpenGL%2FGLUT%20coursework%20repo%3A%20https%3A%2F%2Fgithub.com%2Fawnion%2Fcomputer-graphics-2007.%20Build%20with%20make%2C%20run%20with%20make%20run.%20Focus%20on%20README.md%20and%20src%2FappMG."><img alt="Open in Claude" src="https://img.shields.io/badge/Open%20in-Claude-D97757?style=for-the-badge&logo=anthropic&logoColor=white"></a>
  <a href="https://claude.ai/code/new?repo=awnion%2Fcomputer-graphics-2007&amp;branch=main&amp;q=Explore%20this%20C%2B%2B17%20OpenGL%2FGLUT%20coursework%20repo%3A%20https%3A%2F%2Fgithub.com%2Fawnion%2Fcomputer-graphics-2007.%20Build%20with%20make%2C%20run%20with%20make%20run.%20Focus%20on%20README.md%20and%20src%2FappMG."><img alt="Open in Claude Code" src="https://img.shields.io/badge/Open%20in-Claude%20Code-D97757?style=for-the-badge&logo=anthropic&logoColor=white"></a>
  <a href="https://cursor.com/link/prompt?text=Explore%20this%20C%2B%2B17%20OpenGL%2FGLUT%20coursework%20repo%3A%20https%3A%2F%2Fgithub.com%2Fawnion%2Fcomputer-graphics-2007.%20Build%20with%20make%2C%20run%20with%20make%20run.%20Focus%20on%20README.md%20and%20src%2FappMG."><img alt="Open in Cursor" src="https://img.shields.io/badge/Open%20in-Cursor-000000?style=for-the-badge&logo=cursor&logoColor=white"></a>
</p>

## macOS Requirements

- macOS with Xcode Command Line Tools installed.
- No extra OpenGL libraries are required: the project links against the system `OpenGL` and `GLUT` frameworks.
- A compiler with C++17 support. The default macOS `clang++` from Command Line Tools is enough.

If `clang++` is not available, install Command Line Tools:

```sh
xcode-select --install
```

## Build

```sh
make
```

The executable is created here:

```sh
bin/appMG
```

## Run

```sh
make run
```

The application opens a 1600x1200 GLUT window. Press `Esc` to exit.

## Controls

- Arrow keys: move the camera on the X/Y axes.
- `W` / `S`: move the camera on the Z axis.
- `C`: reset the camera to its initial position.
- `A`: toggle antialiasing through the accumulation buffer.
- `B`: toggle object transparency.
- `F`: toggle fog.
- `L`: toggle lighting.
- `N`: show/hide normals.
- `1`-`4`: toggle light sources, if they have been created in the current frame.

Letter shortcuts also work when the Russian ЙЦУКЕН keyboard layout is active.

## Clean

```sh
make clean
```

## macOS Compatibility Changes

- Added `src/appMG/GLCompat.h` for platform-specific GLUT includes.
- On macOS, `GetTickCount()` is provided through a compatibility wrapper around `glutGet(GLUT_ELAPSED_TIME)`.
- Replaced `void main` with standard `int main`.
- Added a `Makefile` that links against the system OpenGL/GLUT frameworks.

## Modernization Notes

- The project now builds as C++17 while still using the original immediate-mode OpenGL/GLUT rendering style.
- Fixed array ownership in `Torid`: arrays are released with `delete[]`, including the previously leaked normals array.
- Texture generation now uses `std::vector` instead of manual `malloc`/`free`.
- Rendering is driven by a GLUT timer instead of a busy idle callback, which avoids pegging the CPU while the scene is open.
- FPS is shown in the window title once per second instead of printing one line per frame to the terminal.

## Project Architecture

```mermaid
flowchart TD
    Makefile["Makefile"] --> Binary["bin/appMG"]
    Sources["src/appMG/*.cpp, *.h"] --> Makefile

    Main["main.cpp<br/>GLUT setup and render loop"] --> GLCompat["GLCompat.h<br/>platform OpenGL/GLUT includes"]
    Main --> Scene["Scene rendering<br/>floor, wall, mirror, lights"]
    Main --> Torid["Torid<br/>procedural tube mesh"]
    Main --> Geometry["Geometry<br/>vectors, normals, rotation, reflection matrix"]

    Torid --> ComplexObject["ComplexObject<br/>quad storage and camera-distance sorting"]
    Torid --> Geometry
    ComplexObject --> Geometry

    Main --> Callbacks["GLUT callbacks"]
    Callbacks --> Display["display()"]
    Callbacks --> Reshape["reshape()"]
    Callbacks --> Keyboard["keyboard() / arrow_keys()"]
    Callbacks --> Timer["timer()"]

    Display --> Render["Render()"]
    Render --> Scene
    Render --> Mirror["Stencil mirror pass"]
    Render --> Geometry

    Keyboard --> State["Global render state<br/>camera, fog, lighting, blending, normals"]
    Timer --> Display
```
