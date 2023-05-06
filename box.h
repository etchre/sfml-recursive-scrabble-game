//ethan reed
//5-6-23
//box class
#ifndef BOX_H
#define BOX_H

#include <SFML/Graphics.hpp>

class Box {

    public:
        inline static int size = 50;
        Box(
            const sf::Font* font, 
            const char& letter=' ', 
            const int& s=Box::size
        );
        void getLetter();
        sf::CircleShape* getSquare();
    private:
        sf::Text letter;
        sf::CircleShape square;


};

#endif