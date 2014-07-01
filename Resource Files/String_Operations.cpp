
#include <string>
#include <algorithm>
#include <vector>
#include "String_Operations.h"
#include <sstream>
#include <iostream>

using namespace std;

/*
 *	Small functions to modify strings
 */

// Trim the line to avoid erros
void trimLine(string & LINE) {
    LINE.erase(remove(LINE.begin(), LINE.end(), '\t'), LINE.end());
    LINE.erase(remove(LINE.begin(), LINE.end(), ' '), LINE.end());
}

// Remove all punctation characters
void stripPunct(std::string & str) {

    string word = "";

    for(std::string::size_type i = 0; i != str.size(); ++i) {
        if(str[i] == '\''){
            break;
        }
        else if((str[i]=='+') || (str[i]=='-') || (str[i]=='*')){
            word= word + (str[i]);
        }
        else if(isalnum(str[i])){
            word = word + (str[i]);
        }
    }

    str = word;

}
/*
 *	Put the query words into a vector of strings
 */
vector<string> queryToVector(const std::string & str){
    string NEXT;
    vector<string> RESULT;

    // For each character in the string
    for (string::const_iterator it = str.begin(); it != str.end(); it++) {
        // If we've hit the terminal character which is a space : ' '
        if (*it == ' ') {
            // If we have some characters accumulated
            if (!NEXT.empty()) {
                // Add them to the result vector
                RESULT.push_back(NEXT);
                NEXT.clear();
            }
        } else {
            // Accumulate the next character into the sequence
            NEXT += *it;
        }
    }

    if (!NEXT.empty())
         RESULT.push_back(NEXT);

    return RESULT;

}
//Read all vector of a sentence
std::vector<std::string> readWords(std::string & sentence){

    vector<std::string> WORDS;

    istringstream ss(sentence);
    string word;

    while(ss >> word){
        WORDS.push_back(word);
    }

    return WORDS;
}

//Add Caps lock to first character of string and period to end since punctuation was removed to effectively remove all stop words
void addSentenceFormat(string & s){
    s[0] = toupper(s[0]);
    if(s.size() > 1)
        s[s.size()-1] =	'.';
}

//Get number of words in sentence
int sentenceSize(const string & sentence){
    int CTR = 0;

    istringstream ss(sentence);
    string word;

    while(ss >> word){
        CTR++;
    }

    return CTR;
}

