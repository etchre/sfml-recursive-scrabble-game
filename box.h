//ethan reed
//5-6-23
//box class
#ifndef BOX_H
#define BOX_H

#include <SFML/Graphics.hpp>
namespace objects {
    class Box {
        public:
            inline static int size = 60;
            sf::Color squareColor = sf::Color(88,129,87); 
            inline static sf::Color textColor = sf::Color(218,215,205);
            Box(
                const sf::Font& font, 
                const int& x,
                const int& y,
                const char& letter=' ', 
                const int& s=Box::size
            );
            sf::Text* getLetter();
            sf::RectangleShape* getSquare();
            void draw(sf::RenderWindow& window) const;
            void update(const sf::Vector2i& mousePos);
            bool checkMouseClick(const sf::Vector2i& mousePos);
            bool focus = false;
        private:
            sf::Text letter;
            sf::RectangleShape square;
    };
}

#endif