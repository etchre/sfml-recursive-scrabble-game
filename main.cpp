#include <SFML/Graphics/Color.hpp>
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
#include <unordered_map>
#include <filesystem>

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

namespace fs = std::filesystem;

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

    sf::Texture letterA;
    if(!letterA.loadFromFile("../assets/letters/a.png")) {
        return -1;
    }

    std::unordered_map<string, sf::Texture> lettersMap;
    fs::path lettersPath = fs::current_path() /= "../assets/letters";
    //cout << lettersPath << endl;
    for(const auto& entry : fs::directory_iterator(lettersPath)) {
        sf::Texture currLetter;
        if(!currLetter.loadFromFile(entry.path())) {
            cout << "couldn't find " << entry.path().filename() << "!" << endl;
        } else {
            string filename = entry.path().stem();
            transform(filename.begin(), filename.end(), filename.begin(), ::toupper);
            lettersMap[filename] = currLetter;
        }
    }

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

    int guesses = 3;

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
        // hard mode
        //  if(validWords.size() != 2) {
        //      continue;
        //  }
        // easy mode
        if (validWords.size() < 3 || validWords.size() > 4) {
            continue;
        }
        // medium mode
        //  if(validWords.size() < 5) {
        //      continue;
        //  }
        vector<char> wordChars(chosenWord.begin(), chosenWord.end());
        randomString = string{wordChars.begin(), wordChars.end()};
        while(randomString == chosenWord) {
            shuffle(wordChars);
            randomString = string{wordChars.begin(), wordChars.end()};
        }
        for (vector<char>::iterator iter = wordChars.begin(); iter != wordChars.end(); std::advance(iter, 1)) {
            if (randomChars.find(*iter) == randomChars.end()) {
                randomChars.insert(*iter);
            }
        }
        break;
    }

    unordered_set<string> unguessedWords(validWords.begin(), validWords.end());

    //cheat mode
    for(string& s : validWords) {
        cout << s << " ";
    }
    cout << endl;

    sf::Font font;
    if(!font.loadFromFile("../assets/JetBrains.ttf")) {
        return -1;
    }

    string hiddenText = "";

    for(const char& c: randomString) {
        hiddenText += '?';
    }

    sf::Text hiddenTextObj = sf::Text(hiddenText, font, 16);

    vector<string> correctMessages = {
        "you got one!", 
        "that's correct!", 
        "nice one!", 
        "good going!",
        "great guess!",
        "smooth!",
        "clever one!",
        "nice, keep going!"
    };

    vector<string> incorrectMessages = {
        "not quite..", 
        "sorry, that's not correct", 
        "a little off..", 
        "try again..",
        "almost..",
        "you were close!",
        "i'm not sure that's a word..",
        "i think that's incorrect.."
    };

    shuffle(correctMessages);
    shuffle(incorrectMessages);

    float transparencyValue = 0;

    sf::Text sentence = sf::Text(
        "this is some sample text",
        font,
        16
    );

    sf::Text guessCounterText = sf::Text(
        std::to_string(guesses)+"  incorrect guesses left",
        font,
        20
    );

    sf::CircleShape guessCounterCircle = sf::CircleShape(12);
    guessCounterCircle.setFillColor(sf::Color::Transparent);
    guessCounterCircle.setOutlineThickness(2);
    guessCounterCircle.setOutlineColor(sf::Color::White);
    {
        float center = 400 - sentence.getLocalBounds().width/2;
        sentence.setPosition(center,150);
        center = 400 - guessCounterText.getLocalBounds().width/2;
        guessCounterText.setPosition(center,450);
        guessCounterCircle.setPosition(400 - guessCounterText.getLocalBounds().width/2 - 6,451);
    }
    

    sf::Color background_color(58,90,64);

    vector<objects::Box> boxes;
    list<objects::Slot> slots;
    vector<objects::Button> buttons;
    construction::constructWord(
        font, 
        randomString, 
        boxes, 
        slots,
        lettersMap
    );
    construction::constructCorrectTextboxes(
        font,
        validWords,
        buttons,
        hiddenText
    );
    buttons.push_back(
        objects::Button(
            font, 
            0, 
            320, 
            [&slots, &wordList, &buttons, &charAmount, &guesses, &sentence, &unguessedWords, &guessCounterCircle,
                &correctMessages, &incorrectMessages, &transparencyValue, &validWords, &guessCounterText]() {
                string word = "";
                for(objects::Slot& s : slots) {
                    char currLetter = s.getHeldLetter();
                    if(currLetter != ' ') {
                        word += currLetter;
                    }
                }
                cout << word << endl;
                if(utilities::binarySearch(word, wordList) != -1 && unguessedWords.contains(word)) {
                    if(word.length() == charAmount) {
                        sentence.setString(correctMessages.back());
                        sentence.setFillColor(sf::Color(106,153,78));
                        transparencyValue = 255;
                        correctMessages.pop_back();
                        for(auto& b : buttons) {
                            if(b.text == word) {
                                b.hidden = false;
                                b.fillColor = sf::Color(106,153,78);
                                unguessedWords.erase(word);
                            }
                        }
                        float center = 400 - sentence.getLocalBounds().width/2;
                        sentence.setPosition(center,150);
                        return;
                    }
                } else if(utilities::binarySearch(word, wordList) != -1 && !unguessedWords.contains(word)) {
                    sentence.setString("you already guessed this one!");
                    sentence.setFillColor(sf::Color(188,71,73));
                    transparencyValue = 255;
                    float center = 400 - sentence.getLocalBounds().width/2;
                    sentence.setPosition(center,150);
                    return;
                } else {
                    if(incorrectMessages.empty()) {
                        sentence.setString("incorrect");  
                    } else {
                        sentence.setString(incorrectMessages.back());
                        incorrectMessages.pop_back();
                    }
                }
                sentence.setFillColor(sf::Color(188,71,73));
                transparencyValue = 255;
                float center = 400 - sentence.getLocalBounds().width/2;
                sentence.setPosition(center,150);
                guesses--;
                if(guesses > 1) {
                    guessCounterText.setString(std::to_string(guesses)+"  incorrect guesses left");
                } else {
                    guessCounterText.setString(std::to_string(guesses)+"  incorrect guess left");
                }
                
                center = 400 - guessCounterText.getLocalBounds().width/2;
                guessCounterText.setPosition(center,450);
                guessCounterCircle.setPosition(400 - guessCounterText.getLocalBounds().width/2 - 6,451);
            }, 
            "check"
        )
    );
    {
        buttons.back().move(2);
        float center = 400 - (buttons.back().rect.getLocalBounds().width/2)-5;
        buttons.back().move(center);
    }
    
    objects::Box* heldBox = nullptr;

    bool finished = false;

    while(window.isOpen()) {
        //cout << "x: " << sf::Mouse::getPosition(window).x << " y: " << sf::Mouse::getPosition(window).y << endl;

        if(transparencyValue < 0) {
            transparencyValue = 0;
        } else {
            transparencyValue -= 0.02;
        }

        if(guesses <= 0 || unguessedWords.empty()) {
            finished = true;
            guessCounterCircle.setOutlineColor(sf::Color::Transparent);
            if(guesses <= 0) {
                guessCounterText.setString("out of guesses, game over!");
            } else {
                guessCounterText.setString("congrats! you got them all!");
            }
            float center = 400 - guessCounterText.getLocalBounds().width/2;
            guessCounterText.setPosition(center,450);
        } 

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
        sentence.setFillColor(sf::Color(
            sentence.getFillColor().r,
            sentence.getFillColor().g,
            sentence.getFillColor().b,
            transparencyValue));
        window.draw(sentence);
        window.draw(guessCounterText);
        window.draw(guessCounterCircle);
        for(objects::Button& button : buttons) {
            if(button.isMouseOver(mousePos) && button.hasFunction && heldBox==nullptr && !finished) {
                mouseHover = true;
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    button.clicked = true;
                } else {
                    if(button.clicked) {
                        button.clickFunction();
                    }
                    button.clicked = false;
                }
            } else {
                button.clicked = false;
            }
            
            if(finished && button.hasFunction) {

            } else {
                button.draw(window);
                button.update();
            }
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