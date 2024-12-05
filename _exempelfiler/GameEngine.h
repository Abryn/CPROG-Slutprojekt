#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Sprite.h"
#include <vector>

class GameEngine
{
public:
	void add(Sprite* sprite);
	void remove(Sprite* sprite);
	void run();

private:
	std::vector<Sprite*> sprite;
	std::vector<Sprite*> added, removed;
};

#endif