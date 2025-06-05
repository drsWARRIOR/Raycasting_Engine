#include <Window.h>

// Global window and renderer objects
SDL_Window* win = NULL;
SDL_Renderer* renderer = NULL;

// Initializes SDL, creates a window and renderer, and runs the main loop
void RunWin(const char* title, int width, int height)
{
	// Initialize SDL Video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL not initialized due to error : %s \n", SDL_GetError());
		exit(-1);
	}

	printf("SDL has been initialized!!! \n");

	// Create the main SDL window (centered by default in SDL3)
	win = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);

	if (win == NULL)
	{
		printf("SDL Window has not been initialized properly due to error : %s \n", SDL_GetError());
		SDL_Quit();
		exit(-1);
	}

	// Create a hardware-accelerated renderer linked to the window
	renderer = SDL_CreateRenderer(win, NULL);  // NULL == use default driver and settings

	if (renderer == NULL)
	{
		printf("SDL Renderer has not been initialized properly due to error : %s \n", SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_Quit();
		exit(-1);
	}


	// User-defined setup function for loading textures, game data, etc.
	Begin();

	// Start the main loop
	isRunning = true;
	while (isRunning)
	{
		Process_Input();  // Handles events and input
		Update();         // Game logic update
		Render();         // Render the current frame
	}

	// Free all resources before exiting
	DeleteResources();

	SDL_Quit();

	printf("SDL has been exited \n");

	exit(0);  // Exit the program
}
