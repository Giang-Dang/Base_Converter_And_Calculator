#ifndef CALCULATION_H
#define CALCULATION_H

#include <iostream>
#include <math.h>
#include <bitset>
#include <vector>

const unsigned int MAX_BITSET = 8;

std::string addBinNum(std::string str_binNum1, std::string str_binNum2);
std::string subtractBinNum(std::string str_binNum1, std::string str_binNum2);
std::string multiplyBinNum(std::string str_binNum1, std::string str_binNum2);
std::vector<std::string> divideBinNum(std::string str_binNum1, std::string str_binNum2);

std::bitset<MAX_BITSET> addBinNum_IgnoreOverFlowCheck(std::string str_binNum1, std::string str_binNum2);
std::bitset<MAX_BITSET> subtractBinNum_IgnoreOverflowCheck(std::string str_binNum1, std::string str_binNum2);
std::bitset<MAX_BITSET> convertToPositive_2Complement(std::bitset<MAX_BITSET> binNum);
std::bitset<MAX_BITSET> convertToNegative_2Complement(std::bitset<MAX_BITSET> binNum);

#endif
