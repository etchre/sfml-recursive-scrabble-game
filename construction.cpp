#include "construction.h"

vector<objects::Box> construction::constructWord(const sf::Font& font,const string& word, const int& x, const int& y) {
    vector<objects::Box> result;

    int inc = 0;
    int gap = 5;
    for(const char& c : word) {
        result.push_back(objects::Box(font, x+inc*(gap+objects::Box::size), y, c));
        inc++;
    }

    return result;
}