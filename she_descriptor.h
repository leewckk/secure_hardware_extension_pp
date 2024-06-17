/**
 * @file she_descriptor.h
 * @author liwenchao (leewckk@126.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#ifndef SHE_DESCRIPTOR_H
#define SHE_DESCRIPTOR_H



#include <string>

class SheDescriptor {
protected:
    std::string _attribute_name;
    size_t _bit_size;

public:
    SheDescriptor(size_t bit_size) : _bit_size(bit_size) {}

    virtual void set_name(const std::string& name) ;
};

#endif //SHE_DESCRIPTOR_H