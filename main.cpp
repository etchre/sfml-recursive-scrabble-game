#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>

#include "word.h"
#include "utilities.h"
#include "box.h"

using std::cout;
using std::endl;

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

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

    Box b(&font);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(*b.getSquare());
        window.display();
    }

    return 0;
}