#include "Constants.h"
#include "Platform.h"
#include "System.h"
#include <SDL2/SDL_image.h>

namespace cwing 
{
    Platform::Platform(int x, int y, int w, int h, const std::string& imagePath): Sprite(x, y, w, h)
    {
        platformImage = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + imagePath).c_str());
    }

    Platform* Platform::getInstance(int x, int y, int w, int h, const std::string& imagePath) 
    {
		return new Platform(x, y, w, h, imagePath);
	}

    void Platform::draw() const 
    {
        SDL_RenderCopy(sys.get_ren(), platformImage, NULL, &getRect());
    }

    Platform::~Platform() 
    {
        SDL_DestroyTexture(platformImage);
    }

}
