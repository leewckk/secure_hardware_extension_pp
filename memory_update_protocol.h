/**
 * @file memory_update_protocol.h
 * @author liwenchao (leewckk@126.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#ifndef MEMORY_UPDATE_PROTOCOL_H
#define MEMORY_UPDATE_PROTOCOL_H


#include <iostream>
#include <vector>
#include <stdexcept>

#include "secure_flags.h"
#include "memory_update_info.h"
#include "memory_update_messages.h"
#include "she_constants.h"


class MemoryUpdateProtocol {
public:
    MemoryUpdateProtocol(const MemoryUpdateInfo &update_info)
        : update_info_(update_info) {}

    MemoryUpdateProtocol(const MemoryUpdateMessages &update_messages) {
        update_info_ = MemoryUpdateProtocol::decrypt_using_messages(update_messages);
    }

    SheBytes get_k1();
    SheBytes get_k2();
    SheBytes get_k3();
    SheBytes get_k4();
    SheBytes get_m1();
    SheBytes get_m2();
    SheBytes get_m3();
    SheBytes get_m4();
    SheBytes get_m5();
   
   static MemoryUpdateInfo decrypt_using_messages(const MemoryUpdateMessages& update_messages) ;

    static const SheBytes KEY_UPDATE_ENC_C;// SheConstants::KEY_UPDATE_ENC_C();
    static const SheBytes KEY_UPDATE_MAC_C;// SheConstants::KEY_UPDATE_MAC_C();
private:

    MemoryUpdateInfo update_info_;

};

#endif 