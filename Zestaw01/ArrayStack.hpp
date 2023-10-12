#ifndef ARRAYSTACK_HPP
#define ARRAYSTACK_HPP

class ArrayStack {
    int _capacity;
public:
    ArrayStack(int capacity = (int)1e6) : _capacity{capacity} {} // zapytac czemu erroruje
    ~ArrayStack() { delete[] stack; }

    void push(int x);
    int pop();
    int size();
    bool empty();

private:
    int current = 0;
    int *stack = new int[_capacity];
};

#endif