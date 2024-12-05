#include "Constants.h" //gResPath-contains path to your resources.
#include <SDL2/SDL.h>
#include "Session.h"
#include "Component.h"
#include <SDL2/SDL_image.h>
#include "System.h"
#include <string>

/*
*   'gResPath' is a global constant defined in "Constants.h", 
*   representing the relative path to your resource folders as a string,
*   i.e. ' const std::string gResPath = "../../resources/" '
*   Use it through its namespace, 'constants::gResPath'.
*/

Session ses;


class Bullet : public Component {
public:
	static Bullet* getInstance(int x) {
		return new Bullet(x);
	}
	Bullet(int x) : Component(x, 500, 40,40){
		texture = IMG_LoadTexture(sys.ren, (constants::gResPath + "images/dot40x40.bmp").c_str() );
	}
	~Bullet() {
		SDL_DestroyTexture(texture);
	}
	void draw() const {
		// Code adjustment to handle the address to temporary object. 
		const SDL_Rect &rect = getRect();
		//SDL_RenderCopy(sys.ren, texture, NULL, &getRect());
		SDL_RenderCopy(sys.ren, texture, NULL, &rect);
	}
	void tick() {
		counter++;
		if (rect.y <= 0)
			ses.remove(this);
		else if (counter % 10 == 0)
			rect.y--;
	}
private:
	SDL_Texture* texture;
	int counter = 0;
};

class Pistol : public Component {
public:
	Pistol() :Component(0, 0, 0, 0) {}
	void draw() const {}
	void tick() {}
	void mouseDown(int x, int y) {
		Bullet* b = Bullet::getInstance(x);
		ses.add(b);
	}
};

int main(int argc, char** argv) {
	Pistol* pistol = new Pistol();
	ses.add(pistol);
	ses.run();
	
	return 0;
}
