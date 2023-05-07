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

    sf::Color background_color(58,90,64);

    vector<Box> boxes = construction::constructWord(font, "word", 200, 50);

    while(window.isOpen()) {
        cout << "x: " << sf::Mouse::getPosition(window).x << " y: " << sf::Mouse::getPosition(window).y << endl;

        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            for(Box& b: boxes) {
                b.checkMouseClick(sf::Mouse::getPosition(window));
            }
        }

        window.clear(background_color);
        for(Box& b: boxes) {
            b.update(sf::Mouse::getPosition(window));
            b.draw(&window);
        }
        window.display();
    }

    return 0;
}