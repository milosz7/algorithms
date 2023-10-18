#include <iostream>
#include <string>
#include "ArrayQueue.hpp"
#include "LinkedQueue.hpp"

#define POP_OPERATION 'D'
#define SIZE_OPERATION 'S'
#define PUSH_OPERATION 'A'
#define QUEUE_EMPTY_PROMPT "EMPTY"
#define NUM_START_IDX 2

int main()
{
    int n_operations;
    std::cin >> n_operations;
    std::cin.ignore();
    std::string line;
    // initialising queue with capacity of n_operations because
    // there is a chance that all operations will be push operations
    // uncomment the preferred queue implementation
    
    // ArrayQueue<int> queue = ArrayQueue<int>(n_operations);
    LinkedQueue<int> queue = LinkedQueue<int>(n_operations);

    for (int i = 0; i < n_operations; i++)
    {
        std::getline(std::cin, line);
        char operation = line[0];
        if (operation == POP_OPERATION)
        {
            bool is_empty = queue.empty();
            if (is_empty)
                std::cout << QUEUE_EMPTY_PROMPT << std::endl;
            if (!is_empty)
                std::cout << queue.pop() << std::endl;
        }
        if (operation == SIZE_OPERATION)
        {
            std::cout << queue.size() << std::endl;
        }
        if (operation == PUSH_OPERATION)
        {
            int to_push = std::stoi(line.substr(NUM_START_IDX));
            queue.push(to_push);
        }
    }
    return 0;
}
