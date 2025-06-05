#pragma once

#include <Globals.h>

// Structure representing a single ray cast in the world
struct Ray
{
	float ray_angle;       // Angle at which the ray is cast
	float wall_hit_x;      // X-coordinate where the ray hits a wall
	float wall_hit_y;      // Y-coordinate where the ray hits a wall
	float ray_distance;    // Distance from the player to the wall hit point

	bool isRayDown;        // True if the ray is facing downward
	bool isRayRight;       // True if the ray is facing right

	bool isHitVertical;    // True if the ray hit a vertical wall (vs horizontal)
};

// Casts a single ray from the player and fills the Ray structure with hit data
void CastRay(struct Ray* ray, struct Player* player, struct MapGrid* map);

// Casts all rays across the screen FOV (Field of View)
void CastAllRays(struct Player* player, struct Ray rays[], struct MapGrid* map);

// Draws the rays from the player to the walls on the minimap
void DrawRays(SDL_Renderer* renderer, struct Player* player, struct Ray rays[]);

// Renders the vertical wall slices to the screen using the ray information
void DrawWalls(SDL_Renderer* renderer, struct Player* player, struct Ray ray[], Uint32* colorBuffer, Uint32 wallColor,Uint32 wallShadeColor, Uint32 floorColor, Uint32 skyColor);