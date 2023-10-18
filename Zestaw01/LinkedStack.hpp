#ifndef LINKEDSTACK_HPP
#define LINKEDSTACK_HPP

class Node {
public:
    Node *next = nullptr;
    Node(int value) : _value{value} {}
    int _value;
};

class LinkedStack {
    int _capacity;

public:
    LinkedStack(int capacity = (int)1e6) : _capacity{capacity} {}
    ~LinkedStack();

    void push(int x);
    int pop();
    int size();
    bool empty();

private:
    int current = 0;
    Node* head = nullptr;
};

#endif