#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <math.h>

#define FRAME_RATE 60
#define WIN_WIDTH 480
#define WIN_HEIGHT 352

#define MINI_FACTOR 1.0

#define MAP_ROW 11
#define MAP_COLUMN 15
#define BLOCK_SIZE 32

#define PLAYER_SIZE 6

#define CORE_BEGIN() inFrameTime = 1000 / FRAME_RATE

#define CORE_UPDATE() \
{ \
    int wait_time = inFrameTime - (SDL_GetTicks() - lastFrameTime); \
    if (wait_time > 0 && wait_time <= inFrameTime) { \
        SDL_Delay(wait_time); \
    } \
    deltaTime = (SDL_GetTicks() - lastFrameTime) / 1000.0f; \
    lastFrameTime = SDL_GetTicks(); \
}

extern SDL_Window* win;
extern SDL_Renderer* renderer;

void Process_Input();

void Begin();

void Update();

void Render();

float inFrameTime;

static float deltaTime = 0.0f;

bool isRunning;

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

inline void DrawGridMap(SDL_Renderer* renderer, int block_size, float mini_factor, int map_row, int map_column, struct MapGrid* map);
inline void DrawPlayer(SDL_Renderer* renderer, float mini_factor,float pos_x, float pos_y, int width, int height);