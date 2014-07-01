
#include "StopWord.h"
#include <iostream>
#include <algorithm>

using namespace std;

/*
 *Create a stopword object. Initalize the stop list with the text file.
 *
 */
    StopWord::StopWord(){
        ifstream ifs("C:/Qt/Qt5.2.1/Tools/QtCreator/bin/CppAss5/stop_list.txt");
        vector<string> v = readDocument(ifs);
        for(vector<string>::const_iterator it = v.begin(); it != v.end(); it++){
            stop_list[*it];
        }
    };

/*
 * Check if word is a stop word;
 *
 */
    bool StopWord::isStopWord() {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        unordered_map<std::string,int>::const_iterator MAP_ITER = stop_list.find(word);
        return (MAP_ITER != stop_list.end());
    };

/*
 * Assign a word to the stopword object (do not create a new stopword object to avoid reading again all the stop list file)
 *
 */
    void StopWord::setWord(const string & s){
        word = s;
    };

/*
 * Return word assigned to stopword object
 *
 */

    string & StopWord::getWord(){
        return word;
    };
