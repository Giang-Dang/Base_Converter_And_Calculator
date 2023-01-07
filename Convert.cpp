#include "Convert.h"

std::string convertDecToBin(std::string decStr) {
    unsigned long long decNum = std::stoi(decStr);
    std::string binStr = "";
    while (decNum != 0) {
        binStr = std::to_string(decNum % 2) + binStr;
        decNum /= 2;
    }
    return binStr;
}

std::string convertDecToHex(std::string decStr) {
    std::string hexValues = "0123456789ABCDEF";
    unsigned long long decNum = std::stoi(decStr);
    std::string hexStr = "";
    while (decNum != 0) {
        hexStr = hexValues[decNum % 16] + hexStr;
        decNum /= 16;
    }
    return hexStr;
}

std::string convertBinToDec(std::string binStr) {
    unsigned long long decNum = 0;
    float exp = 0;
    while(binStr != "") {
        if(binStr.back() == '1') {
            decNum += pow(2.0, exp);
        }
        exp++;
        binStr.pop_back(); 
    }
    return std::to_string(decNum);
}

std::string convertHexToDec(std::string hexStr) {
    std::string hexValues = "0123456789ABCDEF";
    unsigned long long decNum = 0;
    float exp = 0;
    while(hexStr != "") {
        char digit = hexStr.back();
        decNum += hexValues.find(digit) * pow(16.0, exp);
        exp++;
        hexStr.pop_back();
    }
    return std::to_string(decNum);
}

std::string convertBinToHex(std::string binStr) {
    std::string decStr = convertBinToDec(binStr);
    return convertDecToHex(decStr);
}