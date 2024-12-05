#ifndef SPRITE_H
#define SPRITE_H
#include <SDL2/SDL.h>

class Sprite
{
public:
	virtual void mouseDown(int x, int y) {}
	virtual void mouseUp(int x, int y) {}
	virtual void draw() const = 0;
	SDL_Rect getRect() const { return rect; }
	virtual void tick() = 0;
protected:
	Sprite(int x, int y, int w, int h) : rect{ x,y,w,h } {}
	SDL_Rect rect;
};

#endif
