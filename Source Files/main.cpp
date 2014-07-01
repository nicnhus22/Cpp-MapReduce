/*
 * Source.cpp
 *
 *  Created on: Jan 23, 2014
 *      Author: nicolas.husser
 */

#include "String_Operations.h"
#include "Math_Operations.h"
#include "File_Operations.h"
#include "Map_Operations.h"
#include "StopWord.h"
#include "SentenceSplitter.h"
#include "EssayOMat.h"

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <map>
#include <regex>
#include <algorithm>
#include <complex>
#include <functional>

using namespace std;

typedef vector<string> string_vector;
typedef vector<unordered_map <string, int>> map_vector;

int main(){

    // Open Input FIle Stream. NOTE: adding files slows down process, computing weight of each word of every sentences is what slows down the process.
    ifstream ifs("C:/Qt/Qt5.2.1/Tools/QtCreator/bin/CppAss5/file_names.txt");
    ifstream input_ifs("C:/Qt/Qt5.2.1/Tools/QtCreator/bin/CppAss5/q1.txt");
    // Vector that holds name
    string_vector FILES_NAME = readFileName(ifs);
    // Store the scalar product of each document vector with the query vector
    vector<double> SCALAR_PRODS;
    // Store the multiplication of the norm of each document vector and the query
    vector<double> NORM_PRODS;
    // Store the score of each document in multimap in case there are more than one identical score
    multimap<double, string> DOC_SCORE;
    // Store the number of words to be displayed
    multimap<double, string>::size_type NTH_SCORE;

    // Hold the vectors containing the vector of words of each document
    vector<string_vector> DOCUMENTS_HOLDER;
    // Hold the words of every single documents
    unordered_map <string, int> MASTER_MAP;
    // Create vector that holds the map for every file
    vector<unordered_map <string, int>> MAP_HOLDER;
    // Create vector that holds frequency vector for every file
    map_vector VECTOR_HOLDER_SENTENCES;
    // Create vector that holds weight vector for every file
    vector<unordered_map <string, double>> WEIGHT_HOLDER_SENTENCES;
    // Store the query of the user with each words in a vector
    unordered_map<string, int> QUERY_WORDS_MAP;
    // Store the query of the user with each words in a vector with computed weight
    unordered_map<string, double> QUERY_WORDS_MAP_WEIGHT;

    // Vector that holds a vector of all the sentences of a document at each index
    vector<string_vector> DOC_SENTENCES_HOLDER;
    //Vector of every sentence of every doc without stop words
    vector<string> DOC_SENTENCES;
    // Store the number of times a word appear accross each mini-doc(sentence), in a doc
    unordered_map<string, int> DOC_APPEAR_SENTENCES;

    cout << "Loading..." << endl;

    //Get frequency of each word in query, and update master map with the query words to get the number of documents in wich the query words appear in. Also update the number of sentences in which a word appears
    QUERY_WORDS_MAP = getQueryFrequency(readDocumentStopWord(input_ifs), MASTER_MAP, DOC_APPEAR_SENTENCES);

    // Iterate through all the files and push their content inside the DOCUMENTS_HOLDER
    // with the index of the current file
    for(string_vector::size_type i = 0; i != FILES_NAME.size(); ++i){

        ifstream IN_FILE(FILES_NAME[i].c_str()); // Open current file

        if(IN_FILE){ // If the file exists and can be found, then process
            DOCUMENTS_HOLDER.push_back(readDocument(IN_FILE)); // Put the content of the files in the DOCUMENTS_HOLDER[i]
            DOC_SENTENCES_HOLDER.push_back(removeStopWord(splitSentence(DOCUMENTS_HOLDER[i]))); //Extract each sentence of every document, remove stop words and store in a vector
        }else { // Else, if the file doesnt exist or cannot be found then erase it from FILE_NAME vector
            cout << "The file " << FILES_NAME[i] << " doesn't exist or cannot be found, please verify the file name." << endl;
            FILES_NAME.erase(FILES_NAME.begin()+i); // Remove the current file name from the vector
            --i; // Decrement i so that you avoid starting the vector at 1
        }
    }
    //Iterate through every sentence and process them (getFrequency) then store each map (each sentence -> map) in a vector
    for(string_vector::size_type i = 0; i != DOC_SENTENCES_HOLDER.size(); ++i){
        for(string_vector::size_type j = 0; j != DOC_SENTENCES_HOLDER[i].size(); ++j){
            MAP_HOLDER.push_back(getFrequency(readWords(DOC_SENTENCES_HOLDER[i][j]), MASTER_MAP, DOC_APPEAR_SENTENCES)); // Create the map to get the frequency of each word in the current sentence (for each sentence, a map)
            //cout << "Sentence:" + DOC_SENTENCES_HOLDER[i][j] +"!"<< endl;
            DOC_SENTENCES.push_back(DOC_SENTENCES_HOLDER[i][j]);//Store every sentence to display later based on rank
            //MAP_HOLDER_SENTENCES.push_back(getQueryFrequency(readWords(DOC_SENTENCES_HOLDER[i][j]))); Not needed, but keep it for debug
        }
    }
    //Loop through every sentence, obtain the frequency vector of all sentences(compared to master map) and then compute weight using each vector. Store each weight vector in a weight holder vector
    for(vector<unordered_map <string, int>>::size_type i=0; i!= MAP_HOLDER.size(); ++i){
        VECTOR_HOLDER_SENTENCES.push_back(computeVector(MAP_HOLDER[i], MASTER_MAP));
        WEIGHT_HOLDER_SENTENCES.push_back(computeWeight(DOC_APPEAR_SENTENCES,VECTOR_HOLDER_SENTENCES[i],MAP_HOLDER.size()));
    }
    //Do the same for the query, get frequency vector, compute weight
    QUERY_WORDS_MAP = computeVector(QUERY_WORDS_MAP, MASTER_MAP); // Get the vector compared to the MASTER_MAP
    QUERY_WORDS_MAP_WEIGHT = computeWeight(DOC_APPEAR_SENTENCES,QUERY_WORDS_MAP,MAP_HOLDER.size());

    // Iterate through all the vectors of each document and compute dot product with the query also
    // multiplication of the norm of the document(sentence) vector with the query vector
    for(vector<unordered_map <string, double>>::size_type i=0; i!= WEIGHT_HOLDER_SENTENCES.size(); ++i){
        double TEMP_DOT = scalar_product(QUERY_WORDS_MAP_WEIGHT, WEIGHT_HOLDER_SENTENCES[i]); // Get the scalar product
        SCALAR_PRODS.push_back(TEMP_DOT);
        double TEMP_NORM = multiplyNorms(QUERY_WORDS_MAP_WEIGHT, WEIGHT_HOLDER_SENTENCES[i]); // Multiply the norm of the two vectors
        NORM_PRODS.push_back(TEMP_NORM);
    }


    // Iterate through all the vectors and compute the ratio of the scalar product and the multiplication
    // of the vectors' norms. Then add it to a Map so that the elements are sorted.
    for(vector<double>::size_type i = 0; i != WEIGHT_HOLDER_SENTENCES.size(); ++i){
        double RATIO;

        if(SCALAR_PRODS[i] == 0 && NORM_PRODS[i] == 0){ // Avoid division by zero error and other check to be sure
            RATIO = 0;
        }
        else{
            RATIO = SCALAR_PRODS[i]/NORM_PRODS[i];
        }
        DOC_SCORE.insert(pair<double, string>(RATIO,DOC_SENTENCES[i])); //Sentence at each index i is the sentence of MAP_HOLDER[i]. At each index, the sentence of map holder is same as doc sentences because they were initilized together (same length of vector, same index)
    }

    cout << "\nWhat length do you want for the summary? " ;
    cin  >> NTH_SCORE;
    cout << endl;
    if(NTH_SCORE > MASTER_MAP.size()){
        NTH_SCORE = MASTER_MAP.size();
        cout << "You entered a number greater than the number of words of all the input documents. The summary will be written with the maximum length." << endl;
    }else if(NTH_SCORE <= 0){
        NTH_SCORE = MASTER_MAP.size();
        cout << "You entered a number less than or equal 0. The summary will be written with the maximum length." << endl;
    }

    generateEssay(DOC_SCORE,NTH_SCORE);
    cout << "Essay generated in \"essay.txt\"" << endl;

    string DEBUG;
    cin >> DEBUG;

    return 0;
}
