/**
 * @file memory_update_messages.h
 * @author liwenchao (leewckk@126.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#ifndef MEMORY_UPDATE_MESSAGES_H
#define MEMORY_UPDATE_MESSAGES_H

#include "she_bytes.h"

class MemoryUpdateMessages {

protected:
    SheBytes auth_key;
    SheBytes M1;
    SheBytes M2;

public:

    MemoryUpdateMessages(const SheBytes& auth_key, const SheBytes& m1, const SheBytes& m2)
        : auth_key(auth_key), M1(m1), M2(m2) {}

    MemoryUpdateMessages(const MemoryUpdateMessages& message):auth_key(message.auth_key), M1(message.M1), M2(message.M2) {

    }

    inline SheBytes get_m1() const{
        return this->M1;
    }

    inline SheBytes get_m2() const {
        return this->M2;
    }

    inline SheBytes get_auth_key() const {
        return this->auth_key;
    }

    friend std::ostream& operator<<(std::ostream& os, const MemoryUpdateMessages& message) ;
};


#endif 