#ifndef PLATFORM_H
#define PLATFORM_H

#include "Sprite.h"
#include <SDL2/SDL.h>
#include <string>

namespace cwing {
    class Platform : public Sprite {
    public:
        static Platform* getInstance(int x, int y, int w, int h, const std::string& imagePath);
        void draw() const override;
        bool checkCollision(SDL_Rect& playerRect, float& velocityY) const;
        ~Platform();
    protected:
        Platform(int x, int y, int w, int h, const std::string& imagePath);
    private:
        SDL_Texture* platformImage;
    };
}

#endif
