


#ifndef SECURE_FLAGS_H
#define SECURE_FLAGS_H

#include "she_descriptor.h"
#include <stdexcept>

class SecurityFlag : public SheDescriptor {
private:
    int _bit_index;

public:
    SecurityFlag(int bit_index) : SheDescriptor(1), _bit_index(bit_index) {}

    inline void set(void* obj, bool value) {
        int& fid = *static_cast<int*>(obj);
        if (value) {
            fid |= (1 << _bit_index);
        } else {
            fid &= ~(1 << _bit_index);
        }
    }

    inline bool get(void* obj) const {
        int fid = *static_cast<int*>(obj);
        return fid & (1 << _bit_index);
    }
};





class SecurityFlags {
private:
    unsigned char _fid;

public:
    SecurityFlag write_protection;
    SecurityFlag boot_protection;
    SecurityFlag debugger_protection;
    SecurityFlag key_usage;
    SecurityFlag wildcard;
    SecurityFlag cmac_usage;

    SecurityFlags()
        : _fid(0),
          write_protection(5),
          boot_protection(4),
          debugger_protection(3),
          key_usage(2),
          wildcard(1),
          cmac_usage(0) {}

    SecurityFlags(const unsigned char flag) 
        : _fid(flag),
            write_protection(5),
            boot_protection(4),
            debugger_protection(3),
            key_usage(2),
            wildcard(1),
            cmac_usage(0) {}


    inline int get_fid() const {
        return _fid;
    }

    inline void set_fid(int fid) {
        if (fid < 0 || fid > 63) {
            throw std::invalid_argument("fid must be between 0 and 63");
        }
        _fid = fid;
    }
};






#endif 