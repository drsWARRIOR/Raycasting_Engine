#include <Ray.h>

// Casts all rays for the current frame, spanning the player's FOV
void CastAllRays(struct Player* player, struct Ray rays[], struct MapGrid* map)
{
	// Start ray angle from left edge of FOV, small offset added to avoid division issues
	float rayAngle = player->rotAngle - (FOV_ANGLE / 2) + 0.0001f;

	for (int column = 0; column < NUM_RAYS; column++)
	{
		rays[column].ray_angle = rayAngle;
		rays[column].wall_hit_x = 0;
		rays[column].wall_hit_y = 0;

		// Cast each ray to find its intersection with walls
		CastRay(&rays[column], player, map);

		// Increment angle for next ray to cover entire FOV
		rayAngle += FOV_ANGLE / NUM_RAYS;
	}
}

// Casts a single ray from the player's position to detect wall intersections
void CastRay(struct Ray* ray, struct Player* player, struct MapGrid* map)
{
	// Normalize angle between 0 and 2_PI radians
	ray->ray_angle = NormalAngle(ray->ray_angle);

	// Determine ray direction flags for convenience in intersection calculations
	ray->isRayDown = ray->ray_angle > 0 && ray->ray_angle < SDL_PI_F;
	ray->isRayRight = ray->ray_angle < 0.5 * SDL_PI_F || ray->ray_angle > 1.5 * SDL_PI_F;

	// Variables for intersection points and steps
	float x_intercept;
	float y_intercept;
	float x_step;
	float y_step;

	//////////////////////////////////
	// HORIZONTAL INTERSECTION CHECK //
	////////////////////////////////

	bool h_intersectionDetected = false;
	float wall_hit_hx = 0;
	float wall_hit_hy = 0;

	// Find the first horizontal gridline intersection
	y_intercept = floor(player->y / BLOCK_SIZE) * BLOCK_SIZE;
	y_intercept += ray->isRayDown ? BLOCK_SIZE : 0;
	x_intercept = player->x + ((y_intercept - player->y) / tan(ray->ray_angle));

	// Calculate step increments for subsequent intersections
	y_step = !ray->isRayDown ? -BLOCK_SIZE : BLOCK_SIZE;
	x_step = y_step / tan(ray->ray_angle);

	float nextIntersection_hx = x_intercept;
	float nextIntersection_hy = y_intercept;

	// Adjust intersection slightly to avoid rounding errors when ray faces up
	if (!ray->isRayDown) { nextIntersection_hy -= 0.0001f; }

	// Iterate through horizontal intersections until wall hit or out of bounds
	while (nextIntersection_hx >= 0 && nextIntersection_hx <= WIN_WIDTH && nextIntersection_hy >= 0 && nextIntersection_hy <= WIN_HEIGHT)
	{
		if (IsWallExist(nextIntersection_hx, nextIntersection_hy, map))
		{
			h_intersectionDetected = true;
			wall_hit_hx = nextIntersection_hx;
			wall_hit_hy = nextIntersection_hy;
			break;
		}

		h_intersectionDetected = false;
		nextIntersection_hx += x_step;
		nextIntersection_hy += y_step;
	}

	//////////////////////////////////
	// VERTICAL INTERSECTION CHECK //
	////////////////////////////////

	bool v_intersectionDetected = false;
	float wall_hit_vx = 0;
	float wall_hit_vy = 0;

	// Find the first vertical gridline intersection
	x_intercept = floor(player->x / BLOCK_SIZE) * BLOCK_SIZE;
	x_intercept += ray->isRayRight ? BLOCK_SIZE : 0;
	y_intercept = player->y + ((x_intercept - player->x) * tan(ray->ray_angle));

	// Calculate step increments for vertical intersections
	x_step = !ray->isRayRight ? -BLOCK_SIZE : BLOCK_SIZE;
	y_step = x_step * tan(ray->ray_angle);

	float nextIntersection_vx = x_intercept;
	float nextIntersection_vy = y_intercept;

	// Adjust intersection slightly to avoid rounding errors when ray faces left
	if (!ray->isRayRight) { nextIntersection_vx -= 0.0001f; }

	// Iterate through vertical intersections until wall hit or out of bounds
	while (nextIntersection_vx >= 0 && nextIntersection_vx <= WIN_WIDTH && nextIntersection_vy >= 0 && nextIntersection_vy <= WIN_HEIGHT)
	{
		if (IsWallExist(nextIntersection_vx, nextIntersection_vy, map))
		{
			v_intersectionDetected = true;
			wall_hit_vx = nextIntersection_vx;
			wall_hit_vy = nextIntersection_vy;
			break;
		}

		v_intersectionDetected = false;
		nextIntersection_vx += x_step;
		nextIntersection_vy += y_step;
	}

	// Calculate distances from player to both horizontal and vertical hits
	float h_HitDistance = h_intersectionDetected ? DistanceBetweenTwoPoints(player->x, player->y, wall_hit_hx, wall_hit_hy) : FLT_MAX;
	float v_HitDistance = v_intersectionDetected ? DistanceBetweenTwoPoints(player->x, player->y, wall_hit_vx, wall_hit_vy) : FLT_MAX;

	// Determine closest hit and populate ray data accordingly
	if (h_HitDistance < v_HitDistance)
	{
		ray->ray_distance = h_HitDistance;
		ray->wall_hit_x = wall_hit_hx;
		ray->wall_hit_y = wall_hit_hy;
		ray->isHitVertical = false;
	}
	else
	{
		ray->ray_distance = v_HitDistance;
		ray->wall_hit_x = wall_hit_vx;
		ray->wall_hit_y = wall_hit_vy;
		ray->isHitVertical = true;
	}
}

