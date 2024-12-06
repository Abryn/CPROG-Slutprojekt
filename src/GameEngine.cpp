#include "GameEngine.h"
#include <SDL2/SDL.h>
#include "System.h"

#include <iostream>

namespace cwing 
{
	GameEngine::GameEngine(){
		std::cout << "*** GameEngine::GameEngine()\n";
	}

	void GameEngine::add(Sprite* s) {
		sprites.push_back(s);
	}

	void GameEngine::run() {
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
			for (Sprite* s : sprites)
				s->draw();
			SDL_RenderPresent(sys.get_ren());

		} //yttre while

	}

	GameEngine::~GameEngine()
	{
	}
}