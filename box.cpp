#include "box.h"
#include <SFML/Graphics/CircleShape.hpp>

Box::Box(const sf::Font* font, const char& letter, const int& s) {
    this->square = sf::CircleShape(s, 4);
    this->square.setPosition(100,50);
    this->square.rotate(45);
    
    this->letter = sf::Text();
    this->letter.setFont(*font);
    this->letter.setFillColor(sf::Color::Green);
    this->letter.setString(letter);
}

sf::CircleShape* Box::getSquare() {
    return &(this->square);
}