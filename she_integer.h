/**
 * @file she_integer.h
 * @author liwenchao (leewckk@126.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef SHE_INTEGER_H
#define SHE_INTEGER_H


#include "she_descriptor.h"
#include <stdexcept>


class SheInteger : public SheDescriptor {
public:
    SheInteger(size_t bit_size) : SheDescriptor(bit_size) {}

    inline void set(void* obj, int value){

        if (value < 0) {
            throw std::invalid_argument("Value must be non-negative");
        }
        int max_value = (1 << _bit_size) - 1;
        if (value > max_value) {
            throw std::invalid_argument("Value exceeds maximum allowed for bit size");
        }
        // 设置值（假设对象有一个属性来存储整数）
        *static_cast<int*>(obj) = value;

    }
};

#endif // SHE_INTEGER_H