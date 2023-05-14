//ethan reed
//5-6-23
//button class
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

#include <string>
#include <functional>

using std::string;

namespace objects {
    class Button {
        public:
            Button( //button that takes in a lambda function it will run when clicked
                const sf::Font& font,
                const float& x,
                const float& y,
                const std::function<void()>& f,
                const string& str = "",
                const int& size = 32,
                const sf::Color& fillColor = sf::Color(88,129,87),
                const sf::Color& clickColor = sf::Color(163,177,138)
            );
            Button( //button without a function, essentially a text box
                const sf::Font& font,
                const bool& hidden,
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
            void move(const float& x=0.0, const float& y=0.0);
            bool isMouseOver(const sf::Vector2i& mousePos);
            bool clicked = false;
            std::function<void()> clickFunction;
            bool hasFunction = false;
            sf::RectangleShape rect;
            bool hidden = false;
            string text;
            sf::Text hiddenText;
            sf::Color fillColor;

        private:
            inline static sf::Color rectBorderColor = sf::Color(52,58,64);
            sf::Color clickColor;
            sf::Text buttonText;
            inline static sf::Color textColor = sf::Color(0,0,0);
    };
}

#endif