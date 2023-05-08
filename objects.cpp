#include "box.h"

namespace objects {
    Box::Box(const sf::Font& font, const int& x, const int& y, const char& letter, const int& s) {
        this->square = sf::RectangleShape(sf::Vector2f(Box::size,Box::size));
        this->square.setFillColor(Box::squareColor);
        this->square.setPosition(x,y);

        this->letter = sf::Text();
        this->letter.setFont(font);
        this->letter.setFillColor(Box::textColor);
        this->letter.setString(letter);
        this->letter.setCharacterSize(48);

        sf::FloatRect textBounds = this->letter.getGlobalBounds();
        sf::Vector2f squarePos = this->square.getPosition();
        this->letter.setPosition(
            //squarePos->x + this->letter.getCharacterSize() - 50 + Box::size/2 - 14
            squarePos.x - this->letter.getCharacterSize()/24 + Box::size/2 - textBounds.width/2,
            squarePos.y - this->letter.getCharacterSize() + textBounds.height + (Box::size - textBounds.height)/2
        );
    }

    sf::RectangleShape* Box::getSquare() {
        return &(this->square);
    }

    sf::Text* Box::getLetter() {
        return &(this->letter);
    }

    void Box::draw(sf::RenderWindow& window) const {
        window.draw(this->square);
        window.draw(this->letter);
    }

    void Box::update(const sf::Vector2i& mousePos) {
        if(this->focus) {
            sf::FloatRect textBounds = this->letter.getGlobalBounds();
            this->square.setPosition(mousePos.x, mousePos.y);
            this->letter.setPosition(
                //squarePos->x + this->letter.getCharacterSize() - 50 + Box::size/2 - 14
                this->square.getPosition().x - this->letter.getCharacterSize()/24 + Box::size/2 - textBounds.width/2,
                this->square.getPosition().y - this->letter.getCharacterSize() + textBounds.height + (Box::size - textBounds.height)/2
            );
            this->square.setFillColor(sf::Color(163, 177, 138));
        } else {
            this->square.setFillColor(sf::Color(88,129,87));
        }
    }

    bool Box::checkMouseClick(const sf::Vector2i& mousePos) {
        if(this->square.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            return true;
        } else {
            return false;
        }
    }
}