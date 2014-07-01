#ifndef STOPWORD_H_
#define STOPWORD_H_

#include <vector>
#include <string>
#include "File_Operations.h"
#include <fstream>
#include <unordered_map>

class StopWord{
public:
    StopWord();
    bool isStopWord();
    void setWord(const std::string & s);
    std::string & getWord();
private:
    std::string word;
    std::unordered_map<std::string,int> stop_list;
};

#endif
