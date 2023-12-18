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
    // prime number bigger than number of buckets
    // it is safe to choose int max as its equal to max number
    // of buckets possible
    int p = INT32_MAX;
    // randomly chosen integers - could be further improved by randomly assigning a and b programmaticaly
    // a from range [1, p-1]
    // b from range [0, p-1]
    int a = 86847;
    int b = 1237951;
    size_t hash;
    hash = (a * code + b) % p % n_buckets; 
    return hash;
}

#endif