#include <random>
#include <iostream>
#include <chrono>
#include <stdexcept>

#define N_ARGUMENTS 2
#define N_OPERATIONS 6
#define MAX_INT 1000
#define MAX_OPERATIONS 1000

int main(int argc, char *argv[]) {
    if (argc != N_ARGUMENTS) {
        std::cerr << "Please provide an amount of operations to generate.";
        return 1;
    }

    int amt_to_generate = std::stoi(argv[1]);
    if (amt_to_generate < 0 || amt_to_generate > MAX_OPERATIONS)
        throw std::invalid_argument("You can only pass an integer from 1 to 1e3!");

    enum outcomes {
        F = 0,
        B = 1,
        f = 2,
        b = 3,
        R = 4,
        S = 5,
    };

    std::cout << amt_to_generate << std::endl;
    std::srand(std::time(0));

    for (int i = 0; i < amt_to_generate; i++) {
        int operation = std::rand() % N_OPERATIONS;
        if (operation == F)
            std::cout << "F" << " " << std::rand() % (MAX_INT + 1) << std::endl;
        if (operation == B)
            std::cout << "B" << " " << std::rand() % (MAX_INT + 1) << std::endl;
        if (operation == f)
            std::cout << "f" << std::endl;
        if (operation == b)
            std::cout << "b" << std::endl;
        if (operation == R)
            std::cout << "R" << " " << std::rand() % (MAX_INT + 1) << " " << std::rand() % (MAX_INT + 1) << std::endl;
        if (operation == S)
            std::cout << "S" << std::endl;
    }
    return 0;
}
