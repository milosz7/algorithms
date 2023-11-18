#include "InsertionSort.hpp"
#include <iostream>
#include <chrono>

int main()
{
    std::vector<int> to_sort;
    int number;
    while (std::cin >> number) {
        to_sort.push_back(number);
    }

    // uncomment for time measurements
    // auto t_start = std::chrono::high_resolution_clock::now();
    sort<int>(to_sort);
    // auto t_end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> t_execution = t_end - t_start;
    // std::cout << to_sort.size() << "," << t_execution.count() <<std::endl;
    
    // comment out for time measurements
    for (const auto& num : to_sort) {
        std::cout << num << std::endl;
    }

    return 0;
}




