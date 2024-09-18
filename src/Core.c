#include <Core.h>

int frameRate = 60;

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


void Begin()
{
	inFrameTime = 1000.0f / frameRate;

	printf("Begin function called!!!! \n");
}

void Update()
{
	CORE_UPDATE();

	printf("Msg \n");

}

/*
void Core_Update()
{
	int wait_time = inFrameTime - (SDL_GetTicks() - lastFrameTime);

	if (wait_time > 0 && wait_time <= inFrameTime)
	{
		SDL_Delay(wait_time);
	}

	deltaTime = (SDL_GetTicks() - lastFrameTime) / 1000.0f;

	lastFrameTime = SDL_GetTicks();
}*/

void Process_Input()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT)
	{
		isRunning = false;
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
	{
		isRunning = false;
	}
}