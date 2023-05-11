#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <functional>

#include <SFML/Graphics.hpp>

#include "button.h"
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

    sf::Clock clock;

    sf::Cursor handCursor;
    sf::Cursor arrowCursor;

    handCursor.loadFromSystem(sf::Cursor::Hand);
    arrowCursor.loadFromSystem(sf::Cursor::Arrow);

    vector<Word> wordList;
    vector<Word> wordListBySize;
    ifstream file("../CollinsScrabbleWords_2019.txt");

    if(file.is_open()) {
        string line;
        getline(file, line); //skip header line

        while(getline(file, line)) {
            wordList.push_back(Word(line.substr(0,line.size() - 1)));
        }
    }

    file.close();

    wordListBySize = wordList; //make copy of wordList;
    utilities::quicksort(wordListBySize, 0, wordListBySize.size() - 1);

    sf::Font font;
    if(!font.loadFromFile("../assets/VulfMonoLight.ttf")) {
        return -1;
    }

    sf::Color background_color(58,90,64);

    vector<objects::Box> boxes;
    list<objects::Slot> slots;
    vector<objects::Button> buttons;
    construction::constructWord(font, "golf", 250, 200, boxes, slots);
    buttons.push_back(
        objects::Button(
            font, 
            329, 
            290, 
            [&slots, &wordList]() {
                string word = "";
                for(objects::Slot& s : slots) {
                    char currLetter = s.getHeldLetter();
                    if(currLetter != ' ') {
                        word += currLetter;
                    }
                }
                cout << word << endl;
                if(utilities::binarySearch(word, wordList) != -1) {
                    if(word.length() == 4) {
                        cout << "valid word" << endl;
                        return;
                    }
                }
                cout << "not a valid word" << endl;
            }, 
            "check"
        )
    );

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

        bool mouseHover = false;

        window.clear(background_color);
        for(objects::Button& button : buttons) {
            if(button.isMouseOver(mousePos)) {
                mouseHover = true;
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    button.clicked = true;
                } else {
                    if(button.clicked) {
                        button.clickFunction();
                    }
                    button.clicked = false;
                }
            }
            button.update();
            button.draw(window);
        }
        for(objects::Slot& s: slots) {
            if(s.isMouseOver(mousePos)) {
                mouseHover = true;
            }
            s.update();
            s.draw(window);
        }
        for(objects::Box& b: boxes) {
            if(b.isMouseOver(mousePos)) {
                mouseHover = true;
            }
            b.update(mousePos);
            if(&b == heldBox) {
                continue;
            }
            b.draw(window);
        }
        if(heldBox) {
            heldBox->draw(window);
        }
        if(mouseHover) {
            window.setMouseCursor(handCursor);
        } else {
            window.setMouseCursor(arrowCursor);
        }
        window.display();
    }

    return EXIT_SUCCESS;
}