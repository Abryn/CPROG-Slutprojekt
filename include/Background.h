#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Sprite.h"
#include <string>
#include <SDL2/SDL.h>

namespace cwing {
    class Background : public Sprite {
    public:
        static Background* getInstance(const std::string& imagePath);
        void draw() const;
        ~Background();
    protected:
        Background(const std::string& imagePath);
    private:
        SDL_Texture* backgroundImage;
    };
}

#endif
