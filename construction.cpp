#include "construction.h"

#include <iostream>

//will construct an amount of box and slot objects according to the given word
//the objects will always be placed in the center of the screen
void construction::constructWord(
    const sf::Font& font,
    const string& word, 
    vector<objects::Box>& boxVec,
    list<objects::Slot>& slotVec,
    const std::unordered_map<string, sf::Texture>& textureMap,
    float& width
) {
    //calculate the difference in size between the slot and box objects and divide by 2 (the box will be centered in the slot)
    float slotSizeDifference = (objects::Slot::size - objects::Box::size)/2;
    float inc = 10; //this variable keeps track of the width of all slots and boxes, it will increased as they are created
    int gap = 5; //the gap amount in pixels between slots
    for(const char& c : word) { //iterate over each character in the given word
        boxVec.push_back(objects::Box(font, 0+inc, 200, c)); //create a box with that letter
        boxVec.back().getSquare()->setTexture( 
            &textureMap.at(string(1,c)) //assign it a texture according to the hashmap of textures passed in
        );
        slotVec.push_back( //we then create a slot object
            objects::Slot(
                0-slotSizeDifference+inc, //values that will center the slot around the box
                200-slotSizeDifference
            )
        );
        inc+=(gap+slotVec.back().square.getLocalBounds().width); //we then increase the variable keeping track of the width by the size of the slots
    }
    width = inc; //we then assign the given float variable to inc, which is the combined width of all of the slots
                 //this lets me keep using this value in the main game loop
    auto iter = slotVec.begin(); //then we get an iterator for all of the slots
    for(objects::Box& b : boxVec) { //then we iterate over all the boxes, this is to make sure each slot contains one box at the start
        iter->setBox(&b); //assign the current box to the current slot
        iter++; //i increase the slot iterator by 1, keeping both iterators in sync. 
    } 
    float center = 400 - (inc/2); //calculate the center given the width
    for(objects::Slot& s : slotVec) { //then we center all of the objects together
        s.move(center);
    }
}

void construction::constructCorrectTextboxes(
    const sf::Font& font, 
    const vector<string>& words, 
    vector<objects::Button>& buttonVec,
    const string& hiddenText
) {
    float inc = 0;
    int gap = 5;
    for(const string& s : words) {
        buttonVec.push_back(
            objects::Button(
                font,
                true,
                0+inc, 
                282,
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
        b.hiddenText.setFont(font);
        b.hiddenText.setString(hiddenText);
        b.hiddenText.setCharacterSize(16);
    }
}

