# Raycasting Engine

A simple raycasting engine implementation in C, inspired by the raycasting mechanism of *Wolfenstein 3D*. This project showcases the fundamental logic and algorithms behind early 3D graphics and rendering.

## Contents

- [Overview](#Overview)
- [Buidling Instructions](#Building)
- [Features](#Features)

## Overview

The Raycasting Engine is a 2.5D graphics renderer written in C, built to simulate a 3D perspective with the classic raycasting technique. Inspired by Wolfenstein 3D, it shows how a flat 2D map can be transformed into a pseudo-3D world with the help of basic trigonometry and grid based logic.

This project is built from scratch without any game engine, uses SDL3 for graphics, input, and windowing. It helps in learning about how early 3D engines handled rendering under the hood

## Building Instructions

The project supports Microsoft Windows and Linux

### Windows Building Instructions

Project supports MSVC/Visual Studio and MinGW

 You will need [Git](https://git-scm.com/downloads), [Cmake](https://cmake.org/download/), [Visual Studio](https://visualstudio.microsoft.com/) / [MinGW](https://sourceforge.net/projects/mingw/)

#### MSVC and Visual Studio (Recommended)

1. Clone the repository
``` 
git clone --recurse-submodules https://github.com/drsWARRIOR/Raycasting_Engine.git 
```

2. Create the Folder for building, and build the project in the folder using CMake
``` 
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
```

3. Once the building process is complete, a Visual Studio Solution will be generated. Open the Visual Studio solution file named "Raycasting_Engine.sln"

``` 
.\Raycasting_Engine.sln
```

4. Once the Solution is opened, find the project named as "Raycasting_Engine" in the solution explorer, and right click on it and select the option "Set as Startup Project" from the dropdown menu. This will set the main Raycasting_Engine project as the Startup project

5. Build the solution and run the Project

#### MinGW

1. Clone the repository
```
git clone --recurse-submodules https://github.com/drsWARRIOR/Raycasting_Engine.git 
```

*Note: Make sure that MinGW is installed and properly set in the environment variables*

2. Create the Folder for building, and build the project in the folder using CMake
```
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
```

*Note: Avoid spaces in the project path when building with MinGW, as they may throw an error while building the makefile*

3. Now that the building is completed, you can run the Raycasting_Engine.exe file in the /build/bin/ directory

```
.\bin\Raycasting_Engine.exe
```

### Linux Building Instructions

To build on Linux, you will need git, cmake, gcc, and SDL3 building prerequisites

#### Debian

- Prerequisite installation

1. This command installs GCC, Git, CMake, and all SDL3 building prerequisites
```
sudo apt install build-essential cmake git libx11-dev libgl1-mesa-dev libxext-dev libwayland-dev libdrm-dev libgbm-dev libpulse-dev libudev-dev libasound2-dev libsamplerate0-dev
```
2. Clone the git repository, and open the clone directory
```
git clone --recurse-submodules https://github.com/drsWARRIOR/Raycasting_Engine.git 
cd Raycasting_Engine
```

3. Create the Folder for building, and build the project in the folder using CMake
```
mkdir build
cd build
cmake ..
make
```
4. Now that the building is completed, you can run the Raycasting_Engine file in /build/bin/ directory

```
./bin/Raycasting_Engine
```

## Features

- Grid-Based Map

    ![Image](https://github.com/user-attachments/assets/932750e0-9842-460f-b912-71688b01f81b)

The world is represented as a 2D grid where each cell can either be a wall or empty space. This approach makes the collision detection simple and efficient, level design straightforward

- Player Movement and Control

![Image](https://github.com/user-attachments/assets/1718b259-7be3-43a6-92fe-d71381c87a5b)

Smooth player movement with support for turning, walking forward/backward, Keyboard input is handled via SDL, giving responsive control in real time.

- Wall Rendering via Raycasting

![Image](https://github.com/user-attachments/assets/86c27df6-0187-457f-8758-2e6332765869)

Implements a fundamental raycasting algorithm that casts rays in the direction the player is facing to detect walls. The engine calculates wall distances and renders vertical strips on screen, simulating a 3D perspective from a 2D map.

#### If you want to learn about the raycasting algorithm in detail
Check this article by Liam Wynn https://wynnliam.github.io/raycaster/news/tutorial/2019/03/23/raycaster-part-01.html
