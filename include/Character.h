#ifndef CHARACTER_H
#define CHARACTER_H

#include "Sprite.h"
#include <string>

namespace cwing {
    class Character : public Sprite {
        public:
            static Character* getInstance(int x, int y, int w, int h, const std::string& imagePath);
            void draw();
            virtual void perform(Character* source) {}
            ~Character();
        protected:
            Character(int x, int y, int w, int h, const std::string& imagePath)
        private:
            int x;
            int y;
    }
}