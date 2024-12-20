/* Följande filer måste finnas i 'src/':
 * Button.cpp, Component.cpp, Label.cpp, f12_main.cpp, enginesion.cpp, System.cpp
 * Följande filer måste finnas i 'include/':
 * Button.h, Component.h, Constants.h, Label.h, enginesion.h, System.h
 */

#include <SDL2/SDL.h>
#include "Label.h"
#include "GameEngine.h"
#include "Button.h"
#include "Character.h"
#include "Platform.h"
#include <string>
#include "Constants.h"
#include "Background.h"
#include <map>

#include <iostream>

/*  PATH TO YOUR RESOURCE FOLDER 'resources'
*   'gResPath' is a global constant defined in "Constants.h", 
*   representing the relative path to your resource folders as a string,
*   i.e. ' const std::string gResPath = "../../resources/" '
*   Use it through its namespace, 'constants::gResPath'.
*
*   If you need to copy your 'resources' folder into directory
*   '/build/debug/', in that case change gResPath="./resources/"
*
*   Change to your own path if you choose a different approach!
*   Absolut Path(Second choice)
*   gResPath = "/Users/kjellna/dev/cpp/sdl2_second/resources/";
*/

using namespace std;
using namespace cwing;

class Bird : public Character {
    public:
        Bird(int x, int y, int w, int h, const std::string& defaultImagePath, float velocityX, const bool looping)
            : Character(x, y, w, h, defaultImagePath), velocityX(velocityX), looping(looping) {}
        
        static Bird* getInstance(int x, int y, int w, int h, const std::string& defaultImagePath, const float velocityX, const bool looping) {
            return new Bird(x, y, w, h, defaultImagePath, velocityX, looping);
        }

        void update() override {
            getRect().x += static_cast<int>(velocityX);

            if (looping) {
                if (getRect().x + getRect().w < 0) {
                    getRect().x = 1000;
                } else if (getRect().x > 1000) {
                    getRect().x = -getRect().w;
                }
            } else {
                if (getRect().x < 0 || getRect().x + getRect().w > 1000) {
                    velocityX = -velocityX;
                }
            }
            
            time += 0.1f;
            getRect().y = getRect().y  + static_cast<int>(5.0f * sin(time));
        }

        
    private:
        float velocityX;
        const bool looping;
        float time;
};

class MyPlayer : public Character {
public:
    MyPlayer(int x, int y, int w, int h, const std::string& defaultImagePath, std::vector<Platform*> platforms,
            std::vector<Bird*> birds, GameEngine* engine, Label* birdsLeftLabel)
        : Character(x, y, w, h, defaultImagePath), platforms(platforms), birds(birds), engine(engine), birdsLeftLabel(birdsLeftLabel) {}

    static MyPlayer* getInstance(int x, int y, int w, int h, const std::string& defaultImagePath, std::vector<Platform*> platforms,
            std::vector<Bird*> birds, GameEngine* engine, Label* birdsLeftLabel) {
        return new MyPlayer(x, y, w, h, defaultImagePath, platforms, birds, engine, birdsLeftLabel);
    }

    void keyDown(const SDL_Event& event) override {
        if (isGrounded) {
            switch (event.key.keysym.sym) {
            case SDLK_a:
                movingLeft = true;
                jumpDirection = -1;
                break;
            case SDLK_d:
                movingRight = true;
                jumpDirection = 1;
                break;
            case SDLK_SPACE:
                if (!chargingJump) {
                    chargingJump = true;
                    velocityX = 0.0f;
                    jumpCharge = 0.0f;
                    break;
                }
            }
        }
    }

    void keyUp(const SDL_Event& event) override {
        if (isGrounded) {
            switch (event.key.keysym.sym) {
            case SDLK_a:
                movingLeft = false;
                break;
            case SDLK_d:
                movingRight = false;
                break;
            case SDLK_SPACE:
                performJump();
                break;
            }
        }
    }

