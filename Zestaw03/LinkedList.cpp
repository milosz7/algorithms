#include "LinkedList.hpp"
#include <iostream>

#define PUSH_FRONT 'F'
#define PUSH_BACK 'B'
#define POP_FIRST 'f'
#define POP_LAST 'b'
#define REPLACE 'R'
#define SIZE 'S'
#define LIST_EMPTY_PROMPT "EMPTY"
#define REPLACE_SUCCESS "TRUE"
#define REPLACE_FAILED "FALSE"

int main()
{
    int n_operations;
    char operation;
    std::cin >> n_operations;

    LinkedList<int> list = LinkedList<int>();

    for (int i = 0; i < n_operations; i++) {
        std::cin >> operation;

        if (operation == PUSH_FRONT) {
            int to_push;
            std::cin >> to_push;
            list.push_front(to_push);
        }
        if (operation == PUSH_BACK) {
            int to_push;
            std::cin >> to_push;
            list.push_back(to_push);
        }
        if (operation == POP_FIRST) {
            bool is_empty = list.empty();
            if (is_empty) {
                std::cout << LIST_EMPTY_PROMPT << std::endl;
            }
            if (!is_empty) {
                std::cout << list.pop_front() << std::endl;
            }
        }
        if (operation == POP_LAST) {
            bool is_empty = list.empty();
            if (is_empty) {
                std::cout << LIST_EMPTY_PROMPT << std::endl;
            }
            if (!is_empty) {
                std::cout << list.pop_back() << std::endl;
            }
        }
        if (operation == REPLACE) {
            int oldv;
            int newv;
            std::cin >> oldv >> newv;
            int idx = list.find(oldv);
            if (idx == -1) {
                std::cout << REPLACE_FAILED << std::endl;
            } else {
                list.insert(idx, newv);
                list.erase(idx + 1);
                std::cout << REPLACE_SUCCESS << std::endl;
            }
        }
        if (operation == SIZE)
            std::cout << list.size() << std::endl;
    }
    return 0;
}
