#include "TemplateStack.hpp"
#include <iostream>
#include <string>
#include <map>

#define STACK_SIZE 100
#define DELIMITER ' '

static bool is_digit(std::string input);
inline void print_space(bool is_empty);

static const std::map<int, int> priorities_map = {
    {'(', 0}, {')', 1}, {'+', 1},
    {'-', 1}, {'*', 2}, {'/', 2}
};

int main() {
    std::string input;
    TemplateStack<char, STACK_SIZE> stack;

    while (std::cin >> input) {
        if (is_digit(input))
            std::cout << input << DELIMITER;
            
        if (!is_digit(input)) {
            /* if the input is not a digit its an operator - which is a char, so the 0th index of a string is an operator */
            char _operator = input[0];
            if (_operator == '(') {
                stack.push(_operator);
            } else if (_operator == ')') {
                while (stack.top() != '(') {
                    std::cout << stack.pop();
                }
                stack.pop();
                print_space(stack.empty());
            } else {
                int operator_prio = priorities_map.at(_operator);
                int top_prio = priorities_map.at(stack.top());
                while (top_prio >= operator_prio) {
                    std::cout << stack.pop();
                    print_space(stack.empty());
                    top_prio = priorities_map.at(stack.top());
                }
                stack.push(_operator);
            }
        }
    }

    while(!stack.empty()) {
        char current = stack.pop();
        std::cout << current;
        print_space(stack.empty());
    };
}

static bool is_digit(std::string input) {
    try {
        std::stoi(input);
        return true;
    } catch (...) {
        return false;
    }
}

inline void print_space(bool is_empty) {
    if (!is_empty)
        std::cout << DELIMITER;
}
