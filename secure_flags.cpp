/**
 * @file secure_flags.cpp
 * @author liwenchao (leewckk@126.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include "secure_flags.h"
#include <iostream>
#include <sstream>
#include <iomanip>

/**
 * @brief 
 * 
 * @param os 
 * @param info 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& os, const SecurityFlags& info) {
    os << std::hex << std::setw(2) << std::setfill('0') << info.get_fid();
    return os;
}