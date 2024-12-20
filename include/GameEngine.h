#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>
#include "Sprite.h"
#include "Background.h"

namespace cwing 
{

	class GameEngine
	{
	public:
		GameEngine();
		void add(Sprite* s);
		void remove(Sprite* s);
		void run();
		void setBackground(Background* newBackground);
		bool checkCollisionBetweenSprites(const Sprite* a, const Sprite* b);
		~GameEngine();
	private:
		std::vector<Sprite*> sprites;
		Background* currentBackground;
	};
}

#endif