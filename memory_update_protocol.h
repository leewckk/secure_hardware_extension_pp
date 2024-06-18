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
#include <crypto++/aes.h>
#include <crypto++/modes.h>
#include <crypto++/cmac.h>
#include <crypto++/secblock.h>
#include <crypto++/osrng.h>
#include <crypto++/filters.h>
#include <crypto++/hex.h>

#include "secure_flags.h"
#include "memory_update_info.h"
#include "memory_update_messages.h"
#include "she_constants.h"

using namespace CryptoPP;

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
   
private:
    static const SheBytes KEY_UPDATE_ENC_C;// SheConstants::KEY_UPDATE_ENC_C();
    static const SheBytes KEY_UPDATE_MAC_C;// SheConstants::KEY_UPDATE_MAC_C();

    MemoryUpdateInfo update_info_;

    static SheBytes compress(const SheBytes& key, const SheBytes& message);
    static SheBytes encrypt_aes_cbc(const SheBytes& key, const SheBytes& data, const SheBytes& iv);
    static SheBytes encrypt_aes_ecb(const SheBytes& key, const SheBytes& data);
    static SheBytes cmac_aes(const SheBytes& key, const SheBytes& data);
    static MemoryUpdateInfo decrypt_using_messages(const MemoryUpdateMessages& update_messages) ;
};

#endif 