// Draws all rays on the minimap for visualization (scaled by MINI_FACTOR)
void DrawRays(SDL_Renderer* renderer, struct Player* player, struct Ray rays[])
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	for (int i = 0; i < NUM_RAYS; i++)
	{
		SDL_RenderLine(renderer,
			MINI_FACTOR * player->x,
			MINI_FACTOR * player->y,
			MINI_FACTOR * rays[i].wall_hit_x,
			MINI_FACTOR * rays[i].wall_hit_y);
	}
}

// Draws the 3D vertical wall slices based on ray distances and colors
void DrawWalls(SDL_Renderer* renderer, struct Player* player, struct Ray rays[],
	Uint32* colorBuffer, Uint32 wallColor, Uint32 wallShadeColor, Uint32 floorColor, Uint32 skyColor)
{
	for (int i = 0; i < NUM_RAYS; i++)
	{
		// Correct fisheye effect by using the cosine of the angle difference
		float straightDistance = rays[i].ray_distance * cos(rays[i].ray_angle - player->rotAngle);

		// Calculate projected height of the wall slice on screen
		int wallProjectedHeight = (int)((BLOCK_SIZE / straightDistance) * (WIN_WIDTH / (2 * tan(FOV_ANGLE / 2))));

		// Top pixel of wall slice on screen (centered vertically)
		int aboveWallTop = ((WIN_HEIGHT / 2) - (wallProjectedHeight / 2));
		aboveWallTop = aboveWallTop < 0 ? 0 : aboveWallTop;

		// Bottom pixel of wall slice on screen
		int bottomWallTop = ((WIN_HEIGHT / 2) + (wallProjectedHeight / 2));
		bottomWallTop = bottomWallTop > WIN_HEIGHT ? WIN_HEIGHT : bottomWallTop;

		// Draw sky/ceiling above the wall slice
		for (int j = 0; j < aboveWallTop; j++)
		{
			colorBuffer[(WIN_WIDTH * j) + i] = skyColor;
		}

		// Draw the wall slice, shaded differently for vertical/horizontal hits
		for (int j = aboveWallTop; j < bottomWallTop; j++)
		{
			if (rays[i].isHitVertical)
			{
				colorBuffer[(WIN_WIDTH * j) + i] = wallColor;
			}
			else
			{
				colorBuffer[(WIN_WIDTH * j) + i] = wallShadeColor;
			}
		}

		// Draw floor below the wall slice
		for (int j = bottomWallTop; j < WIN_HEIGHT; j++)
		{
			colorBuffer[(WIN_WIDTH * j) + i] = floorColor;
		}
	}
}
