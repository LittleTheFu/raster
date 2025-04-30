# Rasterizer Project

This project is a simple software rasterizer application built using SDL2 and Eigen library. It demonstrates the basic principles of 3D graphics rendering, including transformation, clipping, rasterization, and texture mapping.

## Features

- Initializes SDL2 video subsystem
- Creates a window with specified dimensions and position
- Implements a simple pipeline for transforming 3D models to 2D screen coordinates
- Supports texture mapping for triangle surfaces
- Implements a Z-buffer for depth testing
- Renders a textured triangle and displays it in a window
- Properly cleans up SDL resources before exiting

## Prerequisites

- SDL2 library installed on your system
- Eigen library installed on your system
- C++ compiler (e.g., g++)

## How to Build and Run

1. Clone this repository or download the source code.
2. Make sure you have SDL2 and Eigen libraries installed on your system.
3. Compile the code using the following command:

   ```bash
   g++ -o rasterizer main.cpp rasterizer.cpp texture.cpp frame.cpp pipeline.cpp zbuffer.cpp triangle.cpp -I/path/to/eigen -lSDL2