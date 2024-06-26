/**
 * @file memory_update_protocol.cpp
 * @author liwenchao (leewckk@126.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include "memory_update_protocol.h"
#include "she_bytes.h"
#include "crypto_common.h"
#include "she_constants.h"

/**
 * @brief 
 * 
 * @return SheBytes 
 */
SheBytes MemoryUpdateProtocol::get_k1() {
    return CryptoCommon::aesmp(update_info_.get_auth_key(), SheConstants::KEY_UPDATE_ENC_C);
}

/**
 * @brief 
 * 
 * @return SheBytes 
 */
SheBytes MemoryUpdateProtocol::get_k2() {
    return CryptoCommon::aesmp(update_info_.get_auth_key(), SheConstants::KEY_UPDATE_MAC_C);
}

/**
 * @brief 
 * 
 * @return SheBytes 
 */
SheBytes MemoryUpdateProtocol::get_k3() {
    return CryptoCommon::aesmp(update_info_.get_new_key(), SheConstants::KEY_UPDATE_ENC_C);
}

/**
 * @brief 
 * 
 * @return SheBytes 
 */
SheBytes MemoryUpdateProtocol::get_k4() {
    return CryptoCommon::aesmp(update_info_.get_new_key(), SheConstants::KEY_UPDATE_MAC_C);
}


/**
 * @brief 
 * 
 * @return SheBytes 
 */
SheBytes MemoryUpdateProtocol::get_m1() {
    SheBytes m1 = update_info_.get_uid();
    m1.push_back((update_info_.get_new_key_id() << 4) | update_info_.get_auth_key_id());
    return m1;
}


/**
 * @brief 
 * 
 * @return SheBytes 
 */
SheBytes MemoryUpdateProtocol::get_m2() {
    uint32_t counter = update_info_.get_counter();
    uint8_t fid = update_info_.get_flags().get_fid();

    SheBytes m2_plain(16);
    counter = counter << 4;
    m2_plain[0] = (counter >> 24) & 0xFF;
    m2_plain[1] = (counter >> 16) & 0xFF;
    m2_plain[2] = (counter >> 8) & 0xFF;
    m2_plain[3] = (counter & 0xFF) | ((fid >> 2) & 0xF0);
    m2_plain[4] = (fid << 6) & 0xC0;

    SheBytes new_key = update_info_.get_new_key();
    m2_plain.insert(m2_plain.end(), new_key.begin(), new_key.end());

    SheBytes iv(16, 0);
    return CryptoCommon::encrypt_aes_cbc(get_k1(), m2_plain, iv);
}


/**
 * @brief 
 * 
 * @return SheBytes 
 */
SheBytes MemoryUpdateProtocol::get_m3() {
    SheBytes m1 = get_m1();
    SheBytes m2 = get_m2();

    SheBytes data(m1);
    data.insert(data.end(), m2.begin(), m2.end());

    return CryptoCommon::cmac_aes(get_k2(), data);
}

/**
 * @brief 
 * 
 * @return SheBytes 
 */
SheBytes MemoryUpdateProtocol::get_m4() {
    uint32_t counter = update_info_.get_counter();
    counter = counter << 4;

    SheBytes m4(16);
    m4[0] = (counter >> 24) & 0xFF;
    m4[1] = (counter >> 16) & 0xFF;
    m4[2] = (counter >> 8) & 0xFF;
    m4[3] = counter & 0xFF | (0x01 << 3);

    // std::cout<<"m4_plain :" << m4 << std::endl;
    m4 = CryptoCommon::encrypt_aes_ecb(get_k3(), m4);
    SheBytes m1 = get_m1();
    m4.insert(m4.begin(), m1.begin(), m1.end());

    return m4;
}

SheBytes MemoryUpdateProtocol::get_m5() {
    return CryptoCommon::cmac_aes(get_k4(), get_m4());
}


/**
 * @brief 
 * 
 * @param update_messages 
 * @return MemoryUpdateInfo 
 */
MemoryUpdateInfo MemoryUpdateProtocol::decrypt_using_messages(const MemoryUpdateMessages& update_messages) {
    
    SheBytes m1 = update_messages.get_m1();
    SheBytes m2 = update_messages.get_m2();
    SheBytes auth_key = update_messages.get_auth_key();

    SheBytes uid(m1.begin(), m1.begin() + 15);
    uint8_t auth_key_id = m1[15] & 0x0F;
    uint8_t new_key_id = (m1[15] & 0xF0) >> 4;

    SheBytes k1 = CryptoCommon::aesmp(auth_key, SheConstants::KEY_UPDATE_ENC_C);
    SheBytes iv(16, 0);
    SheBytes m2_plain = CryptoCommon::decrypt_aes_cbc(k1, m2, iv);

    uint32_t counter = (m2_plain[0] << 24) | (m2_plain[1] << 16) | (m2_plain[2] << 8) | (m2_plain[3] & 0xF0) >> 4;
    uint8_t fid = ((m2_plain[3] & 0x0F) << 2) | ((m2_plain[4] & 0xC0) >> 6);

    SecurityFlags flags(fid);
    SheBytes new_key(m2_plain.begin() + 16, m2_plain.begin() + 32);

    return MemoryUpdateInfo(new_key, auth_key, new_key_id, auth_key_id, counter, uid, flags);
}
