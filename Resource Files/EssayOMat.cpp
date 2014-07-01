
#include "EssayOMat.h"
#include "String_Operations.h"

#include <iostream>
#include <fstream>
using namespace std;


/*
 * Generates essay by writing to an output text file the highest ranked sentences of all documents based on the query.
 * Note: Sorting each sentence by Doc, then By sentence order in each doc would nullify all work done with weight computation!(-> Effectively,  since our doc score has every sentence of every document,
 * if docs are sorted, all the sentences of doc 1 will be displayed first. Then among doc 1,2,... sentences, display the sentence in original order. Result: it will simply display the original files without stop words, why compute weight then?)
 */


void generateEssay(std::multimap<double,std::string> & DOC_SCORE,std::multimap<double,std::string>::size_type & NTH_SCORE){
    std::multimap<double,std::string>::size_type CTR = 0;

    ofstream myfile;
    myfile.open ("C:/Qt/Qt5.2.1/Tools/QtCreator/bin/CppAss5/essay.txt");
        // Display the final created map reversed so that the highest ranking comes first.
        for (std::multimap<double,std::string>::reverse_iterator IT = DOC_SCORE.rbegin(); IT != DOC_SCORE.rend(); ++IT){
            CTR += sentenceSize((IT->second));
            if(CTR < NTH_SCORE){ // Display only the requested number of documents' score
                if(IT->second != ""){
                    addSentenceFormat(IT->second);
                    myfile << IT->second << " ";
                }
                }
            else
                break;
        }
        myfile.close();
}
