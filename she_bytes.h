/**
 * @file she_bytes.h
 * @author liwenchao (leewckk@126.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef SHE_BYTES_H
#define SHE_BYTES_H



#include <vector>
#include <string>


class SheBytes : public std::vector<unsigned char> {
public:
    SheBytes() : std::vector<unsigned char>() {}
    
    // Constructor with size
    SheBytes(const size_t size) : std::vector<unsigned char>(size, 0x00) {}

    // Constructor with size and value
    SheBytes(const size_t size, unsigned char value) : std::vector<unsigned char>(size, value) {}

    SheBytes(const std::vector<unsigned char>& bytes) : std::vector<unsigned char>(bytes) {}
    
    // Constructor from iterators
    template <typename InputIt>
    SheBytes(InputIt first, InputIt last) : std::vector<unsigned char>(first, last) {}

    SheBytes(std::initializer_list<unsigned char> ilist) : std::vector<unsigned char>(ilist) {}

    SheBytes(const std::string& hex);

    SheBytes operator^(const SheBytes& other) const ;
    SheBytes& operator=(const SheBytes& other);

    // Overloaded << operator
    friend std::ostream& operator<<(std::ostream& os, const SheBytes& sheBytes) ;
    friend bool operator==(const SheBytes& lhs, const SheBytes& rhs); 
};



#endif