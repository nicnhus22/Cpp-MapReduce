
/*
 * File_Operations.cpp
 *
 *  Created on: Jan 23, 2014
 *      Author: nicolas.husser
 */

#include "File_Operations.h"
#include "String_Operations.h"
#include "StopWord.h"

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <regex>
#include <sstream>

using namespace std;

typedef vector<string> string_vector;
StopWord stop_word;

/*
 *	End of small string functions
 */


vector<string> readFileName(ifstream & INPUT_F){

    string TEMP_LINE;
    string_vector WORDS;

    // Read the file line by line until there is no more
    // Store the line is a vector<string> to keep track of it
    while(getline(INPUT_F, TEMP_LINE)){
        // Trim file name to avoid errors
        trimLine(TEMP_LINE);
        WORDS.push_back(TEMP_LINE);
    }
    INPUT_F.close();

    return WORDS;
}

/*
 * Reads every word in doc and add space for formatting later (by definition there is a space after each word because a space is the delimitor)
 * Return vector of all words
 */

vector<string> readDocument(ifstream & INPUT_F){

    string WORD;
    string_vector WORDS;

    // Read the file word by word until there is no more
    // Store the words is a vector<string> to keep track of it
    while(INPUT_F >> WORD){
        WORD = WORD + " ";
        WORDS.push_back(WORD);
    }
    INPUT_F.close();

    return WORDS;

}

/*
 * Reads every word in doc and add space for formatting later (by definition there is a space after each word because a space is the delimitor)
 * Return vector of all words except stop words
 */

vector<string> readDocumentStopWord(ifstream & INPUT_F){
    string WORD;
    string_vector WORDS;
    // Read the file word by word until there is no more
    // Store the words is a vector<string> to keep track of it
    while(INPUT_F >> WORD){
        //cout << WORD << endl;
        stripPunct(WORD);
        WORD = WORD + " ";
        stop_word.setWord(WORD);
        if(!stop_word.isStopWord()){
            //cout << "NOT STOP " + WORD << endl;
            WORDS.push_back(WORD);
        }
    }
    INPUT_F.close();

    return WORDS;

}

/*
 * Checks each string of the argument vector. If stop word detected, the returned vector will not contain it. Method is defined here to avoid creating new stopword object
 *
 */


std::vector<std::string> removeStopWord(std::vector<std::string> & v){

    vector<std::string> SENTENCE_NO_STOP;

        string WORD;

        string no_stop_string = "";

        for (std::vector<std::string>::size_type i = 0; i != v.size(); ++i)
        {
            stringstream TEMP(v[i]);

            while(TEMP >> WORD){
                //cout << WORD << endl;
                stripPunct(WORD);
                WORD = WORD + " ";
                stop_word.setWord(WORD);
                if(!stop_word.isStopWord()){
                    //cout << "NOT STOP: "+  WORD << endl;
                    no_stop_string = no_stop_string + WORD;
                }
            }

            SENTENCE_NO_STOP.push_back(no_stop_string);
            no_stop_string = "";
        }

        return SENTENCE_NO_STOP;
    };
