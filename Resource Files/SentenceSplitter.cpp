
#include "SentenceSplitter.h"

#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;


/*
 * Checks if the string is a sentence ending word
 *
 */
bool hasEndPunct(const string & s){
    if(s.size() > 2){
        char a = s.at((s.size()-1));
        char b = s.at((s.size()-2));
        bool b_check = (b == '.' || b == '?' || b == '!' || b == ',');
        bool a_check = (a == ' ');
        return (b_check && a_check);
    }
    return false;
}


/*
 * Reads all words and checks for sentence ending words -> stop adding word vs. add word since it is not sentence ending word. Each sentence is added to a vector
 *
 */
std::vector<std::string> splitSentence(const vector<string> & DOC_WORDS){

        vector<std::string> SENTENCES;

        string sentence = "";

        for(vector<std::string>::size_type i = 0; i != DOC_WORDS.size(); ++i){
            //cout << DOC_WORDS[i] <<endl;
            if(hasEndPunct(DOC_WORDS[i])){
                sentence = sentence + DOC_WORDS[i];
                SENTENCES.push_back(sentence);
                sentence = "";
            }
            else{
                sentence = sentence + DOC_WORDS[i];
            }
        }

        return SENTENCES;
}
