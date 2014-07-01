/*
 * File_Operations.h
 *
 *  Created on: Jan 23, 2014
 *      Author: nicolas.husser
 */


#ifndef STRING_OPERATIONS_H_
#define STRING_OPERATIONS_H_

#include <string>
#include <vector>

std::vector<std::string> queryToVector(const std::string & str);
void stripPunct(std::string & str);
void trimLine(std::string & LINE);
std::vector<std::string> readWords(std::string & sentence);
void addSentenceFormat(std::string & s);
int sentenceSize(const std::string & sentence);

#endif /* STRING_OPERATIONS_H_ */
