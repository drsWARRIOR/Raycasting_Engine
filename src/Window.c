#include <Window.h>

SDL_Window* win = NULL;
SDL_Renderer* renderer = NULL;

void RunWin(const char* title, int posX, int posY, int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL not initialized due to error : %s \n", SDL_GetError());

		exit(-1);
	}

	printf("SDL has been initialized!!! \n");

	win = SDL_CreateWindow(title, posX, posY, width, height, SDL_WINDOW_SHOWN);

	if (win == NULL)
	{
		printf("SDL Window has not been initialized properly due to error : %s \n", SDL_GetError());
		SDL_Quit();
		exit(-1);
	}

	renderer = SDL_CreateRenderer(win, -1, 0);

	if (renderer == NULL)
	{
		printf("SDL Renderer has not been initialized properly due to error : %s \n", SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_Quit();
		exit(-1);
	}

	Begin();

	isRunning = true;

	while (isRunning)
	{
		Process_Input();
		Update();
		Render();
	}

	SDL_DestroyWindow(win);

	SDL_Quit();

	printf("SDL has been exited \n");

	exit(0);
}