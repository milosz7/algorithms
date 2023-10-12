#include <iostream>
#include <string>
#include "LinkedStack.hpp"

#define POP_OPERATION 'D'
#define SIZE_OPERATION 'S'
#define PUSH_OPERATION 'A'
#define STACK_EMPTY_PROMPT "EMPTY"
#define NUM_START_IDX 2

int main() {
    int n_operations;
    std::cin >> n_operations;
    std::cin.ignore();
    std::string line;
    // initialising stack with capacity of n_operations because
    // there is a chance that all operations will be push operations
    LinkedStack stack = LinkedStack(n_operations);

    for (int i = 0; i < n_operations; i++) {

        std::getline(std::cin, line);
        char operation = line[0];
        if (operation == POP_OPERATION) {
            bool is_empty = stack.empty();
            if (is_empty)
                std::cout << STACK_EMPTY_PROMPT << std::endl;
            if (!is_empty)
                std::cout << stack.pop() << std::endl;
        }
        if (operation == SIZE_OPERATION) {
            std::cout <<  stack.size() << std::endl;
        }
        if (operation == PUSH_OPERATION) {
            int to_push = std::stoi(line.substr(NUM_START_IDX));
            stack.push(to_push);
        }
    }
}