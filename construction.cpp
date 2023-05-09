#include "construction.h"

#include <iostream>

void construction::constructWord(
    const sf::Font& font,
    const string& word, 
    const int& x, 
    const int& y, 
    vector<objects::Box>& boxVec,
    list<objects::Slot>& slotVec
) {
    int inc = 0;
    int gap = 15;
    for(const char& c : word) {
        boxVec.push_back(objects::Box(font, x+inc*(gap+objects::Slot::size), y, c));
        float slotSizeDifference = (objects::Slot::size - objects::Box::size)/2;
        slotVec.push_back(
            objects::Slot(
                x-slotSizeDifference+inc*(gap+objects::Slot::size), 
                y-slotSizeDifference
            )
        );
        inc++;
    }
    auto iter = slotVec.begin();
    // std::cout << "from construction" << std::endl;
    for(objects::Box& b : boxVec) {
        // std::cout << &b << std::endl;
        iter->setBox(&b);
        iter++;
    }
}