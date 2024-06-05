# RayTracing
C++ implementation of Peter Shirley's "Ray Tracing in One Weekend" series of books (https://raytracing.github.io/).

## Features
- Multi-threaded rendering.
- Anti-aliasing.
- Basic primitives rendering: Spheres and triangles.
- Sphere UV-mapping with an image.
- Few materials: Dielectric, Diffuse surface (Lambertian surface) and Metal.
- Few textures can be applied to materials: Checker board, image texture (only relevant for spheres now) and a simple color texture.
- Color gradient skybox.

## Potential improvements
- Image support for the skybox.
- Triangle UV-mapping with an image.
- Scene diffuse lighting.
- Vectorized 3-dimensional vectors arithmetic.

## Example
![Example of a rendered scene.](https://github.com/TheBanji/RayTracing/blob/main/img/raytracing5.png?raw=true)

## Important note
Image rendering is splat among several threads. Depending on your system capabilities, you may want to precisely tune the number of spawned threads as to speed-up rendering. A #define pre-processor **NB_THREADS** found in src/scene.cpp can be adjusted in that sense. Note that the latter should be a power of 4, namely 1, 4, 16, 64, 256 and so on. By default, **NB_THREADS** is set to 16.

Default configuration renders the scene in low resolution, namely 640x480 with 100 rays per pixel and a maximum bounce of 10 per ray. Thus, it should be relatively quick to render.

## Requirements
g++, make and Python with Numpy, Matplotlib modules.
 
 ## Compile (UNIX/Windows)
```bash
make clean
make all
```

## Run
(Image will be generated as a PPM image, named img/test.ppm by default.).
```bash
./main
```

## Convert image to PNG
```bash
python ppm2png.py img/test.ppm
```

## Project tree
```
.
├── .git/
├── .gitignore
├── benchmark/
│   └── * Generic class to monitor the execution time of a test unit. *
├── img/
│   └── * Rendered images and example images. *
├── inc/
│   └── * C++ header files. *
├── lib/
│   ├── * Directory containing third-party dependencies. *
│   └── stb/ * Only third-party library used. *
├── src/
│   └── * C++ source files. *
├── Makefile * Initialization & compilation flow. *
├── ppm2png.py * Script to convert PPM images to PNG. *
├── triangle.py * Test script to render triangles through ray-tracing. *
├── README.md
└── run.sh * For a timed image rendering. *
```