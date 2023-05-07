#include "utilities.h"

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <random>
#include <cctype>

int utilities::binarySearch(string key, const vector<Word> &vec) {
    int low = 0;
    int high = vec.size() - 1;

    // automatically capitalize every letter in the key
    // good to do since all words in word list are capital
    for (auto &c : key) {
        c = static_cast<char>(toupper(c));
    }

    while (high >= low) {
        int mid = (low + high) / 2;

        if (key.compare(vec.at(mid).getWord()) < 0) {
            high = mid - 1;
        } else if (key.compare(vec.at(mid).getWord()) == 0) {
            return mid;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}

// partition function which is used for quicksort
// sorts by size of word!!
int utilities::partition(vector<Word> &vec, const int &startIndex, const int &endIndex) {
    // Select the middle value as the pivot.
    long int midpoint = startIndex + (endIndex - startIndex) / 2;
    Word pivot = vec.at(midpoint);

    // "low" and "high" start at the ends of the array segment
    // and move towards each other.
    long int low = startIndex;
    long int high = endIndex;

    bool done = false;
    while (!done) {
        // Increment low while item at index low from vec < pivot
        while (vec.at(low) < pivot) {
            low = low + 1;
        }

        // Decrement high while pivot < item at index high from vec
        while (vec.at(high) > pivot) {
            high = high - 1;
        }

        // If low and high have crossed each other, the loop
        // is done. If not, the elements are swapped, low is
        // incremented and high is decremented.
        if (low >= high) {
            done = true;
        } else {
            Word temp = vec.at(low);
            vec.at(low) = vec.at(high);
            vec.at(high) = temp;
            low++;
            high--;
        }
    }

    return high;
}

// quicksort function which sorts an vector of word items in ascending.
// used to put the vector of words in ascending order according to the size of words
void utilities::quicksort(vector<Word> &vec, const int &startIndex, const int &endIndex) {
    // Only attempt to sort the array segment if there are
    // at least 2 elements
    if (endIndex <= startIndex) {
        return;
    }

    // Partition the array segmentt
    int high = utilities::partition(vec, startIndex, endIndex);

    // Recursively sort the left segment
    utilities::quicksort(vec, startIndex, high);

    // Recursively sort the right segment
    utilities::quicksort(vec, high + 1, endIndex);
}

// new code I inserted into the game
// returns a vector of words all containing the given length of word
// used to make sure the game will always pick a word of a certain size
vector<Word> utilities::subsection(const vector<Word> &vec, int wordLength) {
    if (wordLength < 2 || wordLength > 15) {
        throw std::invalid_argument("value must be within 2-15");
    }
    int low = 0;
    int high = vec.size() - 1;

    while (high >= low) {
        int mid = (low + high) / 2;
        if (vec.at(mid).getWord().size() > wordLength) {
            high = mid - 1;
        } else if (vec.at(mid).getWord().size() == wordLength) {
            break;
        } else {
            low = mid + 1;
        }
    }

    // a little bit of an ugly implementation, but it works well enough
    if (vec.at(low).getWord().size() < wordLength) {
        while (vec.at(low).getWord().size() < wordLength) {
            low++;
        }
    } else if (vec.at(low).getWord().size() == wordLength) {
        while (vec.at(low).getWord().size() == wordLength && low > vec.size() + 1) {
            low--;
        }
        low++;
    }

    if (vec.at(high).getWord().size() > wordLength) {
        while (vec.at(high).getWord().size() > wordLength) {
            high--;
        }
    } else if (vec.at(high).getWord().size() == wordLength) {
        while (vec.at(high).getWord().size() == wordLength && high < vec.size() - 1) {
            high++;
        }
    }

    return vector<Word>(vec.begin() + low, vec.begin() + (high + 1));
}

// recursive function
// finds every word you can make using the letters in remainLetters
// scramLetters should be left empty when using this function
vector<string> utilities::findAllPossibilities(string remainLetters, string scramLetters) {
    string tmpString;
    vector<string> result;

    if (remainLetters.size() == 0) { // base case
        result.push_back(scramLetters);
        return result;
    } else { // recursive case
        for (unsigned int i = 0; i < remainLetters.size(); i++) {
            tmpString = remainLetters.substr(i, 1);
            remainLetters.erase(i, 1);
            scramLetters = scramLetters + tmpString;

            vector<string> possibilities = findAllPossibilities(remainLetters, scramLetters);
            result.insert(result.end(), std::make_move_iterator(possibilities.begin()), std::make_move_iterator(possibilities.end()));

            remainLetters.insert(i, tmpString);
            scramLetters.erase(scramLetters.size() - 1, 1);
        }
    }

    return result;
}

//a wrapper function for the findAllPossibilities function
//iterates over the vector returned by said function, and only keeps the words
//that exist in the word list, then it returns a vector of those words
vector<string> utilities::findAllValidWords(vector<Word> &vec, const string &word) {
    vector<string> result;
    vector<string> possibleWords = utilities::findAllPossibilities(word);

    for (const auto &w : possibleWords) {
        if (utilities::binarySearch(w, vec) != -1) {
            if(std::find(result.begin(), result.end(), w) == result.end()) {
                result.push_back(w);
            }
        }
    }

    return result;
}

// new code I inserted into the game
// shuffles the vector in place
// implements the fisher yates shuffle
// used to randomize the letters in words, or the order of the vector of words
template <class T> void utilities::shuffle(vector<T> &vec) {
    std::random_device os_seed;  // gets a seed from the operating system
    std::mt19937 rng(os_seed()); // initializes the mersenne twister engine using the above seed
    for (int i = vec.size() - 1; i > 1; i--) {
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, i); // gets a uniform distribution of the numbers from 0 to i
        int j = dist(rng); // get random number using the above distribution
        T temp = vec.at(i); // swap items i and j
        vec.at(i) = vec.at(j);
        vec.at(j) = temp;
    }
}