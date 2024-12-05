#ifndef SPRITE_H
#define SPRITE_H
#include <SDL2/SDL.h>

class Sprite
{
public:
	virtual ~Sprite();
	virtual void mouseDown(const SDL_Event&) {}
	virtual void mouseUp(const SDL_Event&) {}
	virtual void keyDown(const SDL_Event&) {}
	virtual void keyUp(const SDL_Event&) {}
	virtual void draw() const = 0;
	const SDL_Rect& getRect() const { return rect; }
protected:
	Sprite(int x, int y, int w, int h);
private:
	SDL_Rect rect;
	Sprite(const Sprite&) = delete;
	const Sprite& operator=(const Sprite&) = delete;
};

#endif
