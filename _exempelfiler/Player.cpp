#include "Player.h"
#include "Constants.h"
#include "System.h"
#include <SDL2/SDL_image.h>
#include <stdexcept>

namespace cwing {
    Player::Player(
        int x, int y, int w, int h, 
        const std::string& defaultAnimationImagePath,
        const std::map<std::string, std::string>& stateImagePaths) : Character(x, y, w, h, defaultAnimationImagePath) 
    {
        for (const auto& [state, imagePath] : stateImagePaths) {
            stateTextures[state] = IMG_LoadTexture(sys.get_ren(), imagePath.c_str());
        }
        currentState = "default";
    }

    Player* Player::getInstance(
        int x, int y, int w, int h, 
        const std::string& defaultAnimationImagePath, 
        const std::map<std::string, std::string>& optionalStateImagePaths)
    {
        return new Player(x, y, w, h, defaultAnimationImagePath, optionalStateImagePaths);
    }

    void Player::setState(const std::string& state) 
    {
        if (stateTextures.find(state) != stateTextures.end()) {
            currentState = state;
        }
    }

    void Player::draw() const 
    {
        if (stateTextures.find(currentState) != stateTextures.end()) {
            SDL_RenderCopy(sys.get_ren(), stateTextures.at(currentState), NULL, &getRect());
        } else {
            Character::draw();
        }
    }

    void Player::keyDown(const SDL_Event& eve) {
        switch (eve.key.keysym.sym) {
            case SDLK_a:
                movingLeft = true;
                velocityX = -5.0f;
                setState("left");
                break;
            case SDLK_d:
                movingRight = true;
                velocityX = 5.0f;
                setState("right");
                break;
            case SDLK_SPACE:
                if (!jumping) {
                    jumping = true;
                    velocityY = -10.0f;
                }
                break;
            default:
                break;
        }
    }

    void Player::keyUp(const SDL_Event& eve) {
        switch (eve.key.keysym.sym) {
            case SDLK_a: // Stop moving left
                if (movingLeft) {
                    movingLeft = false;
                    velocityX = 0.0f;
                    setState("idle");
                }
                break;
            case SDLK_d: // Stop moving right
                if (movingRight) {
                    movingRight = false;
                    velocityX = 0.0f;
                    setState("idle");
                }
                break;
            case SDLK_SPACE: // Release jump
                // Jump release logic if necessary
                break;
            default:
                break;
        }
    }

    void Player::update() 
    {
        if (movingLeft) {
            velocityX = -5.0f;
        } else if (movingRight) {
            velocityX = 5.0f;
        } else {
            velocityX = 0.0f;
        }

        rect.x += static_cast<int>(velocityX);

        if (jumping) {
            velocityY += gravity;
            rect.y -= static_cast<int>(velocityY);

            if (rect.y >= groundLevel) {
                rect.y = groundLevel;
                jumping = false;
                velocityY = 0.0f;
            }
        }
    }
}