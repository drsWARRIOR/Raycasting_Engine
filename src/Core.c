#include <Core.h>

float lastFrameTime = 0;

float inFrameTime;

struct MapGrid map = {
	.grid = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1},
		{1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	}
};

struct Player player;

void Begin()
{
	inFrameTime = 1000.0f / FRAME_RATE;

	printf("Begin function called!!!! \n");

	player.x = (BLOCK_SIZE * MAP_COLUMN) / 2;
	player.y = (BLOCK_SIZE * MAP_ROW) / 2;
	player.horizontalAxis = 0;
	player.verticalAxis = 0;
	player.rotAngle = M_PI / 2;
	player.moveVelocity = 3;
	player.angularVelocity = 2 * (M_PI / 180);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	for (int i = 0; i < MAP_ROW; i++)
	{
		for (int j = 0; j < MAP_COLUMN; j++)
		{
			int blockX = j * BLOCK_SIZE;
			int blockY = i * BLOCK_SIZE;

			if (map.grid[i][j] == 0) {
				Draw_Rect(renderer, blockX, blockY, BLOCK_SIZE, BLOCK_SIZE, 0, 0, 0, 255);
			}
			else
			{
				Draw_Rect(renderer, blockX, blockY, BLOCK_SIZE, BLOCK_SIZE, 255, 255, 255, 255);
			}
		}
	}

	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);

	for (int i = 0; i <= MAP_COLUMN; i++)
	{
		int x = i * BLOCK_SIZE;
		SDL_RenderDrawLine(renderer, x, 0, x, MAP_ROW * BLOCK_SIZE);
	}

	for (int i = 0; i <= MAP_ROW; i++)
	{
		int y = i * BLOCK_SIZE;
		SDL_RenderDrawLine(renderer, 0, y, MAP_COLUMN * BLOCK_SIZE, y);
	}
	SDL_RenderPresent(renderer);
}

void Update()
{
	CORE_UPDATE();

	printf("x = %d, y = %d \n", player.horizontalAxis, player.verticalAxis);

	player.rotAngle += player.horizontalAxis * player.angularVelocity;

	float hypoStep = player.verticalAxis * player.moveVelocity;

	player.x += cos(player.rotAngle) * hypoStep;
	player.y += sin(player.rotAngle) * hypoStep;

	Draw_Circle_Clear(renderer, player.x, player.y, 5, 255, 0, 0, 255);

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
			player.verticalAxis = -1;
		}
		else if (event.key.keysym.sym == SDLK_DOWN) {
			player.verticalAxis = 1;
		}
		else if (event.key.keysym.sym == SDLK_LEFT) {
			player.horizontalAxis = 1;
		}
		else if (event.key.keysym.sym == SDLK_RIGHT) {
			player.horizontalAxis = -1;
		}
		else if (event.key.keysym.sym == SDLK_ESCAPE) {
			isRunning = false;
		}
	}
	else if (event.type = SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN) {
			player.verticalAxis = 0;
		}
		if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT) {
			player.horizontalAxis = 0;
		}
	}

}