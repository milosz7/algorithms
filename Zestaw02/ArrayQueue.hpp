#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H
#include <stdexcept>
#include <utility>
#include <iostream>

template <class T>
class ArrayQueue {

public:
    ArrayQueue(int capacity = (int)1e6) : _capacity{capacity} {}
    ~ArrayQueue() { delete[] queue; }
    template<class U>
    void push(U&& x);
    T pop();
    int size();
    bool empty();

private:
    int _capacity;
    int head = 0;
    int tail = 0;
    T *queue = new T[_capacity];
};

template <class T>
template <class U>
void ArrayQueue<T>::push(U &&x) {
    if (size() == _capacity)
        throw std::out_of_range("Stack is full!");
    queue[(tail++) % _capacity] = std::forward<U>(x);
}

template <class T>
int ArrayQueue<T>::size() {
    return tail - head;
}

template <class T>
bool ArrayQueue<T>::empty() { return head == tail; }

template <class T>
T ArrayQueue<T>::pop() {
    if (empty())
        throw std::out_of_range("Queue is empty!");

    T output = queue[(head++) % _capacity];
    return output;
}

#endif