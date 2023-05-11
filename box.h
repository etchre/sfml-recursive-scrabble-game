//ethan reed
//5-6-23
//box class
#ifndef BOX_H
#define BOX_H

#include <SFML/Graphics.hpp>
namespace objects {
    class Box {
        public:
            Box(
                const sf::Font& font, 
                const float& x,
                const float& y,
                const char& letter=' ', 
                const float& s=Box::size
            );
            inline static float size = 60;
            inline static sf::Color textColor = sf::Color(218,215,205);
            sf::Color squareColor = sf::Color(88,129,87); 
            sf::Text* getLetter();
            char getCharLetter();
            sf::RectangleShape* getSquare();
            void draw(sf::RenderWindow& window) const;
            void update(const sf::Vector2i& mousePos);
            void setPosition(const float& x, const float& y);
            bool checkMouseClick(const sf::Vector2i& mousePos);
            bool isMouseOver(const sf::Vector2i& mousePos);
            bool focus = false;

        private:
            char charLetter;
            sf::Text letter;
            sf::RectangleShape square;
    };
}

#endif