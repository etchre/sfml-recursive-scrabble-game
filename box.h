//ethan reed
//5-6-23
//box class
#ifndef BOX_H
#define BOX_H

#include <SFML/Graphics.hpp>

class Box {

    public:
        inline static int size = 50;
        inline static sf::Color squareColor = sf::Color(88,129,87);
        inline static sf::Color textColor = sf::Color(218,215,205);
        Box(
            const sf::Font* font, 
            const int& x,
            const int& y,
            const char& letter=' ', 
            const int& s=Box::size
        );
        sf::Text* getLetter();
        sf::RectangleShape* getSquare();
        void draw(sf::RenderWindow* window);
    private:
        sf::Text letter;
        sf::RectangleShape square;
        const sf::Vector2f* squarePos;


};

#endif