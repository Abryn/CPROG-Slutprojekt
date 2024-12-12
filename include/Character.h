#ifndef CHARACTER_H
#define CHARACTER_H

#include "Sprite.h"
#include <SDL2/SDL.h>
#include <string>

namespace cwing {
    class Character : public Sprite 
    {
        public:
            static Character* getInstance(int x, int y, int w, int h, const std::string& imagePath);
            void draw() const;
            virtual void perform(Character* source) {}
            ~Character();
        protected:
            Character(int x, int y, int w, int h, const std::string& imagePath);
        private:
            SDL_Texture* characterImage;
            int x;
            int y;
    };
}

#endif