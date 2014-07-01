#ifndef SENTENCE_SPLITTER_H_
#define SENTENCE_SPLITTER_H_

#include <string>
#include <vector>


bool hasEndPunct(const std::string & s);
std::vector<std::string> splitSentence(const std::vector<std::string> & DOC_WORDS);


#endif
