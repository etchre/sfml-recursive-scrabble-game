#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "box.h"

using std::vector;
using std::string;

namespace construction{
    vector<Box> constructWord(
        const sf::Font& font,
        const string& word, 
        const int& x, 
        const int& y
    );
}
