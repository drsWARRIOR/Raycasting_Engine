#pragma once

// Standard Libraries
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

// SDL3
#include <SDL3/SDL.h>

// === Application Constants ===

#define FRAME_RATE 60                  // Target frames per second
#define WIN_WIDTH 1024                // Window width in pixels
#define WIN_HEIGHT 720                // Window height in pixels

#define MINI_FACTOR 0.5               // Scale-down factor for minimap

#define MAP_ROW 11                    // Number of map rows
#define MAP_COLUMN 15                 // Number of map columns
#define BLOCK_SIZE 32                 // Size of each block in pixels
#define WALL_STRIP_THICKNESS 1       // Width of each vertical slice (ray)

#define FOV 60                        // Field of view in degrees
#define FOV_ANGLE (FOV * (SDL_PI_F / 180.0))  // FOV in radians

#define NUM_RAYS (WIN_WIDTH / WALL_STRIP_THICKNESS)  // Number of rays to cast

#define PLAYER_SIZE 6                // Size of the player in pixels (for minimap rendering)


// === Global Variables ===

extern SDL_Window* win;              // Pointer to SDL window
extern SDL_Renderer* renderer;       // Pointer to SDL renderer

extern bool isRunning;               // Main loop control flag


// === Game Structs ===

// 2D Grid map representation
struct MapGrid
{
	int grid[MAP_ROW][MAP_COLUMN];  // 2D array of integers representing walls (1) and space (0)
};

// Player object
struct Player
{
	float x, y;                      // Player's position in the world
	int width, height;              // Player's visual size (for minimap or collision)
	int horizontalAxis;             // Input axis (left/right): -1, 0, 1
	int verticalAxis;               // Input axis (up/down): -1, 0, 1
	float rotAngle;                 // Player's facing angle (radians)
	float moveVelocity;            // Speed of movement
	float angularVelocity;         // Speed of rotation
};


// === Engine Lifecycle Functions ===

void Process_Input();               // Handles keyboard or mouse input
void Begin();                       // Initializes game state (e.g., player, map, textures)
void Update();                      // Updates all game logic
void Render();                      // Renders the current frame
void DeleteResources();            // Cleans up resources (textures, buffers, etc.)


// === Math Utility Functions ===

float NormalAngle(float angle);     // Keeps angle within 0 to 2*PI
float DistanceBetweenTwoPoints(float x1, float y1, float x2, float y2);


// === Map & Player Rendering ===

int IsWallExist(float x, float y, struct MapGrid* map);  // Checks collision in the map grid
void PlayerStartPosition(struct MapGrid* map, struct Player* player);// Initialize player position in the center or empty space of the map
void DrawGridMap(SDL_Renderer* renderer, int block_size, float mini_factor, int map_row, int map_column, struct MapGrid* map);  // Renders the 2D grid map (minimap)
void DrawPlayer(SDL_Renderer* renderer, struct Player* player);  // Renders the player in the minimap


// === Color Buffer Functions (Raycasting Output) ===

void DeleteColorBuffer(Uint32** colorBuffer);  // Frees memory allocated to color buffer
void RenderColorBuffer(SDL_Renderer* renderer, SDL_Texture* texture, Uint32* colorBuffer);  // Uploads buffer to texture and renders
void ClearColorBuffer(Uint32* colorBuffer, Uint32 color);  // Clears buffer with a given color
