//ethan reed
//5-6-23
//button class
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

#include <string>

using std::string;

namespace objects {
    class Button {
        public:
            Button(
                const sf::Font& font,
                const float& x,
                const float& y,
                const string& str = "",
                const int& size = 32,
                const sf::Color& fillColor = sf::Color(88,129,87),
                const sf::Color& clickColor = sf::Color(163,177,138)
            );
            void draw(sf::RenderWindow& window) const;
            void update();
            void setPosition(const float& x, const float& y);
            bool isMouseOver(const sf::Vector2i& mousePos);
            bool clicked = false;

        private:
            sf::RectangleShape rect;
            inline static sf::Color rectBorderColor = sf::Color(52,58,64);
            sf::Color fillColor;
            sf::Color clickColor;
            sf::Text buttonText;
            inline static sf::Color textColor = sf::Color(218,215,205);
    };
}

#endif