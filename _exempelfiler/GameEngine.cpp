#include "GameEngine.h"
#include <SDL2/SDL.h>
#include "System.h"
#include <iostream>
#include <algorithm>

namespace cwing 
{
	GameEngine::GameEngine() : currentBackground(nullptr) 
	{
		std::cout << "*** GameEngine::GameEngine()\n";
	}

	void GameEngine::add(Sprite* s) 
	{
		sprites.push_back(s);
	}


	void GameEngine::setBackground(Background* newBackground) {
		// Ta bort nuvarande bakgrund om den finns
		if (currentBackground) {
			auto it = std::find(sprites.begin(), sprites.end(), static_cast<Sprite*>(currentBackground));
			if (it != sprites.end()) {
				sprites.erase(it);
			}
			delete currentBackground; // Frigör minnet för den gamla bakgrunden
		}

		// Sätt den nya bakgrunden som aktiv
		currentBackground = newBackground;
	}

	void GameEngine::run() 
	{
		bool quit = false;
		while (!quit) {
			SDL_Event eve;
			while (SDL_PollEvent(&eve)) {
				switch (eve.type) {
				case SDL_QUIT: quit = true; break;
				case SDL_MOUSEBUTTONDOWN:
					for (Sprite* s : sprites)
						s->mouseDown(eve);
					break;
				case SDL_MOUSEBUTTONUP:
					for (Sprite* s : sprites)
						s->mouseUp(eve);
					break;
				case SDL_KEYDOWN:
					for (Sprite* s : sprites)
						s->keyDown(eve);
					break;
				case SDL_KEYUP:
					for (Sprite* s : sprites)
						s->keyUp(eve);
					break;

				} // switch
			} // inre while
			
			SDL_SetRenderDrawColor(sys.get_ren(), 255, 255, 255, 255);
			SDL_RenderClear(sys.get_ren());

			if (currentBackground) {
				currentBackground->draw();
			}

			for (Sprite* s : sprites)
				s->draw();
			SDL_RenderPresent(sys.get_ren());

		} //yttre while

	}

	GameEngine::~GameEngine()
	{
		for (Sprite* s : sprites) {
			delete s;
		}
	}
}