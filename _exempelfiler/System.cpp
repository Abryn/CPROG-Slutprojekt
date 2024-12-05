#include "Constants.h" //gResPath-contains path to your resources.
#include "System.h"
#include <SDL2/SDL.h>


System::System() {
	SDL_Init(SDL_INIT_EVERYTHING);
	win = SDL_CreateWindow("GameDemo", 10, 10, 700, 500, 0);
	ren = SDL_CreateRenderer(win, -1, 0);
	Mix_OpenAudio(20050, AUDIO_S16SYS, 2, 4096);
	// Path to your own 'sounds' folder!
  	//musik = Mix_LoadWAV("/Users/kjellna/dev/cpp21/f13b/sounds/bgMusic.wav");
	musik = Mix_LoadWAV( (constants::gResPath + "sounds/bgMusic.wav").c_str() );
	Mix_PlayChannel(-1, musik, -1);
}

System::~System() {
	Mix_FreeChunk(musik);
	Mix_CloseAudio();
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
	SDL_Quit();
}

System sys;
