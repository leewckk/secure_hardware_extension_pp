/**
 * @file secure_flags.h
 * @author liwenchao (leewckk@126.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#ifndef SECURE_FLAGS_H
#define SECURE_FLAGS_H

#include <stdexcept>


#define SECURITY_FLAG_WRITE_PROTECTION          (0x01 << 5)
#define SECURITY_FLAG_BOOT_PROTECTION           (0x01 << 4)
#define SECURITY_FLAG_DEBUGGER_PROTECTION       (0x01 << 3)
#define SECURITY_FLAG_KEY_USAGE                 (0x01 << 2)
#define SECURITY_FLAG_WILDCARD                  (0x01 << 1)
#define SECURITY_FLAG_CMAC_USAGE                (0x01 << 0)


class SecurityFlags {
private:
    unsigned char _fid;

public:
    SecurityFlags()
        : _fid(0)
        {}

    SecurityFlags(const unsigned char flag) 
        : _fid(flag)
        {}
        

    inline int get_fid() const {
        return _fid;
    }

    inline void set_fid(unsigned char fid) {
        _fid = fid;
    }
};






#endif 