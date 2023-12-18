#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdexcept>
#include <utility>

template <class K, class V>
class LinkedList {
    using Pair = std::pair<K, V>;
    public:
    struct Node {
        Node *next;
        Pair *value;

        Node(Node *_next, Pair& _value) : next{_next}, value{_value} {} 
        Node(Node *_next, K _key) : next{_next}, value{new Pair} { value->first = _key; }
        Node() : next{nullptr}, value{nullptr} {}

        ~Node() { if (value != nullptr) delete value; }
    };
    
    Node *indirect; 
    int _size = 0;

    LinkedList();
    ~LinkedList();
    void push_front(Pair &x);
    int size();
    bool empty();
    void clear();
    int find(K x);
    bool erase(K k);
    V& allocate(K key);
    V& address_at(int i);
    Pair& pair_at(int i);
};

template <class K, class V>
bool LinkedList<K, V>::empty() { return _size == 0; }

template <class K, class V>
int LinkedList<K, V>::size() { return _size; }

template <class K, class V>
LinkedList<K, V>::LinkedList() {
    indirect = new Node();
    indirect->next = indirect;
}

template <class K, class V>
LinkedList<K, V>::~LinkedList() {
    clear();
    delete indirect;
}

template <class K, class V>
void LinkedList<K, V>::push_front(Pair &x) {
    Node *head = indirect->next;
    Node *to_insert = new Node(head, x);
    indirect->next = to_insert;
    _size++;
}

template <class K, class V>
void LinkedList<K, V>::clear() {
    Node *to_remove = indirect->next;
    while (to_remove != indirect) {
        Node *temp = to_remove->next;
        delete to_remove;
        to_remove = temp;
    }
    _size = 0;
    indirect->next = indirect;
}

template <class K, class V>
int LinkedList<K, V>::find(K x) {
    Node *walk = indirect->next;
    int index = 0;
    while (walk != indirect) {
        if (walk->value->first == x)
            return index;
        index++;
        walk = walk->next;
    }
    return -1;
}



template <class K, class V>
bool LinkedList<K, V>::erase(K k) {
    Node *walk = indirect->next;
    while (walk->next != nullptr) {
        if (walk->next->value->first == k) {
            Node *temp = walk->next;
            walk->next = walk->next->next;
            delete temp;
            _size--;
            return true;
        }
        walk = walk->next;
    }
    return false;
}

template <class K, class V>
V& LinkedList<K, V>::allocate(K key) {
    Node *head = indirect->next;
    Node *to_insert = new Node(head, key);
    indirect->next = to_insert;
    _size++;
    return to_insert->value->second;
}

template <class K, class V>
V& LinkedList<K, V>::address_at(int i) {
    if (empty())
        throw std::out_of_range("List is empty!");
    if (i > _size - 1)
        throw std::out_of_range("The index is out of bounds!");
    Node *walk = indirect->next;
    for (int it = 0; it < i; it++) {
        walk = walk->next;
    }
    return walk->value->second;
}

template <class K, class V>
typename LinkedList<K, V>::Pair& LinkedList<K, V>::pair_at(int i) {
    if (empty())
        throw std::out_of_range("List is empty!");
    if (i > _size - 1)
        throw std::out_of_range("The index is out of bounds!");
    Node *walk = indirect->next;
    for (int it = 0; it < i; it++) {
        walk = walk->next;
    }
    Pair& output = walk->value;
    return output;
}

#endif