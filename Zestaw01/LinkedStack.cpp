#include "LinkedStack.hpp"
#include <stdexcept>
#include <iostream>

LinkedStack::~LinkedStack() {
    while( head != nullptr ) {
        Node* next = head->next;
        delete head;
        head = next;
    }
}

bool LinkedStack::empty() { return current == 0; }

int LinkedStack::size() { return current; }

void LinkedStack::push(int x) {
    if (current == _capacity)
        throw std::out_of_range("Stack size exceeded.");
    
    Node *new_node = new Node(x);

    if (!head) {
        head = new_node;
    } else {
        new_node->next = head;
        head = new_node;
    }
    current++;
}

int LinkedStack::pop() {
    if (empty())
        throw std::out_of_range("Stack is empty.");
    
    current--;
    Node *to_pop = head;
    int value = to_pop->_value;

    if (current == 0) {
        head = nullptr;
    } else {
        head = to_pop->next;
    }
    delete to_pop;
    
    return value;
}