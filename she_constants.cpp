/**
 * @file she_constants.cpp
 * @author liwenchao (leewckk@126.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "she_constants.h"


SheBytes SheConstants::KEY_UPDATE_ENC_C = SheBytes("010153484500800000000000000000B0");
SheBytes SheConstants::KEY_UPDATE_MAC_C = SheBytes("010253484500800000000000000000B0");
SheBytes SheConstants::DEBUG_KEY_C = SheBytes("010353484500800000000000000000B0");
SheBytes SheConstants::PRNG_KEY_C = SheBytes("010453484500800000000000000000B0");
SheBytes SheConstants::PRNG_SEED_KEY_C = SheBytes("010553484500800000000000000000B0");
SheBytes SheConstants::PRNG_EXTENSION_C = SheBytes("80000000000000000000000000000100");
