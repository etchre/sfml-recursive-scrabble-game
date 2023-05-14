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
            inline static float size = 61;
            inline static sf::Color textColor = sf::Color(0,0,0);
            sf::Color squareColor = sf::Color(88,129,87); 
            sf::Text* getLetter();
            char getCharLetter();
            sf::RectangleShape* getSquare();
            void draw(sf::RenderWindow& window) const;
            void update(const sf::Vector2i& mousePos);
            void setPosition(const int& x, const int& y);
            void move(const int& x=0, const int& y=0);
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