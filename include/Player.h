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
                const std::map<std::string, std::string& stateImagePath = {});
            void draw() const;
            void setState(const std::string& state);
        protected:
            Player(
                int x, int y, int w, int h, 
                const std::string& defaultAnimationImagePath,
                const std::map<std::string, std::string& stateImagePath = {});
        private:
            std::map<std::string, SDL_Texture*> stateTextures;
            std::string currentState; // facing left, facing right, jumping, etc
    }
}

#endif