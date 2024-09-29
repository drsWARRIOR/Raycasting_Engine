#pragma once

#include <Core.h>

SDL_Window* win;
SDL_Renderer* renderer;

void RunWin(const char* title, int posX, int posY, int width, int height);