/**
 * @file crypto_common.h
 * @author liwenchao (leewckk@126.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#ifndef CRYPTO_COMMON_H
#define CRYPTO_COMMON_H

#include "she_bytes.h"

class CryptoCommon {
public :
    static SheBytes aesmp(const SheBytes& key, const SheBytes& message);
    static SheBytes encrypt_aes_cbc(const SheBytes& key, const SheBytes& data, const SheBytes& iv);
    static SheBytes encrypt_aes_ecb(const SheBytes& key, const SheBytes& data);

    static SheBytes decrypt_aes_cbc(const SheBytes& key, const SheBytes& data, const SheBytes& iv);
    static SheBytes decrypt_aes_ecb(const SheBytes& key, const SheBytes& data);

    static SheBytes cmac_aes(const SheBytes& key, const SheBytes& data);
 
};

#endif 