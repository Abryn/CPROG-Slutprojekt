#include "Constants.h"
#include "Character.h"
#include "System.h"
#include <SDL2/SDL_image.h>

namespace cwing {
    Character::Character(int x, int y, int w, int h, const std::string& imagePath):Sprite(x,y,w,h)
    {
        characterImage = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + imagePath).c_str());
    }

    Character* Character::getInstance(int x, int y, int w, int h, const std::string& imagePath)
    {
        return new Character(x, y, w, h, imagePath);
    }

    void Character::draw() const {
        SDL_RenderCopy(sys.get_ren(), characterImage, NULL, &getRect());
    }

    Character::~Character() 
    {
        SDL_DestroyTexture(characterImage);
    }
}