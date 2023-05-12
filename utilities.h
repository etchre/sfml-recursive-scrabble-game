#include <vector>
#include <string>

#include "word.h"

using std::vector;
using std::string;

namespace utilities {
    int binarySearch(string key, const vector<Word> &vec);
    int partition(vector<Word> &vec, const int &startIndex, const int &endIndex);
    void quicksort(vector<Word> &vec, const int &startIndex, const int &endIndex);
    vector<Word> subsection(const vector<Word> &vec, int wordLength);
    vector<string> findAllPossibilities(string remainLetters, string scramLetters = "");
    vector<string> findAllValidWords(vector<Word> &vec, const string &word);
}