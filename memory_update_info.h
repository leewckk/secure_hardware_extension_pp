

#ifndef MEMORY_UPDATE_INFO_H
#define MEMORY_UPDATE_INFO_H

#include "she_bytes.h"
#include "secure_flags.h"

class MemoryUpdateInfo {
    
protected:
    SheBytes new_key;
    SheBytes auth_key;
    int new_key_id;
    int auth_key_id;
    int counter;
    SheBytes uid;
    int fid;
    SecurityFlags flags;

public:

    MemoryUpdateInfo(){}

    MemoryUpdateInfo(
        const SheBytes& new_key,
        const SheBytes& auth_key,
        int new_key_id,
        int auth_key_id,
        int counter,
        const SheBytes& uid,
        const SecurityFlags& flags)
        : new_key(new_key),
          auth_key(auth_key),
          new_key_id(new_key_id),
          auth_key_id(auth_key_id),
          counter(counter),
          uid(uid),
          flags(flags) {
        this->fid = flags.get_fid();
    }

    MemoryUpdateInfo(const MemoryUpdateInfo& info) :
        new_key(info.new_key),
        auth_key(info.auth_key),
        new_key_id(info.new_key_id),
        auth_key_id(info.auth_key_id),
        counter(info.counter),
        uid(info.uid),
        fid(info.fid),
        flags(info.flags) {

    }

    // Assignment operator
    MemoryUpdateInfo& operator=(const MemoryUpdateInfo& other) {
        if (this == &other) {
            return *this; // handle self assignment
        }
        new_key = other.new_key;
        auth_key = other.auth_key;
        new_key_id = other.new_key_id;
        auth_key_id = other.auth_key_id;
        counter = other.counter;
        uid = other.uid;
        fid = other.fid;
        flags = other.flags;
        return *this;
    }


    inline SecurityFlags get_flags() const {
        return flags;
    }

    inline void set_flags(const SecurityFlags& flags) {
        this->flags = flags;
        this->fid = flags.get_fid();
    }

    inline SheBytes get_new_key() const {
        return new_key;
    }

    inline SheBytes get_auth_key() const {
        return auth_key;
    }

    inline uint8_t get_new_key_id() const {
        return new_key_id;
    }

    inline uint8_t get_auth_key_id() const {
        return auth_key_id;
    }

    inline uint32_t get_counter() const {
        return counter;
    }

    inline SheBytes get_uid() const {
        return uid;
    }

};


#endif 
