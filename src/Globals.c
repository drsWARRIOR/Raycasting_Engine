#include <Globals.h>

// Normalize angle between 0 and 2*PI
float NormalAngle(float angle)
{
	angle = remainder(angle, 2 * SDL_PI_F);
	if (angle < 0) { angle += 2 * SDL_PI_F; }
	return angle;
}

// Distance formula between two points in 2D space
float DistanceBetweenTwoPoints(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// Draws the 2D grid minimap
void DrawGridMap(SDL_Renderer* renderer, int block_size, float mini_factor, int map_row, int map_column, struct MapGrid* map)
{
	for (int i = 0; i < map_row; i++)
	{
		for (int j = 0; j < map_column; j++)
		{
			int blockX = j * block_size;
			int blockY = i * block_size;

			//For Drawing Empty Spaces
			if (map->grid[i][j] == 0) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_FRect maptilerect = { mini_factor * blockX, mini_factor * blockY, mini_factor * block_size, mini_factor * block_size };
				SDL_RenderFillRect(renderer, &maptilerect);
			}
			//For Drawing Blocked Spaces
			else
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_FRect maptilerect = { mini_factor * blockX, mini_factor * blockY, mini_factor * block_size, mini_factor * block_size };
				SDL_RenderFillRect(renderer, &maptilerect);
			}
		}
	}


	//To draw Lines
	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);

	for (int i = 0; i <= map_column; i++)
	{
		int x = i * block_size;
		SDL_RenderLine(renderer, x * mini_factor, 0, x * mini_factor, map_row * block_size * mini_factor);
	}

	for (int i = 0; i <= map_row; i++)
	{
		int y = i * block_size;
		SDL_RenderLine(renderer, 0, y * mini_factor, map_column * block_size * mini_factor, y * mini_factor);
	}
}

// Initialize player position in the center or empty space of the map
void PlayerStartPosition(struct MapGrid* map, struct Player* player)
{
	//Set in center if there is empty space
	if (!IsWallExist((BLOCK_SIZE * MAP_COLUMN) / 2, (BLOCK_SIZE * MAP_ROW) / 2, map))
	{
		player->x = (BLOCK_SIZE * MAP_COLUMN) / 2;
		player->y = (BLOCK_SIZE * MAP_ROW) / 2;
		return;
	}

	//Checks for the empty space
	for (int row = 0; row < MAP_ROW; row++)
	{
		for (int col = 0; col < MAP_COLUMN; col++)
		{
			float x = col * BLOCK_SIZE + BLOCK_SIZE / 2;
			float y = row * BLOCK_SIZE + BLOCK_SIZE / 2;

			if (!IsWallExist(x, y, map))
			{
				player->x = x;
				player->y = y;
				return;
			}
		}
	}
}

// Draws the player on the minimap
void DrawPlayer(SDL_Renderer* renderer, struct Player* player)
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // green player

	SDL_FRect player_rect = { MINI_FACTOR * (player->x - 3),MINI_FACTOR * (player->y - 2),MINI_FACTOR * PLAYER_SIZE, MINI_FACTOR * PLAYER_SIZE };

	SDL_RenderFillRect(renderer, &player_rect);
}

// Returns 1 if there's a wall at x, y position
int IsWallExist(float x, float y, struct MapGrid* map)
{
	// Outside world boundaries
	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
		return 1;

	int gridIndexX = floor(x / BLOCK_SIZE);
	int gridIndexY = floor(y / BLOCK_SIZE);

	// Return true if not 0
	return map->grid[gridIndexY][gridIndexX] != 0;
}

// Clears the color buffer with a solid color
void ClearColorBuffer(Uint32* colorBuffer, Uint32 color)
{
	for (int i = 0; i < WIN_WIDTH; i++)
	{
		for (int j = 0; j < WIN_HEIGHT; j++)
		{
			colorBuffer[(j * WIN_WIDTH) + i] = color;
		}
	}
}

// Copies the buffer to the texture and renders it
void RenderColorBuffer(SDL_Renderer* renderer, SDL_Texture* texture, Uint32* colorBuffer)
{
	SDL_UpdateTexture(texture, NULL, colorBuffer, (int)((Uint32)WIN_WIDTH * sizeof(Uint32)));
	SDL_RenderTexture(renderer, texture, NULL, NULL);
}

// Frees the dynamically allocated color buffer memory
void DeleteColorBuffer(Uint32** colorBuffer)
{
	if (*colorBuffer != NULL)
	{
		free(*colorBuffer);
		*colorBuffer = NULL;
	}
}
