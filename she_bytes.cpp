/**
 * @file she_bytes.cpp
 * @author liwenchao (leewckk@126.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include <iostream>
#include <stdexcept>
#include <vector>
#include <bitset>
#include <iomanip>
#include <sstream>
#include <string>
#include "she_bytes.h"

/**
 * @brief Construct a new She Bytes Base:: She Bytes Base object
 * 
 * @param hex 
 */
SheBytes::SheBytes(const std::string& hex){

    if (hex.length() % 2 != 0) {
        throw std::invalid_argument("Hex string must have an even length");
    }
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        unsigned char byte = (unsigned char) strtol(byteString.c_str(), nullptr, 16);
        push_back(byte);
    }
}


/**
 * @brief 
 * 
 * @param other 
 * @return SheBytes 
 */
SheBytes SheBytes::operator^(const SheBytes& other) const {

    if (size() != other.size()) {
        throw std::invalid_argument("Cannot XOR SheBytes with different lengths");
    }
    SheBytes result;
    for (size_t i = 0; i < size(); ++i) {
        result.push_back(at(i) ^ other.at(i));
    }
    return result;

}



///////////////////////////////////// SheBytes implementation /////////////////////////////////



