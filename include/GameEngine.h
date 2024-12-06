#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>
#include "Sprite.h"

namespace cwing 
{

	class GameEngine
	{
	public:
		GameEngine();
		void add(Sprite* s);
		void run();
		~GameEngine();
	private:
		std::vector<Sprite*> sprites;
	};
}
#endif