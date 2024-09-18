#pragma once

#include <SDL.h>

static inline void Draw_Rect(SDL_Renderer* renderer, int posX, int posY, int length, int breadth, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_Rect obj = { posX, posY, length, breadth };
	SDL_SetRenderDrawColor(renderer, r, g, b, a);\
	SDL_RenderFillRect(renderer, &obj);
	SDL_RenderPresent(renderer);
}

static inline void Draw_Circle_Clear(SDL_Renderer* renderer, int centerX, int centerY, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	
	int x = radius;
	int y = 0;
	int decisionOver2 = 1 - x;

	//SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	while (y <= x) {
		SDL_RenderDrawLine(renderer, centerX - x, centerY + y, centerX + x, centerY + y);
		SDL_RenderDrawLine(renderer, centerX - x, centerY - y, centerX + x, centerY - y);
		SDL_RenderDrawLine(renderer, centerX - y, centerY + x, centerX + y, centerY + x);
		SDL_RenderDrawLine(renderer, centerX - y, centerY - x, centerX + y, centerY - x);

		y++;
		if (decisionOver2 <= 0) {
			decisionOver2 += 2 * y + 1;
		}
		else {
			x--;
			decisionOver2 += 2 * (y - x) + 1;
		}
	}

	SDL_RenderPresent(renderer);
}