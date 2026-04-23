# Nelta - Nintendo DS Emulator

Nelta is a lightweight, hardware-accelerated Nintendo DS emulator frontend designed for Windows PC, powered by the melonDS core and SDL2.

## Features
* **Accurate Emulation:** Powered by the highly accurate melonDS core.
* **Hardware Acceleration:** OpenGL streaming textures via SDL2.
* **Aspect Ratio Correction:** Automatic 1:1.5 screen scaling with letterboxing.
* **Save Management:** Full support for SRAM (Battery saves) and Quick Save States (`F1` to Save, `F3` to Load).
* **Native OS Integration:** Built-in Windows file dialog for loading ROMs (`Ctrl + O`).
* **Built-in Performance Tracking:** Live FPS Counter in the window title.

## Build Instructions (Windows)
1. Ensure you have **CMake** and a C++17 compiler (like Visual Studio/MSVC or MinGW) installed.
2. Install the **SDL2** development libraries.
3. Clone this repository (including the melonDS submodule).
4. Run the following commands from the root directory:
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build . --config Release
