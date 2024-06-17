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

using namespace CryptoPP;

class MemoryUpdateProtocol {
public:
    MemoryUpdateProtocol(const MemoryUpdateInfo &update_info)
        : update_info_(update_info) {}

    MemoryUpdateProtocol(const MemoryUpdateMessages &update_messages) {
        update_info_ = decrypt_using_messages(update_messages);
    }

    SheBytes get_k1() {
        return compress(update_info_.get_auth_key(), KEY_UPDATE_ENC_C);
    }

    SheBytes get_k2() {
        return compress(update_info_.get_auth_key(), KEY_UPDATE_MAC_C);
    }

    SheBytes get_k3() {
        return compress(update_info_.get_new_key(), KEY_UPDATE_ENC_C);
    }

    SheBytes get_k4() {
        return compress(update_info_.get_new_key(), KEY_UPDATE_MAC_C);
    }

    SheBytes get_m1() {
        SheBytes m1 = update_info_.get_uid();
        m1.push_back((update_info_.get_new_key_id() << 4) | update_info_.get_auth_key_id());
        return m1;
    }

    SheBytes get_m2() {
        uint32_t counter = update_info_.get_counter();
        uint8_t fid = update_info_.get_flags().get_fid();

        SheBytes m2_plain(16);
        m2_plain[0] = (counter >> 24) & 0xFF;
        m2_plain[1] = (counter >> 16) & 0xFF;
        m2_plain[2] = (counter >> 8) & 0xFF;
        m2_plain[3] = (counter & 0xFF) | ((fid >> 2) & 0xF0);
        m2_plain[4] = (fid << 6) & 0xC0;

        SheBytes new_key = update_info_.get_new_key();
        m2_plain.insert(m2_plain.end(), new_key.begin(), new_key.end());

        SheBytes iv(16, 0);
        return encrypt_aes_cbc(get_k1(), m2_plain, iv);
    }

    SheBytes get_m3() {
        SheBytes m1 = get_m1();
        SheBytes m2 = get_m2();

        SheBytes data(m1);
        data.insert(data.end(), m2.begin(), m2.end());

        return cmac_aes(get_k2(), data);
    }

    SheBytes get_m4() {
        uint32_t counter = update_info_.get_counter();
        counter |= (1 << 28);

        SheBytes m4(16);
        m4[0] = (counter >> 24) & 0xFF;
        m4[1] = (counter >> 16) & 0xFF;
        m4[2] = (counter >> 8) & 0xFF;
        m4[3] = counter & 0xFF;

        m4 = encrypt_aes_ecb(get_k3(), m4);

        SheBytes m1 = get_m1();
        m4.insert(m4.begin(), m1.begin(), m1.end());

        return m4;
    }

    SheBytes get_m5() {
        return cmac_aes(get_k4(), get_m4());
    }

private:
    static const SheBytes KEY_UPDATE_ENC_C;
    static const SheBytes KEY_UPDATE_MAC_C;

    MemoryUpdateInfo update_info_;

    SheBytes compress(const SheBytes& key, const SheBytes& message) {
        ECB_Mode<AES>::Encryption aes;
        aes.SetKey(key.data(), key.size());

        SheBytes result(key.size());
        aes.ProcessData(result.data(), message.data(), message.size());

        SheBytes compressed(result.size());
        for (size_t i = 0; i < result.size(); ++i) {
            compressed[i] = key[i] ^ result[i] ^ message[i];
        }

        return compressed;
    }

    SheBytes encrypt_aes_cbc(const SheBytes& key, const SheBytes& data, const SheBytes& iv) {
        CBC_Mode<AES>::Encryption aes;
        aes.SetKeyWithIV(key.data(), key.size(), iv.data());

        SheBytes encrypted(data.size());
        aes.ProcessData(encrypted.data(), data.data(), data.size());

        return encrypted;
    }

    SheBytes encrypt_aes_ecb(const SheBytes& key, const SheBytes& data) {
        ECB_Mode<AES>::Encryption aes;
        aes.SetKey(key.data(), key.size());

        SheBytes encrypted(data.size());
        aes.ProcessData(encrypted.data(), data.data(), data.size());

        return encrypted;
    }

    SheBytes cmac_aes(const SheBytes& key, const SheBytes& data) {
        CMAC<AES> cmac(key.data(), key.size());
        cmac.Update(data.data(), data.size());

        SheBytes result(cmac.DigestSize());
        cmac.Final(result.data());

        return result;
    }

    MemoryUpdateInfo decrypt_using_messages(const MemoryUpdateMessages& update_messages) {
        
        SheBytes uid(update_messages.get_m1().begin(), update_messages.get_m1().begin() + 15);
        uint8_t auth_key_id = update_messages.get_m1()[15] & 0x0F;
        uint8_t new_key_id = (update_messages.get_m1()[15] & 0xF0) >> 4;

        SheBytes k1 = compress(update_messages.get_auth_key(), KEY_UPDATE_ENC_C);
        SheBytes iv(16, 0);
        SheBytes m2_plain = encrypt_aes_cbc(k1, update_messages.get_m2(), iv);

        uint32_t counter = (m2_plain[0] << 24) | (m2_plain[1] << 16) | (m2_plain[2] << 8) | (m2_plain[3] & 0xF0) >> 4;
        uint8_t fid = ((m2_plain[3] & 0x0F) << 2) | ((m2_plain[4] & 0xC0) >> 6);

        SecurityFlags flags(fid);

        SheBytes new_key(m2_plain.begin() + 16, m2_plain.begin() + 32);

        return MemoryUpdateInfo(new_key, update_messages.get_auth_key(), new_key_id, auth_key_id, counter, uid, flags);
    }
};

#endif 