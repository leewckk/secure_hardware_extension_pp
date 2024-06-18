/**
 * @file memory_update_info.cpp
 * @author liwenchao (leewckk@126.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include "memory_update_info.h"
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
std::ostream& operator<<(std::ostream& os, const MemoryUpdateInfo& info) {

    // new_key_id
    os << "new_key_id: " 
       << std::hex << std::setw(2) << std::setfill('0') 
       << static_cast<int>(info.get_new_key_id()) << std::dec; // Restore to decimal
    os << ", data: " << info.get_new_key() << std::endl;

    // auth_key_id
    os << "auth_key_id: " 
       << std::hex << std::setw(2) << std::setfill('0') 
       << static_cast<int>(info.get_auth_key_id()) << std::dec; // Restore to decimal
    os << " data: " << info.get_auth_key() << std::endl;

    // uid
    os << "uid: " << info.get_uid() << std::endl;
    // counter and flags
    os << "counter: " << info.get_counter() 
       << " , flags: " << info.get_flags() << std::endl;

    return os;
}