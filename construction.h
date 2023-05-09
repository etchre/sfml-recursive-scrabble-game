#include <vector>
#include <string>
#include <list>

#include <SFML/Graphics.hpp>

#include "objects.h"

using std::vector;
using std::string;
using std::list;

namespace construction{
    void constructWord(
        const sf::Font& font,
        const string& word, 
        const int& x, 
        const int& y,
        vector<objects::Box>& boxVec,
        list<objects::Slot>& slotVec
    );
}
