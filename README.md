
# Raycasting Engine

A simple raycasting engine implementation in C, inspired by the raycasting mechanism of *Wolfenstein 3D*. This project showcase the fundamental logic and algoriths behind early 3D graphics and rendering.

## Contents

- [Overview](#Overview)
- [Buidling Instructions](#Building_Instructions)
- [Features](#Features)

## Overview

The Raycasting Engine is a 2.5D graphics renderer written in C, built to simulate a 3D perpective with classic raycasting technique. Inspired by Wolfenstein 3D, it shows how a flat 2D map can be transformed into pseudo 3D world with the help of basic trignometry and grid based logic.

This project is built from scracth without any game engine, uses SDL3 for graphics, input, and windowing. It helps in learning about how early 3D engines handled rendering under the hood

## Building_Instructions

The project supports Microsoft Windows, and Linux

### Windows Buidling Instructions

Project supports MSVC/Visual Studio and MinGW

 You will need [Git](https://git-scm.com/downloads), [Cmake](https://cmake.org/download/), [Visual Studio](https://visualstudio.microsoft.com/) / [MinGW](https://sourceforge.net/projects/mingw/)

#### MSVC and Visual Studio (Recommended)

1. Clone the repository
``` 
git clone --recurse-submodules https://github.com/drsWARRIOR/Raycasting_Engine.git 
```

2. Create the Folder for Buidling, and build the project in the folder using cmake
``` 
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
```

3. Once building process is complete, a Visual Studio Solution will be generated. Open the visual studio solution file named as "Raycasting_Engine.sln"

``` 
.\Raycasting_Engine.sln

```

4. Once the Solution is opened, find the project named as "Raycasting_Engine" in the solution explorer, and right click on it and select the option "Set as Startup Project" from the dropdown menu, this will set the the main Raycasting_Engine project as Startup project

5. Build the solution and Run the Project

#### MinGW

1. Clone the repository
```
git clone --recurse-submodules https://github.com/drsWARRIOR/Raycasting_Engine.git 
```

*Note: Makesure that the MinGW is installed and properly set in enviroment variables*

2. Create the Folder for Buidling, and build the project in the folder using cmake
```
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
```

*Note: Avoid spaces in the project path when building with MinGW, as they may throw error while building makefile*

3. Now building is completed, you can run the Raycasting_Engine.exe file in /build/bin/ directory

```
.\bin\Raycasting_Engine.exe
```

### Linux Buidling Instructions

To build on linux you will need git, cmake, gcc and SDL3 building prerequisites

#### Debian

- Prerequisite installation

1. This command install GCC, Git, Cmake and all SDL3 building prerequisites
```
sudo apt install build-essential cmake git libx11-dev libgl1-mesa-dev libxext-dev libwayland-dev libdrm-dev libgbm-dev libpulse-dev libudev-dev libasound2-dev libsamplerate0-dev
```
2. Clone the git repository, and open the clone directory
```
git clone --recurse-submodules https://github.com/drsWARRIOR/Raycasting_Engine.git 
cd Raycasting_Engine
```

3. Create the Folder for Buidling, and build the project in the folder using cmake
```
mkdir build
cd build
cmake ..
make
```
4. Now building is completed, you can run the Raycasting_Engine.exe file in /build/bin/ directory

```
./bin/Raycasting_Engine
```

## Features

- Grid-Based Map

    ![Image](https://github.com/user-attachments/assets/932750e0-9842-460f-b912-71688b01f81b)

The world represented as 2D grid where each cell can either be wall or empty space. This approach makes the collision detection simple and efficient, level design straightforward

- Player Movement and Control

![Image](https://github.com/user-attachments/assets/1718b259-7be3-43a6-92fe-d71381c87a5b)

Smooth player movement with support for turning, walking forward/backward,Keyboard input is handled via SDL, giving responsive control in real time.

- Wall Rendering via Raycasting

![Image](https://github.com/user-attachments/assets/86c27df6-0187-457f-8758-2e6332765869)

Implements a fundamental raycasting algorithm that casts rays in the direction the player is facing to detect walls. The engine calculates wall distances and renders vertical strips on screen, simulating a 3D perspective from a 2D map.

