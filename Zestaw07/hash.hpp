#ifndef HASH_H
#define HASH_H
#include <string>
#include <cstring>
#include <math.h>
#include <limits.h>

// https://en.wikipedia.org/wiki/Jenkins_hash_function
unsigned code(const std::string &s) {
    unsigned code = 0;
    int i = 0;
    uint8_t character = s[i];
    while (character != 0) {
        code += character;
        code += code << 10;
        code ^= code >> 6;
        character = s[i++];
    }
    code += code << 3;
    code ^= code >> 11;
    code += code << 15;
    return code;
}

unsigned code(const unsigned key) { return key; }

unsigned code(const int key) { return abs(key); }

unsigned code(const float key) {
    unsigned output;
    // represent float as unsigned using its bits
    std::memcpy(&output, &key, sizeof(unsigned));
    return output;
}

unsigned code(const double key) {
    unsigned output;
    // represent float as unsigned using its bits
    std::memcpy(&output, &key, sizeof(unsigned));
    return output;
}

size_t hash(unsigned code, int n_buckets) {
    int p = INT32_MAX;
    size_t hash;
    hash = code % p % n_buckets; 
    return hash;
}

#endif