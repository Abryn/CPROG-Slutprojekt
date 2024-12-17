#include "Platform.h"
#include "System.h"
#include <SDL2/SDL_image.h>
#include "Constants.h"

namespace cwing {
    Platform::Platform(int x, int y, int w, int h, const std::string& imagePath)
        : Sprite(x, y, w, h) {
        platformImage = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + imagePath).c_str());
    }

    Platform* Platform::getInstance(int x, int y, int w, int h, const std::string& imagePath) {
        return new Platform(x, y, w, h, imagePath);
    }

    void Platform::draw() const {
        SDL_RenderCopy(sys.get_ren(), platformImage, NULL, &getRect());
    }

    bool Platform::checkCollision(SDL_Rect& playerRect) const {
    SDL_Rect platformRect = getRect();

    // Kontrollera om spelaren landar ovanpå plattformen
    bool collisionX = (playerRect.x + playerRect.w > platformRect.x) &&
                      (playerRect.x < platformRect.x + platformRect.w);

    bool collisionY = (playerRect.y + playerRect.h <= platformRect.y) && // Spelaren är ovanför plattformen
                      (playerRect.y + playerRect.h + 5 >= platformRect.y); // Spelaren "landar"

    if (collisionX && collisionY) {
        playerRect.y = platformRect.y - playerRect.h; // Justera spelaren ovanpå plattformen
        return true;
    }
    return false;
}



    Platform::~Platform() {
        SDL_DestroyTexture(platformImage);
    }
}
