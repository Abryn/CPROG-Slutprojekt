#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <string>

struct System
{
	System();
	~System();

	SDL_Window* win;
	SDL_Renderer* ren;
	Mix_Chunk* musik;
};

extern System sys;

#endif
