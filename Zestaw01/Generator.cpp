#include <random>
#include <iostream>
#include <chrono>
#include <stdexcept>

#define N_ARGUMENTS 2
#define N_OPERATIONS 3
#define MAX_INT 1000000
#define MAX_OPERATIONS 1000000

int main(int argc, char *argv[]) {
    if (argc != N_ARGUMENTS) {
        std::cerr << "Please provide an amount of operations to generate.";
        return 1;
    }

    int amt_to_generate = std::stoi(argv[1]);
    if (amt_to_generate < 0 || amt_to_generate > MAX_OPERATIONS)
        throw std::invalid_argument("You can only pass an integer from 1 to 1e6!");

    enum outcomes {
        A = 0,
        D = 1,
        S = 2
    };

    std::cout << amt_to_generate << std::endl;
    std::srand(std::time(0));

    for (int i = 0; i < amt_to_generate; i++) {
        int operation = std::rand() % N_OPERATIONS;
        if (operation == A)
            std::cout << "A" << " " << std::rand() % (MAX_INT + 1) << std::endl;
        if (operation == D)
            std::cout << "D" << std::endl;
        if (operation == S)
            std::cout << "S" << std::endl;
    }
    return 0;
}