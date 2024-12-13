#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <string>
#include <map>
#include <SDL2/SDL.h>

namespace cwing {
    class Player : public Character 
    {
        public:
            static Player* getInstance(
                int x, int y, int w, int h, 
                const std::string& defaultAnimationImagePath, 
                const std::map<std::string, std::string>& optionalStateImagePaths = {}
            );
            void draw() const override;
            void setState(const std::string& state);
            void keyDown(const SDL_Event& eve) override;
            void keyUp(const SDL_Event& eve) override;
            void update() override;
            int getX() const { return x; } 
            int getY() const { return y; }
            
        protected:
            Player(
                int x, int y, int w, int h, 
                const std::string& defaultAnimationImagePath,
                const std::map<std::string, std::string>& optionalStateImagePaths = {}
            );
        private:
            std::map<std::string, SDL_Texture*> stateTextures;
            std::string currentState; // ex: "left", "right", "jumping"
            bool movingLeft = false;
            bool movingRight = false;
            bool jumping = false;
            float velocityX = 0.0f;
            float velocityY = 0.0f;
            float gravity = 0.5f;
            int groundLevel = 700;
    };
}

#endif
