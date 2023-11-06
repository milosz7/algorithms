#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H
#include <stdexcept>
#include <utility>
#include <iostream>

template <class T>
class Node {
public:
    Node<T> *next = nullptr;
    Node(T value) : _value{value} {}
    T _value;
};

template <class T>
class LinkedQueue {

public:
    LinkedQueue(int capacity = (int)1e6) : _capacity{capacity} {}
    ~LinkedQueue();
    void push(T x);
    T pop();
    int size();
    bool empty();

private:
    int _capacity;
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
    int n_elements = 0;
};

template <class T>
LinkedQueue<T>::~LinkedQueue() {
    while( head != nullptr ) {
        Node<T> *next = head->next;
        delete head;
        head = next;
    }
}

template <class T>
void LinkedQueue<T>::push(T x) {
    if (n_elements == _capacity)
        throw std::out_of_range("Stack is full!");
    
    Node<T> *new_node = new Node<T>(x);
    if (head == nullptr) {
        head = tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
    n_elements++;
}

template <class T>
int LinkedQueue<T>::size() {
    return n_elements;
}

template <class T>
bool LinkedQueue<T>::empty() { return n_elements == 0; }

template <class T>
T LinkedQueue<T>::pop() {
    if (empty())
        throw std::out_of_range("Queue is empty!");
    Node<T> *enqueued = head;
    head = head->next;
    T output = enqueued->_value;
    delete enqueued;
    n_elements--;
    
    if (empty())
        head = tail = nullptr;

    return output;
}

#endif