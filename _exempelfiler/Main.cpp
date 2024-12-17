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
    MyPlayer(int x, int y, int w, int h, const std::string& defaultImagePath)
        : Character(x, y, w, h, defaultImagePath) {}

    static MyPlayer* getInstance(int x, int y, int w, int h, const std::string& defaultImagePath) {
        return new MyPlayer(x, y, w, h, defaultImagePath);
    }

    void keyDown(const SDL_Event& event) override {
        switch (event.key.keysym.sym) {
        case SDLK_a:
            if (!chargingJump) {
                movingLeft = true;
            }
            break;
        case SDLK_d:
            if (!chargingJump) {
                movingRight = true;
            }
            break;
        case SDLK_SPACE:
            if (!jumping) {
                chargingJump = true;
            }
            break;
            }
        }
    

    void keyUp(const SDL_Event& event) override {
        switch (event.key.keysym.sym) {
        case SDLK_a:
            movingLeft = false;
            break;
        case SDLK_d:
            movingRight = false;
            break;
       case SDLK_SPACE:
            if (chargingJump) {
                velocityY = -minJumpStrength - (jumpCharge / 2.0f);
                chargingJump = false;
                jumpCharge = 0;
                jumping = true;
            }
            break;
        }
    }

    void update() override {
    const float moveSpeed = 10.0f;
    const float gravity = 0.5f;

    if (!chargingJump) {
        if (movingLeft == movingRight) {
            velocityX = 0.0f;
        } else if (movingLeft) {
            velocityX = -moveSpeed;
        } else {
            velocityX = moveSpeed;
        }
    } else {
        velocityX = 0.0f;
    }

    getRect().x += static_cast<int>(velocityX);

    if (getRect().x < 0) getRect().x = 0;
    if (getRect().x + getRect().w > 1000) getRect().x = 1000 - getRect().w;

    if (chargingJump && jumpCharge < maxJumpCharge) {
        jumpCharge += 0.5f;
        if (jumpCharge >= maxJumpCharge) {
            
            velocityY = -minJumpStrength - (jumpCharge / 2.0f);
            chargingJump = false; 
            jumpCharge = 0;       
            jumping = true;       
        }
    }

    velocityY += gravity;
    getRect().y += static_cast<int>(velocityY);

    if (getRect().y >= groundLevel) {
        getRect().y = groundLevel;
        velocityY = 0.0f;
        jumping = false;
    }

    if (getRect().y < 0) {
        getRect().y = 0;
        velocityY = 0.0f;
    }
}

private:
    bool movingLeft = false;
    bool movingRight = false;
    bool jumping = false;
    bool chargingJump = false;
    float velocityX = 0.0f;
    float velocityY = 0.0f;
    float jumpCharge = 0.0f;
    const float minJumpStrength = 5.0f;
    const float maxJumpCharge = 30.0f;
    int groundLevel = 830;
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
	
	// Platform* p1 = Platform::getInstance(450, 465, 100, 70, "images/platform.png");
	// engine.add(p1);

    MyPlayer* player = MyPlayer::getInstance(450, 200, 76, 64, "images/character_idle.png");
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
