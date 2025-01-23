#pragma once

#include <stdlib.h>
#include <math.h>
#include <Engine.h>

#define CORE_BEGIN() inFrameTime = 1000 / FRAME_RATE

#define CORE_UPDATE(LastFrameTime) \
{ \
    int wait_time = inFrameTime - (SDL_GetTicks() - LastFrameTime); \
    if (wait_time > 0 && wait_time <= inFrameTime) { \
        SDL_Delay(wait_time); \
    } \
    deltaTime = (SDL_GetTicks() - LastFrameTime) / 1000.0f; \
    LastFrameTime = SDL_GetTicks(); \
}

float inFrameTime = 0.0f;

static float deltaTime = 0.0f;


struct MapGrid
{
	int grid[MAP_ROW][MAP_COLUMN];
};

struct Player
{
	float x;
	float y;

	int width;
	int height;

	int horizontalAxis;
	int verticalAxis;

	float rotAngle;
	float moveVelocity;
	float angularVelocity;
};

int IsWallExist(float x, float y);

void DrawGridMap(SDL_Renderer* renderer, int block_size, float mini_factor, int map_row, int map_column, struct MapGrid* map);

void DrawPlayer(SDL_Renderer* renderer, float mini_factor, float pos_x, float pos_y, int width, int height);