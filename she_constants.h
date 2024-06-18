/**
 * @file she_constants.h
 * @author liwenchao (leewckk@126.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#ifndef SHE_CONSTANTS_H
#define SHE_CONSTANTS_H


#include <vector>
#include <string>

#include "she_bytes.h"

class SheConstants {
public:

    static SheBytes KEY_UPDATE_ENC_C;
    static SheBytes KEY_UPDATE_MAC_C;
    static SheBytes DEBUG_KEY_C;
    static SheBytes PRNG_KEY_C;
    static SheBytes PRNG_SEED_KEY_C;
    static SheBytes PRNG_EXTENSION_C;
};



#endif


