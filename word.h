//ethan reed
//4-6-23
//recursive scrabble game
#ifndef WORD_H
#define WORD_H

#include <string>

using namespace std;

class Word {

    public:
        Word(string word);
        friend ostream& operator <<(ostream& str, const Word& word);
        friend bool operator <(const Word& word1, const Word& word2);
        friend bool operator >(const Word& word1, const Word& word2);
        string getWord() const;
        void setWord(string word);

    private:
        string word;

};

#endif