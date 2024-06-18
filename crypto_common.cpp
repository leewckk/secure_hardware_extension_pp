/**
 * @file crypto_common.cpp
 * @author liwenchao (leewckk@126.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "crypto_common.h"
#include <crypto++/aes.h>
#include <crypto++/modes.h>
#include <crypto++/cmac.h>
#include <crypto++/secblock.h>
#include <crypto++/osrng.h>
#include <crypto++/filters.h>
#include <crypto++/hex.h>

using namespace CryptoPP;
/**
 * @brief 
 * 
 * @param key 
 * @param data 
 * @param iv 
 * @return SheBytes 
 */
SheBytes CryptoCommon::encrypt_aes_cbc(const SheBytes& key, const SheBytes& data, const SheBytes& iv) {
    CBC_Mode<AES>::Encryption aes;
    aes.SetKeyWithIV(key.data(), key.size(), iv.data());

    SheBytes encrypted(data.size());
    aes.ProcessData(encrypted.data(), data.data(), data.size());

    return encrypted;
}

/**
 * @brief 
 * 
 * @param key 
 * @param data 
 * @return SheBytes 
 */
SheBytes CryptoCommon::encrypt_aes_ecb(const SheBytes& key, const SheBytes& data) {
    ECB_Mode<AES>::Encryption aes;
    aes.SetKey(key.data(), key.size());

    SheBytes encrypted(data.size());
    aes.ProcessData(encrypted.data(), data.data(), data.size());

    return encrypted;
}

/**
 * @brief 
 * 
 * @param key 
 * @param data 
 * @return SheBytes 
 */
SheBytes CryptoCommon::cmac_aes(const SheBytes& key, const SheBytes& data) {
    CMAC<AES> cmac(key.data(), key.size());
    cmac.Update(data.data(), data.size());

    SheBytes result(cmac.DigestSize());
    cmac.Final(result.data());

    return result;
}

/**
 * @brief 
 * 
 * @param key 
 * @param message 
 * @return SheBytes 
 */
SheBytes CryptoCommon::aesmp(const SheBytes& auth_key, const SheBytes& message) {

    std::vector<SheBytes> compressDataList;

    compressDataList.push_back(auth_key);
    compressDataList.push_back(message);

    SheBytes key(auth_key.size());

    
    for (SheBytes msg : compressDataList) {

        ECB_Mode<AES>::Encryption aes;
        aes.SetKey(key.data(), key.size());

        SheBytes result(auth_key.size());
        aes.ProcessData(result.data(), msg.data(), msg.size());
        key = key ^ result;
        key = key ^ msg;
    }

    return key;
}

