#include <stdexcept>
#include "ArrayStack.hpp"

bool ArrayStack::empty() { return current == 0; }

void ArrayStack::push(int x) {
    if (current == _capacity)
        throw std::out_of_range("Stack size exceeded.");
    
    stack[current++] = x;
}

int ArrayStack::pop() {
    if (empty())
        throw std::out_of_range("Stack is empty.");

    return stack[--current];
}

int ArrayStack::size() { return current; }
