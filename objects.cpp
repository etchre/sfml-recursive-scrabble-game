#include "box.h"
#include "slot.h"

#include <iostream>

#include <SFML/Graphics.hpp>

namespace objects {

    //box definitions
    Box::Box(const sf::Font& font, const float& x, const float& y, const char& letter, const float& s) {
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
            this->setPosition(mousePos.x-(Box::size/2), mousePos.y-(Box::size/2));
            sf::Vector2 currPos = this->square.getPosition();
            if(currPos.x <= 0) {
                this->setPosition(0, currPos.y);
            } else if(currPos.x >= 800-objects::Box::size) {
                this->setPosition(800-objects::Box::size, currPos.y);
            }
            currPos = this->square.getPosition();
            if(currPos.y <= 0) {
                this->setPosition(currPos.x, 0);
            } else if(currPos.y >= 600-objects::Box::size) {
                this->setPosition(currPos.x, 600-objects::Box::size);
            }
            this->square.setFillColor(sf::Color(163, 177, 138));
        } else {
            this->square.setFillColor(sf::Color(88,129,87));
        }
    }

    void Box::setPosition(const float& x, const float& y) {
        sf::FloatRect textBounds = this->letter.getGlobalBounds();
        this->square.setPosition(x, y);
        this->letter.setPosition(
            //squarePos->x + this->letter.getCharacterSize() - 50 + Box::size/2 - 14
            this->square.getPosition().x - this->letter.getCharacterSize()/24 + Box::size/2 - textBounds.width/2,
            this->square.getPosition().y - this->letter.getCharacterSize() + textBounds.height + (Box::size - textBounds.height)/2
        );
    }

    bool Box::checkMouseClick(const sf::Vector2i& mousePos) {
        if(this->square.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            return true;
        } else {
            return false;
        }
    }

    Slot::Slot(const float& x, const float& y) {
        this->square = sf::RectangleShape(sf::Vector2f(Slot::size, Slot::size));
        this->square.setPosition(x,y);
        this->square.setFillColor(Slot::squareColor);
        this->square.setOutlineThickness(5);
        this->square.setOutlineColor(Slot::borderColor);
    }

    sf::RectangleShape* Slot::getSquare() {
        return &(this->square);
    }

    void Slot::draw(sf::RenderWindow& window) const {
        window.draw(this->square);
    }

    void Slot::update() {
        if(this->heldBox) {
            // std::cout << "slot= left: " << this->square.getGlobalBounds().left << 
            //             " top: " << this->square.getGlobalBounds().top << 
            //             " width: " << this->square.getGlobalBounds().width << 
            //             " height: " << this->square.getGlobalBounds().height << std::endl;
            // std::cout << "heldBox= left: " << heldBox->getSquare()->getGlobalBounds().left << 
            //             " top: " << heldBox->getSquare()->getGlobalBounds().top << 
            //             " width: " << heldBox->getSquare()->getGlobalBounds().width << 
            //             " height: " << heldBox->getSquare()->getGlobalBounds().height << std::endl;
            if(!(this->square.getGlobalBounds().intersects(heldBox->getSquare()->getGlobalBounds()))) {
                this->heldBox = nullptr;
            }
        } 
    }

    void Slot::checkOverlap(const sf::Vector2i& mousePos, Box* box) {
        if(box == nullptr) {
            return;
        }
        if(this->square.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            if(this->heldBox) {
                sf::Vector2 currPos = this->heldBox->getSquare()->getPosition();
                this->heldBox->setPosition(currPos.x, currPos.y - Slot::size);
                this->heldBox = nullptr;
            }
            this->heldBox = box;
            box->setPosition(this->square.getPosition().x+2.5f, this->square.getPosition().y+2.5f);
        } 
    }

    void Slot::setBox(Box* box) {
        this->heldBox = box;
    }

}