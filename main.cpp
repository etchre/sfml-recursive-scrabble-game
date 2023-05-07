#include <SFML/Graphics/Rect.hpp>
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

    sf::Color background_color(58,90,64);

    Box b(&font, 200, 50, 'w');
    Box b2(&font, 255, 50, 'o');
    Box b3(&font, 310, 50, 'r');
    Box b4(&font, 365, 50, 'd');

    sf::Vector2 pos = b.getSquare()->getPosition();
    sf::FloatRect textPos = b.getLetter()->getGlobalBounds();
    cout << "x: " << pos.x << " y: " << pos.y << endl;
    cout << "left: " << textPos.left << 
            " top: " << textPos.top << 
            " width: " << textPos.width << 
            " height: " << textPos.height << endl;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(background_color);
        b.draw(&window);
        b2.draw(&window);
        b3.draw(&window);
        b4.draw(&window);
        window.display();
    }

    return 0;
}