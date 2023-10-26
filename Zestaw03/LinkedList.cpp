#include "LinkedList.hpp"
#include <iostream>
#include <vector>
#include <sstream>

#define PUSH_FRONT 'F'
#define PUSH_BACK 'B'
#define POP_FIRST 'f'
#define POP_LAST 'b'
#define REPLACE 'R'
#define SIZE 'S'
#define LIST_EMPTY_PROMPT "EMPTY"
#define REPLACE_SUCCESS "TRUE"
#define REPLACE_FAILED "FALSE"

void split_string(std::vector<std::string>&v, std::string &str) {
    std::stringstream ss(str);
    std::string substr;
    while (ss >> substr) {
        std::cout << substr;
        v.push_back(substr);
    }
}

int main()
{
    int n_operations;
    std::cin >> n_operations;
    std::cin.ignore();
    std::string line;

    LinkedList<int> list = LinkedList<int>();
    std::vector<std::string> line_split;

    for (int i = 0; i < n_operations; i++) {
        line_split.clear();
        std::getline(std::cin, line);
        
        split_string(line_split, line);
        char operation = line_split[0][0];

        if (operation == PUSH_FRONT) {
            int to_push = std::stoi(line_split[1]);
            list.push_front(to_push);
        }
        if (operation == PUSH_BACK) {
            int to_push = std::stoi(line_split[1]);
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
            int oldv = std::stoi(line_split[1]);
            int newv = std::stoi(line_split[2]);
            int idx = list.find(oldv);
            std::cout << oldv + newv;
            // return 0;
            if (idx == -1) {
                std::cout << REPLACE_FAILED << std::endl;
            } else {
                list.insert(idx, newv);
                list.erase(idx);
                std::cout << REPLACE_SUCCESS << std::endl;
            }
        }
        if (operation == SIZE)
            std::cout << list.size() << std::endl; 
    }
    return 0;
}
