/*
 * File_Operations.h
 *
 *  Created on: Jan 23, 2014
 *      Author: nicolas.husser
 */

#ifndef MAP_OPERATIONS_H_
#define MAP_OPERATIONS_H_

#include <string>
#include <unordered_map>
#include <vector>

std::unordered_map <std::string, int> getQueryFrequency(const std::vector<std::string> & FILE_CONTENT);
std::unordered_map <std::string, int> getQueryFrequency(const std::vector<std::string> & FILE_CONTENT, std::unordered_map<std::string, int> & MASTER_MAP,std::unordered_map<std::string, int> & DOC_APPEAR_SENTENCES);
std::unordered_map <std::string, int> getFrequency(const std::vector<std::string> & FILE_CONTENT, std::unordered_map<std::string, int> & MASTER);
std::unordered_map <std::string, int> getFrequency(const std::vector<std::string> & FILE_CONTENT, std::unordered_map<std::string, int> & MASTER_MAP,std::unordered_map<std::string, int> & DOC_APPEAR_SENTENCES);
std::unordered_map <std::string, int> computeVector(const std::unordered_map <std::string, int> & FILE_MAP, const std::unordered_map<std::string, int> & MASTER_MAP);
bool isInDocument(const std::string & s, std::unordered_map<std::string,int> map);

#endif /* MAP_OPERATIONS_H_ */
