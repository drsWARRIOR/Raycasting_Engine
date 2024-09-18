#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>

#define MAP_ROW 11
#define MAP_COLUMN 15

#define BLOCK_SIZE 32

#define CORE_UPDATE() \
{ \
    int wait_time = inFrameTime - (SDL_GetTicks() - lastFrameTime); \
    if (wait_time > 0 && wait_time <= inFrameTime) { \
        SDL_Delay(wait_time); \
    } \
    deltaTime = (SDL_GetTicks() - lastFrameTime) / 1000.0f; \
    lastFrameTime = SDL_GetTicks(); \
}

void Process_Input();

void Begin();

void Update();


static float deltaTime = 0.0f;

bool isRunning;

struct MapGrid
{
	int grid[MAP_ROW][MAP_COLUMN];
};