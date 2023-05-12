#include "construction.h"

#include <iostream>

void construction::constructWord(
    const sf::Font& font,
    const string& word, 
    vector<objects::Box>& boxVec,
    list<objects::Slot>& slotVec
) {
    float slotSizeDifference = (objects::Slot::size - objects::Box::size)/2;
    float inc = 7;
    int gap = 15;
    std::cout << slotSizeDifference << std::endl;
    for(const char& c : word) {
        boxVec.push_back(objects::Box(font, 0+inc, 200, c));
        slotVec.push_back(
            objects::Slot(
                0-slotSizeDifference+inc, 
                200-slotSizeDifference
            )
        );
        inc+=(gap+objects::Slot::size);
    }
    auto iter = slotVec.begin();
    // std::cout << "from construction" << std::endl;
    for(objects::Box& b : boxVec) {
        // std::cout << &b << std::endl;
        iter->setBox(&b);
        iter++;
    }
    float center = 400 - (inc/2);
    for(objects::Slot& s : slotVec) {
        s.move(center);
    }
}

void construction::constructCorrectTextboxes(
    const sf::Font& font, 
    const vector<string>& words, 
    vector<objects::Button>& buttonVec
) {
    float inc = 0;
    int gap = 5;
    for(const string& s : words) {
        buttonVec.push_back(
            objects::Button(
                font,
                true,
                0+inc, 
                400,
                s,
                20,
                sf::Color(33,37,41)
            )
        );
        inc += buttonVec.back().rect.getLocalBounds().width+gap;
    }
    //std::cout << inc << std::endl;
    float center = 400 - (inc/2);
    for(auto& b : buttonVec) {
        b.move(center);
    }
}

