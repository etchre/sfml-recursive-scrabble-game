#include <iostream>
#include <fstream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "word.h"
#include "utilities.h"
#include "box.h"
#include "construction.h"

using std::cout;
using std::endl;
using std::vector;

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    sf::RenderWindow window(
        sf::VideoMode(800,600), 
        "word games!",
        sf::Style::Default,
        settings
    );

    ifstream file("../CollinsScrabbleWords_2019.txt");

    file.close();

    sf::Font font;
    if(!font.loadFromFile("../assets/VulfMonoLight.ttf")) {
        return -1;
    }

    sf::Color background_color(58,90,64);

    vector<objects::Box> boxes = construction::constructWord(font, "golf", 200, 50);
    objects::Box* heldBox = nullptr;

    while(window.isOpen()) {
        //cout << "x: " << sf::Mouse::getPosition(window).x << " y: " << sf::Mouse::getPosition(window).y << endl;

        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        if(heldBox) {
            if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                heldBox->focus = false;
                heldBox = nullptr;
            }
        } else {
            for(objects::Box& b: boxes) {
                if(
                    sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                    b.checkMouseClick(sf::Mouse::getPosition(window)) &&
                    !heldBox
                ) {
                    heldBox = &b;
                    heldBox->focus = true;
                }
            }
        }
        

        window.clear(background_color);
        for(objects::Box& b: boxes) {
            b.update(sf::Mouse::getPosition(window));
            if(&b == heldBox) {
                continue;
            }
            b.draw(window);
        }
        if(heldBox) {
            heldBox->draw(window);
        }
        window.display();
    }

    return 0;
}