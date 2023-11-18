#include <iostream>
#include <random>
#include <chrono>

constexpr int N_ARGUMENTS = 3;

int main(int argc, char const *argv[])
{
    if (argc != N_ARGUMENTS) {
        std::cerr << "Please provide an amount of operations to generate." << std::endl;
        return 1;
    }

    int n_to_generate = std::stoi(argv[1]);
    int n_max = std::stoi(argv[2]);

    std::srand(std::time(0));
    
    for (int i = 0; i < n_to_generate; i++) 
        std::cout << (std::rand() % n_max) + 1 << std::endl;
    return 0;
}
