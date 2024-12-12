#include "Background.h"
#include "System.h"
#include "Constants.h"
#include <SDL2/SDL_image.h>

namespace cwing {
    Background::Background(const std::string& imagePath) 
        : Sprite(0, 0, 1000, 1000)
    {
        backgroundImage = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + imagePath).c_str());
    }

    Background* Background::getInstance(const std::string& imagePath) 
    {
		return new Background(imagePath);
	}

    void Background::draw() const 
    {
        SDL_RenderCopy(sys.get_ren(), backgroundImage, NULL, &getRect());
    }

    Background::~Background() 
    {
        SDL_DestroyTexture(backgroundImage);
    }
}
