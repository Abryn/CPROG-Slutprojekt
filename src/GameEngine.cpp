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

	void GameEngine::remove(Sprite* s) 
	{
		auto it = std::find(sprites.begin(), sprites.end(), s);
    
		if (it != sprites.end()) {
			delete *it;
			sprites.erase(it);
		}
	} 


	void GameEngine::setBackground(Background* newBackground) {
		currentBackground = newBackground;
	}

	void GameEngine::run() 
	{
		const int FPS = 60;
		const int frameDelay = 1000 / FPS;

		bool quit = false;
		while (!quit) {
			Uint32 frameStart = SDL_GetTicks();
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

				} 
			} 
			
			SDL_SetRenderDrawColor(sys.get_ren(), 255, 255, 255, 255);
			SDL_RenderClear(sys.get_ren());

			if (currentBackground) {
				currentBackground->draw();
			}

			for (Sprite* s : sprites) {
				s->update();
			}

			for (Sprite* s : sprites)
				s->draw();
			SDL_RenderPresent(sys.get_ren());

			Uint32 frameTime = SDL_GetTicks() - frameStart;
        	if (frameDelay > frameTime) {
            	SDL_Delay(frameDelay - frameTime); 
        	}
		}

	}

	GameEngine::~GameEngine()
	{
		for (Sprite* s : sprites) {
			delete s;
		}
	}
}