#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

#define FRAME_RATE 60
#define WIN_WIDTH 480
#define WIN_HEIGHT 352

#define MINI_FACTOR 1.0

#define MAP_ROW 11
#define MAP_COLUMN 15
#define BLOCK_SIZE 32

#define PLAYER_SIZE 6

extern SDL_Window* win;
extern SDL_Renderer* renderer;

extern bool isRunning;

void Process_Input();

void Begin();

void Update();

void Render();