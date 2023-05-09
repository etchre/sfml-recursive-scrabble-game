#include <iostream>
#include <fstream>
#include <vector>
#include <list>

#include <SFML/Graphics.hpp>

#include "word.h"
#include "utilities.h"
#include "objects.h"
#include "construction.h"

using std::cout;
using std::endl;
using std::vector;
using std::list;

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

    vector<objects::Box> boxes;
    list<objects::Slot> slots;
    construction::constructWord(font, "golf", 250, 200, boxes, slots);

    // std::cout << "boxes from main" << std::endl;

    // for(objects::Box& b : boxes) {
    //     cout << &b << endl;
    // }

    // std::cout << "slots from main" << std::endl;

    // for(objects::Slot& s : slots) {
    //     cout << s.heldBox << endl;
    // }

    objects::Box* heldBox = nullptr;

    while(window.isOpen()) {
        //cout << "x: " << sf::Mouse::getPosition(window).x << " y: " << sf::Mouse::getPosition(window).y << endl;

        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            } 
            if(event.type == sf::Event::MouseLeft) {
                cout << "mouse left" << endl;
                if(heldBox) {
                    heldBox->focus = false;
                    heldBox = nullptr;
                }
            }
        }
        
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if(heldBox) {
            if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                heldBox->focus = false;

                for(objects::Slot& s: slots) {
                    s.checkOverlap(mousePos, heldBox);
                }

                heldBox = nullptr;
            }
        } else {
            for(objects::Box& b: boxes) {
                if(
                    sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                    b.checkMouseClick(mousePos) &&
                    !heldBox
                ) {
                    heldBox = &b;
                    heldBox->focus = true;
                }
            }
        }

        window.clear(background_color);
        for(objects::Slot& s: slots) {
            s.update();
            s.draw(window);
        }
        for(objects::Box& b: boxes) {
            b.update(mousePos);
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