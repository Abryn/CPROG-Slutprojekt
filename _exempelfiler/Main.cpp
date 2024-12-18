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

int value = 0;

class OkaKnapp : public Button {
public:
	OkaKnapp(Label *lbl, GameEngine* engine) : Button(200, 465, 150, 70, "Oka"), label(lbl), gameEngine(engine) {}
	void perform(Button* source) {
		value++;
		label->setText(to_string(value));

		if (value == 10) {
            Background* bg2 = Background::getInstance("images/background2.png");
            gameEngine->setBackground(bg2);
        }
	}
private:
	Label* label;
	GameEngine* gameEngine;
};

class MinskaKnapp : public Button {
public:
	MinskaKnapp(Label *lbl) :Button(650, 465, 150, 70, "Minska"), label(lbl) {}
	void perform(Button* source) {
		value--;
		label->setText(to_string(value));
	}
private:
	Label* label;
};

class MyPlayer : public Character {
public:
    MyPlayer(int x, int y, int w, int h, const std::string& defaultImagePath, std::vector<Platform*> platforms)
        : Character(x, y, w, h, defaultImagePath), platforms(platforms) {}

    static MyPlayer* getInstance(int x, int y, int w, int h, const std::string& defaultImagePath, std::vector<Platform*> platforms) {
        return new MyPlayer(x, y, w, h, defaultImagePath, platforms);
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
    
    const float gravity = 0.5f;
    const float jumpChargeRate = 0.5f;

    if (chargingJump) {
        jumpCharge += jumpChargeRate;
        if (jumpCharge >= maxJumpCharge) {
            performJump();
        }
    }

    if (movingLeft == movingRight) {
        jumpDirection = 0;
    }

    // Rörelse vänster/höger
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

    // Håll spelaren inom skärmen
    if (getRect().x < 0) getRect().x = 0;
    if (getRect().x + getRect().w > 1000) getRect().x = 1000 - getRect().w;

    velocityY += gravity; 
    getRect().y += static_cast<int>(velocityY);

    // Kontrollera marknivå
    if (getRect().y >= 835) {
        getRect().y = 835;
        velocityY = 0.0f;
        isGrounded = true;
    }

    for (Platform* p : platforms) {
        SDL_Rect* playerRect = &getRect();
        SDL_Rect* platformRect = &p->getRect();

        if (SDL_HasIntersection(playerRect, platformRect)) {
            // Justera spelarens y-position så att den står ovanpå plattformen
            playerRect->y = platformRect->y - playerRect->h;
            velocityY = 0.0f; // Stoppa fallande rörelse
            isGrounded = true;  // Spelaren står på en plattform
            std::cout << "Collision detected!" << std::endl;
            break; // Ingen anledning att kontrollera fler plattformar
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

    int jumpDirection = 0;


    std::vector<Platform*> platforms; // List of platforms for collision checks
};

int main(int argc, char** argv) {
	std::cout << "*** main()\n";
	
	GameEngine engine;

	Background* bg1 = Background::getInstance("images/background1.png");

	engine.setBackground(bg1);
	
	// Label* lbl = Label::getInstance(450, 465, 100, 70, "0");
	// engine.add(lbl);

	// Button* b = new OkaKnapp(lbl, &engine);
	// engine.add(b);
	
	std::vector<Platform*> platforms;
    platforms.push_back(Platform::getInstance(0, 830, 1000, 50, "images/platform.png"));
    platforms.push_back(Platform::getInstance(100, 600, 200, 50, "images/platform.png"));
    platforms.push_back(Platform::getInstance(700, 500, 200, 50, "images/platform.png"));

    for (Platform* p : platforms) {
        engine.add(p);
    }

    MyPlayer* player = MyPlayer::getInstance(450, 200, 76, 64, "images/character_idle.png", platforms);
    engine.add(player);

    if (player->getRect().y + player->getRect().h > 400) {
        Background* bg2 = Background::getInstance("images/background2.png");
        engine.setBackground(bg2);
    } else {
        engine.setBackground(bg1);
    }

	engine.run();
	
	return 0;
}