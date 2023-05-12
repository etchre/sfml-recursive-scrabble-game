#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <functional>
#include <stdexcept>
#include <algorithm>
#include <random>
#include <cctype>
#include <unordered_set>

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

// new code I inserted into the game
// shuffles the vector in place
// implements the fisher yates shuffle
// used to randomize the letters in words, or the order of the vector of words
template <class T> void shuffle(vector<T> &vec) {
    std::random_device os_seed;  // gets a seed from the operating system
    std::mt19937 rng(os_seed()); // initializes the mersenne twister engine using the above seed
    for (int i = vec.size() - 1; i > 1; i--) {
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, i); // gets a uniform distribution of the numbers from 0 to i
        int j = dist(rng); // get random number using the above distribution
        T temp = vec.at(i); // swap items i and j
        vec.at(i) = vec.at(j);
        vec.at(j) = temp;
    }
}

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

    int charAmount = 4;
    unordered_set<char> randomChars;
    string randomString = "";
    vector<string> validWords;

    vector<Word> sub = utilities::subsection(wordListBySize, charAmount); //get a vector of words that are all size 'charAmount'
    shuffle(sub); //shuffle the vector of words

    //pick a word of the top, since the vector is already shuffled, the word should be a different one most of the time
    for (const Word &word : sub) {
        string chosenWord = word.getWord();
        validWords = utilities::findAllValidWords(wordList, chosenWord);
        // expert mode
        //  if(findAllValidWords(chosenWord).size() != 1) {
        //      continue;
        //  }
        // easy mode
        //  if(findAllValidWords(chosenWord).size() != 2) {
        //      continue;
        //  }
        // medium mode
        if (validWords.size() < 3 || validWords.size() > 4) {
            continue;
        }
        //hard mode
        //  if(validWords.size() < 5) {
        //      continue;
        //  }
        vector<char> wordChars(chosenWord.begin(), chosenWord.end());
        shuffle(wordChars);
        randomString = string{wordChars.begin(), wordChars.end()};
        for (vector<char>::iterator iter = wordChars.begin(); iter != wordChars.end(); std::advance(iter, 1)) {
            if (randomChars.find(*iter) == randomChars.end()) {
                randomChars.insert(*iter);
            }
        }
        break;
    }

    for(string& s : validWords) {
        cout << s << " ";
    }
    cout << endl;

    sf::Font font;
    if(!font.loadFromFile("../assets/JetBrains.ttf")) {
        return -1;
    }

    sf::Color background_color(58,90,64);

    vector<objects::Box> boxes;
    list<objects::Slot> slots;
    vector<objects::Button> buttons;
    construction::constructWord(
        font, 
        randomString, 
        250, 
        200, 
        boxes, 
        slots
    );
    construction::constructCorrectTextboxes(
        font,
        validWords,
        buttons
    );
    buttons.push_back(
        objects::Button(
            font, 
            329, 
            290, 
            [&slots, &wordList, &buttons]() {
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
                        for(auto& b : buttons) {
                            if(b.text == word) {
                                b.hidden = false;
                                b.fillColor = sf::Color(106,153,78);
                            }
                        }
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
            if(button.isMouseOver(mousePos) && button.hasFunction) {
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