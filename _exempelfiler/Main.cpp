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
            gameEngine->setBackground(bg2);  // Change background to bg2
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
            movingLeft = true;
            break;
        case SDLK_d:
            movingRight = true;
            break;
        case SDLK_SPACE:
            if (velocityY == 0.0f && !jumping) {  // Only jump if on the ground and not already jumping
                jumping = true;
                velocityY = jumpStrength;  // Apply initial jump force
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
            // Reset jumping flag when the spacebar is released
            jumping = false;
            break;
        }
    }

    void update() override {
        const float moveSpeed = 10.0f;
        const float gravity = 0.5f;   // Gravity strength

        // Update horizontal movement (left/right)
        if (movingLeft) {
            velocityX = -moveSpeed;
        } else if (movingRight) {
            velocityX = moveSpeed;
        } else {
            velocityX = 0.0f;
        }

        getRect().x += static_cast<int>(velocityX);

        // Apply gravity only when in the air (not on the ground)
        if (getRect().y < groundLevel) {
            velocityY += gravity;  // Gravity pulls the player down when in the air
        }

        // Update the vertical position (Y-axis)
        getRect().y += static_cast<int>(velocityY);

        // Check if the player has landed on the ground
        if (getRect().y >= groundLevel) {
            getRect().y = groundLevel;
            velocityY = 0.0f; // Reset vertical velocity (no more falling)
            jumping = false;  // Reset the jumping flag when the player is on the ground
        }
    }

private:
    bool movingLeft = false;
    bool movingRight = false;
    bool jumping = false;
    float velocityX = 0.0f;
    float velocityY = 0.0f;
    float jumpStrength = -10.0f; // Strength of the jump
    int groundLevel = 830; // Y-coordinate where the ground level is located
};

int main(int argc, char** argv) {
	std::cout << "*** main()\n";
	
	GameEngine engine;

	Background* bg1 = Background::getInstance("images/background1.png");

	engine.setBackground(bg1);
	
	Label* lbl = Label::getInstance(450, 465, 100, 70, "0");
	engine.add(lbl);

	Button* b = new OkaKnapp(lbl, &engine);
	engine.add(b);
	
	// Platform* p1 = Platform::getInstance(450, 465, 100, 70, "images/platform.png");
	// engine.add(p1);

	//Character* c1 = Character::getInstance(450, 700, 76, 64, "images/character_right.png");
	//engine.add(c1);

	MyPlayer* player = MyPlayer::getInstance(450, 200, 76, 64, "images/character_idle.png");
    engine.add(player);

	engine.run();
	
	return 0;
}
