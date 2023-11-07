#ifndef CURSOR_LIST_H
#define CURSOR_LIST_H
#include <stdexcept>
#include <iostream>
#include "stdlib.h"

template <class T>
class CursorList {
    public:
    struct Node {
        T value;
        int next;
    };
    
    CursorList(int capacity = (int)1e5);
    ~CursorList();
    void push_front(T x);
    T pop_front();
    void push_back(T x);
    T pop_back();
    int size();
    bool empty();
    void clear();
    int find(T x);
    T erase(int idx);
    void insert(int idx, T x);
    int remove(T x);
    int allocate();
    void deallocate(int idx);
    void printfree();
    void printlist();


    private:
    int _capacity;
    Node *nodes;
    int head = -1;
    int tail = -1;
    int spare = 0;
    int _size = 0;
};

template <class T>
CursorList<T>::CursorList(int capacity) : _capacity{capacity} {
    nodes = new Node[_capacity];
    for (int i = 0; i < _capacity - 1; i++) {
        nodes[i].next = i + 1;
    }
    nodes[capacity - 1].next = -1;
}

template <class T>
CursorList<T>::~CursorList() { delete[] nodes; }

template <class T>
void CursorList<T>::push_front(T x) {
    if (_size == _capacity)
        throw std::out_of_range("List is full!");
    int idx = allocate();
    nodes[idx].value = x;
    nodes[idx].next = head;
    head = idx;
    if (empty())
        tail = idx;
    _size++;
}

template <class T>
T CursorList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("List is empty!");
    T to_pop = nodes[head].value;
    int temp = head;
    head = nodes[head].next;
    deallocate(temp);
    _size--;
    if(empty())
        head = tail = -1;
    return to_pop;
}

template <class T>
void CursorList<T>::push_back(T x) {
    if (_size == _capacity)
        throw std::out_of_range("List is full!");
    int idx = allocate();
    nodes[idx].value = x;
    nodes[idx].next = -1;
    nodes[tail].next = idx;
    tail = idx;
    if (empty())
        head = tail;
    _size++;
}

template <class T>
T CursorList<T>::pop_back() {
    if (empty())
        throw std::out_of_range("List is empty!");
    T to_pop = nodes[tail].value;
    Node current_node = nodes[head];
    _size--;

    if (empty()) {
        deallocate(tail);
        head = tail = -1;
        return to_pop;
    }

    if (size() == 1) {
        deallocate(tail);
        tail = head;
        return to_pop;
    }
        
    while (nodes[current_node.next].next != tail) {
        current_node = nodes[current_node.next];
        if (current_node.next == -1) break;
    }
    deallocate(tail);
    tail = current_node.next;
    nodes[tail].next = -1;

    return to_pop;
}

template <class T>
int CursorList<T>::size() { return _size; }

template <class T>
bool CursorList<T>::empty() { return _size == 0; }

template <class T>
void CursorList<T>::clear() {
    for (int i = 0; i < _capacity - 1; i++)
        nodes[i].next = i + 1;
    nodes[_capacity - 1] = -1;
    head = tail = -1;
    _size = spare = 0;
}

template <class T>
int CursorList<T>::find(T x) {
    Node current_node = nodes[head];
    int current_idx = head;
    int idx = 0;
    while (current_idx != -1) {
        if (current_node.value == x)
            return idx;
        idx++;
        current_idx = current_node.next;
        current_node = nodes[current_idx];
    }
    return -1;
}

template <class T>
T CursorList<T>::erase(int idx) {
    if (empty())
        throw std::out_of_range("List is empty!");
    if (idx > _size - 1)
        throw std::out_of_range("The index is out of bounds!");    
    
    if (idx == 0)
        return pop_front();

    _size--;

    Node *current = &nodes[head];
    int current_idx = head;
    for (int i = 0; i < idx - 1; i++) {
        current_idx = current->next;
        current = &nodes[current_idx];
    }      

    int temp = current->next;
    T to_pop = nodes[current->next].value;
    current->next = nodes[current->next].next;
    deallocate(temp);
    return to_pop;
}

template <class T>
void CursorList<T>::insert(int idx, T x) {
    if (_capacity == _size)
        throw std::out_of_range("List is full!");
    if (idx > _size)
        throw std::out_of_range("The index is out of bounds!");

    if (idx == 0) {
        push_front(x);
        return;
    }

    Node *current = &nodes[head];
    for (int i = 0; i < idx - 1; i++) {
        current = &nodes[current->next];
    }
    int new_idx = allocate();
    nodes[new_idx].next = current->next;
    nodes[new_idx].value = x;
    current->next = new_idx;
    _size++;
}

template <class T>
int CursorList<T>::remove(T x) {
    Node current_node = nodes[head];
    int current_idx = head;
    while (current_node.next != -1) {
        if (current_node.value == x) {
            int test = 0;
        }
        current_idx = current_node.next;
        current_node = current_node[current_idx];
    }
    return 0;
}

template <class T>
int CursorList<T>::allocate() {
    int temp = spare;
    spare = nodes[spare].next;
    return temp;
}

template <class T>
void CursorList<T>::deallocate(int idx) {
    nodes[idx].next = spare;
    spare = idx;
}

template <class T>
void CursorList<T>::printfree() {
    Node current_node = nodes[spare];
    std::cout << "spare" << spare;
    while (current_node.next != -1)
    {
        std::cout << current_node.next;
        current_node = nodes[current_node.next];
    }
    
}

template <class T>
void CursorList<T>::printlist() {
    Node current = nodes[head];
    int this_idx = head;
    for (int i = 0; i < _size; i++) {
        std::cout << "value: " << current.value << "next: " << current.next << std::endl;
        current = nodes[current.next];
    }
    Node current2 = nodes[head];
    // for (int i = 1; i < _size; i++) {
    //     std::cout << "idx: " << this_idx  << std::endl;
    //     this_idx = current2.next;
    //     current2 = nodes[current2.next];
    // }
}


#endif