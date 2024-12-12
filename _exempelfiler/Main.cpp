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

	Character* c1 = Character::getInstance(450, 700, 76, 64, "images/character_right.png");
	engine.add(c1);

	engine.run();
	
	return 0;
}
