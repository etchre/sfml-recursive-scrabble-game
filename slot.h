//ethan reed
//5-6-23
//slot class
#ifndef SLOT_H
#define SLOT_H

#include "box.h"

namespace objects {

    class Slot {

        public:
            Slot(
                const float& x,
                const float& y
            );
            inline static float size = objects::Box::size + 5;
            inline static sf::Color squareColor = sf::Color(108,117,125);
            inline static sf::Color borderColor = sf::Color(52,58,64);
            sf::RectangleShape* getSquare();
            void draw(sf::RenderWindow& window) const;
            void update();
            void checkOverlap(const sf::Vector2i& mousePos, Box* box);
            bool isMouseOver(const sf::Vector2i& mousePos);
            void setBox(Box* box);
            char getHeldLetter();
            objects::Box* heldBox = nullptr;

        private:
            sf::RectangleShape square;
            
    };

}

#endif