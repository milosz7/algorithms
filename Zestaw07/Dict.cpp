#include "Dict.hpp"
#include <string>
#include <fstream>
#include <iostream>

constexpr int N_ARGS = 2;

int main(int argc, char const *argv[])
{
    if (argc != N_ARGS) {
        std::cerr << "Incorrect amount of arguments provided!" << std::endl;
        return 1;
    }

    // I want approximately 3 elements per bucket and there are 65000 pairs in the test case
    // 65000 / 3 = 21666 so I choose a prime number of buckets close to that number which is 21647
    Dict<std::string, std::string> dict = Dict<std::string, std::string>(21647);
    const char* filename = argv[1];

    std::ifstream pairs_file{filename};
    std::string key, value;

    while (pairs_file >> key && pairs_file >> value) {
        dict[key] = value;
    }
    pairs_file.close();
    
    while (std::cin >> key) {
        if (dict.find(key))
            std::cout << dict[key] << std::endl;
        else
            std::cout << "-" << std::endl;
    }


    return 0;
}
