#include "Player.h"
#include "Constants.h"
#include "System.h"
#include <SDL2/SDL_image.h>
#include <stdexcept>

namespace cwing {
    Player::Player(
        int x, int y, int w, int h, 
        const std::string& defaultAnimationImagePath, 
        const std::map<std::string, std::string& stateImagePath = {})
    : Character(x, y, w, h, ""), currentState("idle")
    {
        SDL_Texture* defaultAnimationTexture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + defaultAnimationImagePath).c_str());
        if (!defaultAnimationTexture) throw std::runtime_error("Failed to load default image: " + defaultAnimationImagePath);
        animations["idle"].push_back(defaultAnimationTexture);

        for (const auto& [state, paths] : optionalAnimationPaths) {
            for (const std::string& path : paths) {
                SDL_Texture* texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + path).c_str());
                if (!texture) throw std::runtime_error("Failed to load animation frame: " + path);
                animations[state].push_back(texture);
            }
        }
    }

    Player* Player::getInstance(
        int x, int y, int w, int h, 
        const std::string& defaultAnimationImagePath, 
        const std::map<std::string, std::vector<std::string>>& optionalAnimationPaths = {})
    {
        return new Player(x, y, w, h, defaultAnimationImagePath, optionalAnimationPaths);
    }

    void Player::draw() 
    {
        if (!animations.at(currentState).empty()) {
            SDL_Texture* currentTexture = animations.at(currentState)[currentFrame];
            SDL_Rect dest = getRect();
            SDL_RenderCopy(sys.get_ren(), currentTexture, nullptr, &dest);
        }
    }
}