//ethan reed
//4-6-23
//recursive scrabble game
#include "word.h"
#include <cstddef>
#include <sstream>

using namespace std;

Word::Word(string word) {
    this->word = word;
}

ostream& operator <<(ostream& str, const Word& word) {
    str << "Word: [" << word.getWord() << "]";
    return str;
}

bool operator <(const Word& word1, const Word& word2) {
	return word1.word.size() < word2.word.size();
}

bool operator >(const Word& word1, const Word& word2) {
	return word1.word.size() > word2.word.size();
}

string Word::getWord() const {
    return this->word;
}

void Word::setWord(string word) {
    this->word = word;
}