    void update() override {
        if (chargingJump) {
            jumpCharge += jumpChargeRate;
            if (jumpCharge >= maxJumpCharge) {
                performJump();
            }
        }

        if (movingLeft == movingRight) {
            jumpDirection = 0;
        }

        if (!chargingJump && isGrounded) {
            if (movingLeft == movingRight) {
                velocityX = 0.0f;
                jumpDirection = 0;
            } else if (movingLeft) {
                velocityX = -moveSpeed;
            } else {
                velocityX = moveSpeed;
            }
        }

        getRect().x += static_cast<int>(velocityX);

        if (getRect().x + getRect().w < 0) {
            getRect().x = 1000;
        } else if (getRect().x > 1000) {
            getRect().x = -getRect().w;
        }

        velocityY += gravity; 
        getRect().y += static_cast<int>(velocityY);

        if (getRect().y >= 835) {
            getRect().y = 835;
            velocityY = 0.0f;
            isGrounded = true;
        }

        for (Platform* p : platforms) {
            SDL_Rect* platformRect = &p->getRect();

            if (SDL_HasIntersection(playerRect, platformRect)) {
                float deltaLeft = playerRect->x + playerRect->w - platformRect->x;
                float deltaRight = platformRect->x + platformRect->w - playerRect->x;
                float deltaTop = playerRect->y + playerRect->h - platformRect->y;
                float deltaBottom = platformRect->y + platformRect->h - playerRect->y;

                if (deltaLeft > 0 && deltaRight > 0 && deltaTop > 0 && deltaBottom > 0) {
                    if (deltaTop < deltaBottom && deltaTop < deltaLeft && deltaTop < deltaRight) {
                        isGrounded = true;
                        playerRect->y = platformRect->y - playerRect->h;
                        velocityY = 0.0f;
                    } else if (deltaBottom < deltaTop && deltaBottom < deltaLeft && deltaBottom < deltaRight) {
                        playerRect->y = platformRect->y + platformRect->h;
                        velocityY = 0.0f;
                    } else if (deltaLeft < deltaRight && deltaLeft < deltaTop && deltaLeft < deltaBottom) {
                        playerRect->x = platformRect->x - playerRect->w;
                        velocityX = 0.0f;
                    } else if (deltaRight < deltaLeft && deltaRight < deltaTop && deltaRight < deltaBottom) {
                        playerRect->x = platformRect->x + platformRect->w;
                        velocityX = 0.0f;
                    }
                }
            }
        }

        for (auto it = birds.begin(); it != birds.end();) {
            Bird* b = *it;
            SDL_Rect* birdRect = &b->getRect();
            birdsLeft = birds.size();

            if (SDL_HasIntersection(playerRect, birdRect)) {
                engine->remove(b);  
                it = birds.erase(it);
                birdsLeft--;
                birdsLeftLabel->setText(std::to_string(birdsLeft));
                if (birdsLeft == 0) {
                    Label* gameOver = Label::getInstance(100, 300, 800, 400, "Cat wins!");
                    engine->add(gameOver);
                }
            } else {
                ++it; 
            }
        }
    }
    
private:
    void performJump() {
        chargingJump = false;
        isGrounded = false;
        velocityY = -std::max(jumpCharge, minJumpCharge);
        velocityX = moveSpeed * jumpDirection;
        movingLeft = false;
        movingRight = false;
        jumpCharge = 0.0f;
    }

    bool movingLeft = false;
    bool movingRight = false;
    bool chargingJump = false;
    bool isGrounded = true;
    float velocityX = 0.0f;
    float velocityY = 0.0f;
    const float moveSpeed = 5.0f;
    float jumpCharge = 0.0f;
    const float minJumpCharge = 2.5f;
    const float maxJumpCharge = 20.0f;
    const float gravity = 0.5f;
    const float jumpChargeRate = 0.5f;
    int jumpDirection = 0;
    int birdsLeft;
    SDL_Rect* playerRect = &getRect();


    std::vector<Platform*> platforms;
    std::vector<Bird*> birds;
    GameEngine* engine;
    Label* birdsLeftLabel;
};

int main(int argc, char** argv) {
	std::cout << "*** main()\n";
	
	GameEngine engine;

	Background* bg1 = Background::getInstance("images/background1.png");

	engine.setBackground(bg1);
	
	std::vector<Platform*> platforms;
    std::vector<Bird*> birds;
    
    platforms.push_back(Platform::getInstance(50, 760, 200, 50, "images/platform.png"));
    platforms.push_back(Platform::getInstance(750, 500, 200, 50, "images/platform.png"));
    platforms.push_back(Platform::getInstance(500, 300, 200, 50, "images/platform.png"));
    platforms.push_back(Platform::getInstance(350, 200, 100, 50, "images/platform.png"));
    platforms.push_back(Platform::getInstance(200, 150, 100, 50, "images/platform.png"));
    platforms.push_back(Platform::getInstance(50, 100, 100, 50, "images/platform.png"));
    
    for (Platform* p : platforms) {
        engine.add(p);
    }

    birds.push_back(Bird::getInstance(800, 650, 80, 60, "images/bird.png", 10.0f, true));
    birds.push_back(Bird::getInstance(700, 100, 80, 60, "images/bird.png", 2.5f, false));
    birds.push_back(Bird::getInstance(500, 300, 80, 60, "images/bird.png", 5.0f, false));

    
    for (Bird* b : birds) {
        engine.add(b);
    }

    Label* birdsLeftLabel = Label::getInstance(880, 0, 100, 100, std::to_string(birds.size()));
	engine.add(birdsLeftLabel);


    MyPlayer* player = MyPlayer::getInstance(450, 500, 76, 64, "images/character_idle.png", platforms, birds, &engine, birdsLeftLabel);
    engine.add(player);

	engine.run();
	
	return 0;
}