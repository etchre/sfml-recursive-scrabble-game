#include <vector>
#include <string>
#include <list>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "button.h"
#include "objects.h"

using std::vector;
using std::string;
using std::list;

namespace construction{
    void constructWord(
        const sf::Font& font,
        const string& word, 
        vector<objects::Box>& boxVec,
        list<objects::Slot>& slotVec,
        const std::unordered_map<string, sf::Texture>& textureMap
    );

    void constructCorrectTextboxes(
        const sf::Font& font, 
        const vector<string>& words, 
        vector<objects::Button>& buttonVec,
        const string& hiddenText
    );
}
