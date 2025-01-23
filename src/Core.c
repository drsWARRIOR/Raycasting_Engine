#include <Core.h>

struct MapGrid map = {
	.grid = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1},
		{1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	}
};

struct Player player;
float lastFrameTime = 0;
bool isRunning = true;

void Begin()
{
	CORE_BEGIN();

	printf("Begin function called!!!! \n");

	player.x = (BLOCK_SIZE * MAP_COLUMN) / 2;
	player.y = (BLOCK_SIZE * MAP_ROW) / 2;
	player.width = PLAYER_SIZE;
	player.height = PLAYER_SIZE;
	player.horizontalAxis = 0;
	player.verticalAxis = 0;
	player.rotAngle = M_PI / 2;
	player.moveVelocity = 3;
	player.angularVelocity = 2 * (M_PI / 180);
}

void Update()
{
	CORE_UPDATE(lastFrameTime);

	printf("x = %d, y = %d \n", player.horizontalAxis, player.verticalAxis);

	player.rotAngle += player.horizontalAxis * player.angularVelocity;

	float hypoStep = player.verticalAxis * player.moveVelocity;

	float pos_x = player.x + cos(player.rotAngle) * hypoStep;
	float pos_y = player.y + sin(player.rotAngle) * hypoStep;

	if (IsWallExist(pos_x, pos_y) != 1)
	{
		player.x = pos_x;
		player.y = pos_y;
	}

}

void Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	DrawGridMap(renderer, BLOCK_SIZE, MINI_FACTOR, MAP_ROW, MAP_COLUMN, &map);
	DrawPlayer(renderer, MINI_FACTOR, player.x, player.y, player.width, player.height);

	SDL_RenderPresent(renderer);
}

void Process_Input()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT)
	{
		isRunning = false;
	}
	else if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_UP) {
			player.verticalAxis = 1;
		}
		else if (event.key.keysym.sym == SDLK_DOWN) {
			player.verticalAxis = -1;
		}
		else if (event.key.keysym.sym == SDLK_LEFT) {
			player.horizontalAxis = -1;
		}
		else if (event.key.keysym.sym == SDLK_RIGHT) {
			player.horizontalAxis = 1;
		}
		else if (event.key.keysym.sym == SDLK_ESCAPE) {
			isRunning = false;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN) {
			player.verticalAxis = 0;
		}
		if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT) {
			player.horizontalAxis = 0;
		}
	}

}

void DrawGridMap(SDL_Renderer* renderer, int block_size, float mini_factor, int map_row, int map_column, struct MapGrid* map)
{
	for (int i = 0; i < map_row; i++)
	{
		for (int j = 0; j < map_column; j++)
		{
			int blockX = j * block_size;
			int blockY = i * block_size;

			if (map->grid[i][j] == 0) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_Rect maptilerect = { mini_factor * blockX, mini_factor * blockY, mini_factor * block_size, mini_factor * block_size };
				SDL_RenderFillRect(renderer, &maptilerect);
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_Rect maptilerect = { blockX, blockY, block_size, block_size };
				SDL_RenderFillRect(renderer, &maptilerect);
			}
		}
	}

	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);

	for (int i = 0; i <= map_column; i++)
	{
		int x = i * block_size;
		SDL_RenderDrawLine(renderer, x, 0, x, map_row * block_size);
	}

	for (int i = 0; i <= map_row; i++)
	{
		int y = i * block_size;
		SDL_RenderDrawLine(renderer, 0, y, map_column * block_size, y);
	}
}

void DrawPlayer(SDL_Renderer* renderer, float mini_factor, float pos_x, float pos_y, int width, int height)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawLine(renderer, player.x * mini_factor, player.y * mini_factor, (player.x + cos(player.rotAngle) * 30) * mini_factor, (player.y + sin(player.rotAngle) * 30) * mini_factor);
}

int IsWallExist(float x, float y)
{
	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
	{
		return 1;
	}

	int gridIndexX = floor(x / BLOCK_SIZE);
	int gridIndexY = floor(y / BLOCK_SIZE);

	return map.grid[gridIndexY][gridIndexX] != 0;
}