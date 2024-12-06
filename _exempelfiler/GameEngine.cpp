#include "GameEngine.h"
#include <SDL2/SDL.h>
#include "Sprite.h"
#include "System.h"

// Hej Hej

using namespace std;

#define FPS 80

void GameEngine::add(Sprite* sprite) {
	added.push_back(sprite);
}

void GameEngine::remove(Sprite* sprite) {
	removed.push_back(sprite);
}

void GameEngine::run() {
	bool quit = false;

	Uint32 tickInterval = 1000 / FPS;
	while (!quit) {
		Uint32 nextTick = SDL_GetTicks() + tickInterval;
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: quit = true; break;
			case SDL_MOUSEBUTTONDOWN:
				for (Sprite* s : sprites)
					s->mouseDown(event.button.x, event.button.y);
				break;
			case SDL_MOUSEBUTTONUP:
				for (Sprite* s : sprites)
					s->mouseUp(event.button.x, event.button.y);
				break;
			} //switch
		} //inre while

		for (Sprite* s : sprites)
			s->tick();

		for (Sprite* s : sprites)
			sprites.push_back(s);
		added.clear();

		for (Sprite* s : removed) {
			for (vector<Sprite*>::iterator i = sprites.begin();
				i != sprites.end();)
			{
				if (*i == s) 
				{
					i = sprites.erase(i);
				}
				else {
					i++;
				}
			}
		}
		removed.clear();

		SDL_SetRenderDrawColor(sys.ren, 255, 255, 255, 255);
		SDL_RenderClear(sys.ren);
		for (Sprite* s : sprites)
			s->draw();
		SDL_RenderPresent(sys.ren);

		int delay = nextTick - SDL_GetTicks();
		if (delay > 0)
			SDL_Delay(delay);
	} // yttre while
}
