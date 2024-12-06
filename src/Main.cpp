/* Följande filer måste finnas i 'src/':
 * Button.cpp, Component.cpp, Label.cpp, f12_main.cpp, enginesion.cpp, System.cpp
 * Följande filer måste finnas i 'include/':
 * Button.h, Component.h, Constants.h, Label.h, enginesion.h, System.h
 */

#include <SDL2/SDL.h>
#include "Label.h"
#include "GameEngine.h"
#include "Button.h"
#include <string>

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
	OkaKnapp(Label *lbl) :Button(100, 100, 150, 70, "Oka"), label(lbl) {}
	void perform(Button* source) {
		value++;
		label->setText(to_string(value));
	}
private:
	Label* label;
};


class MinskaKnapp : public Button {
public:
	MinskaKnapp(Label *lbl) :Button(400, 100, 150, 70, "Minska"), label(lbl) {}
	void perform(Button* source) {
		value--;
		label->setText(to_string(value));
	}
private:
	Label* label;
};

class Character : public Sprite {
	public:
	private:
	//move
	//jump
	//tick

};

class Entity : public Sprite {
	public:
	private:
	//move
	//tick

};

int main(int argc, char** argv) {
	std::cout << "*** main()\n";

	GameEngine engine;
	
	Label* lbl = Label::getInstance(270, 100, 100, 70, "0");
	engine.add(lbl);
	Button* b = new OkaKnapp(lbl);
	engine.add(b);
	Button* b2 = new MinskaKnapp(lbl);
	engine.add(b2);
	engine.run();
	
	
	return 0;
}
