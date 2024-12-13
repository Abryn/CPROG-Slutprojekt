#include "Constants.h"
#include "System.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

namespace cwing 
{

	System::System()
	{
		std::cout << "*** System::System()\n";
		
		SDL_Init(SDL_INIT_EVERYTHING);
		IMG_Init(IMG_INIT_PNG);
		win = SDL_CreateWindow("Cwing", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
		ren = SDL_CreateRenderer(win, -1, 0);
		TTF_Init();
		font = TTF_OpenFont( (constants::gResPath + "fonts/arial.ttf").c_str(), 36);
		std::cout << "resPath: " << constants::gResPath << std::endl;
	}


	System::~System()
	{
		std::cout << "*** System::~System()\n";
		TTF_CloseFont(font);
		TTF_Quit();
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(ren);
		IMG_Quit();
		SDL_Quit();
	}

	SDL_Renderer* System::get_ren() const {
		return ren;
	}

	TTF_Font* System::get_font() const {
		return font;
	}
	
	System sys; // Statiskt globalt objekt (definierad utanför funktioner.)
}