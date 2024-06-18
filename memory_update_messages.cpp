/**
 * @file memory_update_messages.cpp
 * @author liwenchao (leewckk@126.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include "memory_update_messages.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const MemoryUpdateMessages& message) {

    os <<"auth key: "<< message.auth_key<<", M1: "<<message.M1<<", M2: "<< message.M2<<std::endl;
    return os;
}