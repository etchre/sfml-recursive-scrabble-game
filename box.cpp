#include "box.h"
#include <SFML/Graphics/CircleShape.hpp>

Box::Box(const sf::Font* font, const int& x, const int& y, const char& letter, const int& s) {
    this->square = sf::RectangleShape(sf::Vector2f(Box::size,Box::size));
    this->square.setFillColor(Box::squareColor);
    this->square.setPosition(x,y);
    this->squarePos = &(this->square.getPosition());

    this->letter = sf::Text();
    this->letter.setFont(*font);
    this->letter.setFillColor(Box::textColor);
    this->letter.setString(letter);
    this->letter.setCharacterSize(48);

    sf::FloatRect textBounds = this->letter.getGlobalBounds();
    this->letter.setPosition(
        //squarePos->x + this->letter.getCharacterSize() - 50 + Box::size/2 - 14
        squarePos->x - this->letter.getCharacterSize()/24 + Box::size/2 - textBounds.width/2,
        squarePos->y - this->letter.getCharacterSize() + textBounds.height + (Box::size - textBounds.height)/2
    );
}

sf::RectangleShape* Box::getSquare() {
    return &(this->square);
}

sf::Text* Box::getLetter() {
    return &(this->letter);
}

void Box::draw(sf::RenderWindow* window) {
    window->draw(this->square);
    window->draw(this->letter);
}