#include "construction.h"

vector<Box> construction::constructWord(const sf::Font& font,const string& word, const int& x, const int& y) {
    vector<Box> result;

    int inc = 0;
    int gap = 5;
    for(const char& c : word) {
        result.push_back(Box(font, x+inc*(gap+Box::size), y, c));
        inc++;
    }

    return result;
}