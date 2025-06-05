#include <Core.h>

// Define the game map grid with walls (1) and empty spaces (0)
struct MapGrid map = {
	.grid = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	}
};

// Player struct instance to hold player position, size, rotation, and movement info
struct Player player;

// Time of the last frame, used for frame rate control and delta time calculation
float lastFrameTime = 0;

// Flag to control the main loop, true while the game runs
bool isRunning = true;

// Array to store rays cast each frame (used for raycasting in 3D rendering)
struct Ray rays_arr[NUM_RAYS];

// Pointer to color buffer holding pixels to be rendered on screen
Uint32* colorBuffer = NULL;

// SDL texture that wraps the color buffer for rendering
SDL_Texture* colorBufferTexture = NULL;



// Initialize game state and resources
void Begin()
{
	CORE_BEGIN();  // Set frame duration for target FPS

	printf("Begin function called!!!! \n");

	// Initialize player position in the center or empty space of the map
	PlayerStartPosition(&map, &player);

	player.width = PLAYER_SIZE;
	player.height = PLAYER_SIZE;

	// Initialize input axes to zero (no movement)
	player.horizontalAxis = 0;
	player.verticalAxis = 0;

	// Face player initially to 90 degrees (facing down)
	player.rotAngle = SDL_PI_F / 2;

	// Movement speed in pixels per frame (or per update)
	player.moveVelocity = 3;

	// Angular velocity for rotation (converted from degrees to radians)
	player.angularVelocity = 2 * (SDL_PI_F / 180);

	// Allocate memory for the color buffer (width * height pixels)
	colorBuffer = (Uint32*)malloc(sizeof(Uint32) * WIN_WIDTH * WIN_HEIGHT);

	// Create an SDL texture that uses the color buffer pixels
	colorBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIN_WIDTH, WIN_HEIGHT);
}

// Update game logic every frame
void Update()
{
	CORE_UPDATE(lastFrameTime); // Frame timing and delta time update

	// Update player rotation based on horizontal input axis
	player.rotAngle += player.horizontalAxis * player.angularVelocity;

	// Calculate how far the player moves forward/backward this frame
	float hypoStep = player.verticalAxis * player.moveVelocity;

	// Calculate new proposed player position based on rotation and movement step
	float pos_x = player.x + cos(player.rotAngle) * hypoStep;
	float pos_y = player.y + sin(player.rotAngle) * hypoStep;

	// Check if the new position collides with a wall; if no collision, update player position
	if (IsWallExist(pos_x, pos_y, &map) != 1)
	{
		player.x = pos_x;
		player.y = pos_y;
	}

	// Cast rays from player position for rendering the 3D view
	CastAllRays(&player, rays_arr, &map);
}

// Render all elements every frame
void Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Clear screen with black color
	SDL_RenderClear(renderer);

	// Draw the 3D walls based on rays and player info, write pixels into colorBuffer
	DrawWalls(renderer, &player, rays_arr, colorBuffer, 0xFFFFFFFF, 0xFFCCCCCC, 0xFFF7D26A, 0xFF8AD6F2);

	// Render the color buffer texture on the screen
	RenderColorBuffer(renderer, colorBufferTexture, colorBuffer);

	// Clear the color buffer (set all pixels to black)
	ClearColorBuffer(colorBuffer, 0xFF000000);

	// Draw the 2D grid map on the screen (top-down view)
	DrawGridMap(renderer, BLOCK_SIZE, MINI_FACTOR, MAP_ROW, MAP_COLUMN, &map);

	// Draw rays (lines) from player to walls on 2D map for visualization
	DrawRays(renderer, &player, rays_arr);

	// Draw the player icon on the 2D map
	DrawPlayer(renderer, &player);

	// Present the rendered frame on the screen
	SDL_RenderPresent(renderer);
}

// Handle user input events
void Process_Input()
{
	SDL_Event event;

	SDL_PollEvent(&event);  // Poll one event from the SDL event queue

	if (event.type == SDL_EVENT_QUIT) // SDL3 event constant for quit
	{
		isRunning = false;  // Signal to stop the main loop
	}
	else if (event.type == SDL_EVENT_KEY_DOWN) // Key press event
	{
		// Update movement axes based on arrow key pressed
		if (event.key.key == SDLK_UP) {
			player.verticalAxis = 1;
		}
		else if (event.key.key == SDLK_DOWN) {
			player.verticalAxis = -1;
		}
		else if (event.key.key == SDLK_LEFT) {
			player.horizontalAxis = -1;
		}
		else if (event.key.key == SDLK_RIGHT) {
			player.horizontalAxis = 1;
		}
		else if (event.key.key == SDLK_ESCAPE) {
			isRunning = false;  // Exit on Escape key
		}
	}
	else if (event.type == SDL_EVENT_KEY_UP)  // Key release event
	{
		// Reset movement axes when arrow keys are released
		if (event.key.key == SDLK_UP || event.key.key == SDLK_DOWN) {
			player.verticalAxis = 0;
		}
		if (event.key.key == SDLK_LEFT || event.key.key == SDLK_RIGHT) {
			player.horizontalAxis = 0;
		}
	}
}

// Free allocated resources and destroy SDL objects
void DeleteResources()
{
	DeleteColorBuffer(&colorBuffer);   // Free the color buffer memory
	SDL_DestroyTexture(colorBufferTexture);  // Destroy texture
	SDL_DestroyRenderer(renderer);  // Destroy renderer
	SDL_DestroyWindow(win);         // Destroy window
}
