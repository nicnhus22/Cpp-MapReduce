/*
 * File_Operations.h
 *
 *  Created on: Jan 23, 2014
 *      Author: nicolas.husser
 */

#ifndef MATH_OPERATIONS_H_
#define MATH_OPERATIONS_H_

#include <string>
#include <unordered_map>
#include <vector>

double scalar_product(const std::unordered_map<std::string, int> & a,const std::unordered_map<std::string, int> & b);
double multiplyNorms(const std::unordered_map<std::string, int> & a,const std::unordered_map<std::string, int> & b);

double scalar_product(const std::unordered_map<std::string, double> & a,const std::unordered_map<std::string, double> & b);
double multiplyNorms(const std::unordered_map<std::string, double> & a,const std::unordered_map<std::string, double> & b);

std::unordered_map<std::string, double> computeWeight(std::unordered_map<std::string, int> & DOC_APPEAR, std::unordered_map<std::string, int> & MAP_FREQ, long FILE_COUNT);

#endif /* MATHS_OPERATIONS_H_ */
