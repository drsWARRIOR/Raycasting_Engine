#pragma once

#include <Ray.h>  // Include raycasting related definitions and functions

// Macro to initialize the desired frame duration based on target frame rate
#define CORE_BEGIN() inFrameTime = 1000 / FRAME_RATE

// Macro to handle frame timing and frame rate limiting
// LastFrameTime is the timestamp of the last frame in milliseconds
#define CORE_UPDATE(LastFrameTime) \
{ \
    int wait_time = inFrameTime - (SDL_GetTicks() - LastFrameTime); /* Calculate remaining time to wait this frame */ \
    if (wait_time > 0 && wait_time <= inFrameTime) { \
        SDL_Delay(wait_time); /* Delay to cap frame rate */ \
    } \
    deltaTime = (SDL_GetTicks() - LastFrameTime) / 1000.0f; /* Calculate delta time in seconds */ \
    LastFrameTime = SDL_GetTicks(); /* Update last frame time for next frame */ \
}

// Target duration of a single frame in milliseconds
float inFrameTime = 0.0f;

// Time elapsed since last frame in seconds, useful for frame-independent movement and animation
static float deltaTime = 0.0f;
