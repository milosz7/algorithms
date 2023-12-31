#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdexcept>

template <class T>
class LinkedList {
    public:
    struct Node {
        Node *prev;
        Node *next;
        T value;
        Node(Node *_prev, Node *_next, T _value) : prev{_prev}, next{_next}, value{_value} {} 
        Node() : prev{nullptr}, next{nullptr} {}
    };
    
    Node *indirect; 
    int _size = 0;

    LinkedList();
    ~LinkedList();
    void push_front(T x);
    T pop_front();
    void push_back(T x);
    T pop_back();
    int size();
    bool empty();
    void clear();
    int find(T x);
    T erase(int i);
    void insert(int i, T x);
    int remove(T x);
    bool replace(T oldv, T newv);    
    void bind(Node *current);   
};

template <class T>
bool LinkedList<T>::empty() { return _size == 0; }

template <class T>
int LinkedList<T>::size() { return _size; }

template <class T>
LinkedList<T>::LinkedList() {
    indirect = new Node();
    indirect->next = indirect;
    indirect->prev = indirect;
}

template <class T>
LinkedList<T>::~LinkedList() {
    clear();
    delete indirect;
}

template <class T>
void LinkedList<T>::push_front(T x) {
    Node *head = indirect->next;
    Node *to_insert = new Node(indirect, head, x);
    head->prev = to_insert;
    indirect->next = to_insert;
    _size++;
}

template <class T>
T LinkedList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("List is empty!");
    Node *head = indirect->next;
    T output = head->value;
    indirect->next = head->next;
    head->next->prev = indirect;
    delete head;
    _size--;
    return output;
}

template <class T>
void LinkedList<T>::push_back(T x) {
    Node *tail = indirect->prev;
    Node *to_insert = new Node(tail, indirect, x);
    tail->next = to_insert;
    indirect->prev = to_insert;
    _size++;
}

template <class T>
T LinkedList<T>::pop_back() {
    if (empty())
        throw std::out_of_range("List is empty!");
    Node *tail = indirect->prev;
    T output = tail->value;
    indirect->prev = tail->prev;
    tail->prev->next = indirect;
    delete tail;
    _size--;
    return output;
}

template <class T>
void LinkedList<T>::clear() {
    Node *to_remove = indirect->next;
    while (to_remove != indirect) {
        Node *temp = to_remove->next;
        delete to_remove;
        to_remove = temp;
    }
    _size = 0;
    indirect->next = indirect;
    indirect->prev = indirect;
}

template <class T>
int LinkedList<T>::find(T x) {
    Node *walk = indirect->next;
    int index = 0;
    while (walk != indirect) {
        if (walk->value == x)
            return index;
        index++;
        walk = walk->next;
    }
    return -1;
}

template <class T>
T LinkedList<T>::erase(int i) {
    if (empty())
        throw std::out_of_range("List is empty!");
    if (i > _size - 1)
        throw std::out_of_range("The index is out of bounds!");
    Node *walk = indirect->next;
    for (int it = 0; it < i; it++) {
        walk = walk->next;
    }
    T output = walk->value;
    bind(walk);
    delete walk;
    _size--;
    return output;
}

template <class T>
void LinkedList<T>::insert(int i, T x) {
    if (i > _size - 1)
        throw std::out_of_range("The index is out of bounds!");
    Node *walk = indirect->next;
    for (int it = 0; it < i; it++) {
        walk = walk->next;
    }
    Node *to_insert = new Node(walk->prev, walk, x);
    walk->prev->next = to_insert;
    walk->prev = to_insert;
    _size++;
}

template <class T>
int LinkedList<T>::remove(T x) {
    int occurencies = 0;
    Node *walk = indirect->next;
    while(walk != indirect) {
        Node *temp = walk;
        walk = walk->next;
        if (temp->value == x) {
            bind(temp);
            occurencies++;
            _size--;
            delete temp;
        }
    }
    return occurencies;

}

template <class T>
bool LinkedList<T>::replace(T oldv, T newv) {
    Node *walk = indirect->next;
    while(walk != indirect) {
        if (walk->value == oldv) {
            walk->value = newv;
            return true;
        }
        walk = walk->next;
    }
    return false;
}

template <class T>
void LinkedList<T>::bind(Node *current) {
    current->prev->next = current->next;
    current->next->prev = current->prev;
}


#endif