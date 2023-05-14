#include "box.h"
#include "slot.h"
#include "button.h"

#include <iostream>

#include <SFML/Graphics.hpp>

//box member definitions
namespace objects {

    //box definitions
    Box::Box(const sf::Font& font, const float& x, const float& y, const char& letter, const float& s) {
        this->square = sf::RectangleShape(sf::Vector2f(Box::size,Box::size));
        //this->square.setFillColor(Box::squareColor);
        this->square.setPosition(x,y);

        this->charLetter = letter;
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

    char Box::getCharLetter() {
        return this->charLetter;
    }

    void Box::draw(sf::RenderWindow& window) const {
        window.draw(this->square);
        //window.draw(this->letter);
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
            this->square.setFillColor(sf::Color(255,255,255));
        }
    }

    void Box::setPosition(const int& x, const int& y) {
        sf::FloatRect textBounds = this->letter.getGlobalBounds();
        this->square.setPosition(x, y);
        this->letter.setPosition(
            //squarePos->x + this->letter.getCharacterSize() - 50 + Box::size/2 - 14
            this->square.getPosition().x - this->letter.getCharacterSize()/24 + Box::size/2 - textBounds.width/2,
            this->square.getPosition().y - this->letter.getCharacterSize() + textBounds.height + (Box::size - textBounds.height)/2
        );
    }

    void Box::move(const int& x, const int& y) {
        this->square.move(x,y);
        this->letter.move(x,y);
    }

    bool Box::checkMouseClick(const sf::Vector2i& mousePos) {
        if(this->square.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            return true;
        } else {
            return false;
        }
    }

    bool Box::isMouseOver(const sf::Vector2i &mousePos) {
        return this->square.getGlobalBounds().contains(mousePos.x, mousePos.y);
    }

}

//slot member definitions
namespace objects {

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
                this->heldBox->setPosition(currPos.x, currPos.y - Slot::size - 5);
                this->heldBox = nullptr;
            }
            this->heldBox = box;
            box->setPosition(this->square.getPosition().x+2.5f, this->square.getPosition().y+2.5f);
        }
    }

    void Slot::move(const float& x, const float& y) {
        this->square.move(x,y);
        if(this->heldBox) {
            this->heldBox->move(x,y);
        }
    }

    bool Slot::isMouseOver(const sf::Vector2i &mousePos) {
        return this->square.getGlobalBounds().contains(mousePos.x, mousePos.y);
    }

    void Slot::setBox(Box* box) {
        this->heldBox = box;
    }

    char Slot::getHeldLetter() {
        if(this->heldBox) {
            return this->heldBox->getCharLetter();
        } else {
            return ' ';
        }
    }

}

//button member defintions
namespace objects {

    Button::Button(
        const sf::Font& font,
        const float& x,
        const float& y,
        const std::function<void()>& f,
        const string& str,
        const int& size,
        const sf::Color& rectColor,
        const sf::Color& clickColor
    ) {
        this->buttonText = sf::Text(str, font, 32);
        this->buttonText.setFillColor(Button::textColor);

        sf::Rect buttonTextRect = this->buttonText.getLocalBounds();
        this->rect = sf::RectangleShape(
            sf::Vector2f(buttonTextRect.width*1.2,buttonTextRect.height*1.5)
        );
        this->rect.setFillColor(rectColor);
        this->rect.setOutlineThickness(2);
        this->rect.setOutlineColor(Button::rectBorderColor);

        this->fillColor = rectColor;
        this->clickColor = clickColor;

        this->hasFunction = true;
        this->clickFunction = f;
        
        this->setPosition(x,y);
    }

    //non function constructor
    Button::Button(
                const sf::Font& font,
                const bool& hidden,
                const float& x,
                const float& y,
                const string& str,
                const int& size,
                const sf::Color& fillColor,
                const sf::Color& clickColor
    ) {
        this->buttonText = sf::Text(str, font, size);
        this->buttonText.setFillColor(Button::textColor);

        sf::Rect buttonTextRect = this->buttonText.getLocalBounds();
        this->rect = sf::RectangleShape(
            sf::Vector2f(buttonTextRect.width*1.2,buttonTextRect.height*1.5)
        );
        this->rect.setFillColor(fillColor);
        this->rect.setOutlineThickness(1);
        this->rect.setOutlineColor(Button::rectBorderColor);

        this->fillColor = fillColor;
        this->clickColor = clickColor;

        this->hidden = hidden;
        this->text = str;

        this->setPosition(x,y);
    };

    void Button::draw(sf::RenderWindow& window) const {
        window.draw(this->rect);
        if(!hidden) {
            window.draw(this->buttonText);
        } else {
            window.draw(this->hiddenText);
        }
    }

    void Button::update() {
        if(clicked) {
            this->rect.setFillColor(this->clickColor);
        } else {
            this->rect.setFillColor(this->fillColor);
        }
    }

    void Button::setPosition(const float& x, const float& y) {
        sf::FloatRect textBounds = this->buttonText.getLocalBounds();
        sf::FloatRect rectBounds = this->rect.getLocalBounds();
        this->rect.setPosition(x, y);
        this->buttonText.setPosition(
            //squarePos->x + this->letter.getCharacterSize() - 50 + Box::size/2 - 14
            this->rect.getPosition().x - this->buttonText.getCharacterSize()/24 + rectBounds.width/2 - textBounds.width/2 - 4,
            this->rect.getPosition().y - this->buttonText.getCharacterSize() + textBounds.height + (rectBounds.height - textBounds.height)/2
        );
        this->hiddenText.setPosition(
            //squarePos->x + this->letter.getCharacterSize() - 50 + Box::size/2 - 14
            this->rect.getPosition().x - this->buttonText.getCharacterSize()/24 + rectBounds.width/2 - textBounds.width/2 - 4,
            this->rect.getPosition().y - this->buttonText.getCharacterSize() + textBounds.height + (rectBounds.height - textBounds.height)/2
        );
    }

    void Button::move(const float& x, const float& y) {
        this->rect.move(x,y);
        this->buttonText.move(x,y);
        this->hiddenText.move(x,y);
    }

    bool Button::isMouseOver(const sf::Vector2i &mousePos) {
        return this->rect.getGlobalBounds().contains(mousePos.x, mousePos.y);
    }
    
}