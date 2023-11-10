#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H
#include <stdexcept>
#include <iostream>

template <class T>
class ArrayList {
    public:
    ArrayList(int capacity = (int)1e6) : _capacity{capacity} {}
    ~ArrayList() { delete[] list; }
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
    void move(int idx);

    private:
    int _capacity;
    int _size = 0;
    T *list = new T[_capacity];
};

template <class T>
void ArrayList<T>::push_front(T x) {
    if (_capacity == _size)
        throw std::out_of_range("List is full!");
    for (int i = _size; i > 0; i--)
        list[i] = list[i - 1];
    list[0] = x;
    _size++;
}

template <class T>
T ArrayList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("List is empty!");
    T to_pop = list[0];
    for (int i = 0; i < _size; i++)
        list[i] = list[i + 1];
    _size--;
    return to_pop;
}

template <class T>
void ArrayList<T>::push_back(T x) {
    if (_capacity == _size)
        throw std::out_of_range("List is full!");
    list[_size] = x;
    _size++;
}

template <class T>
T ArrayList<T>::pop_back() {
    if (empty())
        throw std::out_of_range("List is empty!");
    T to_pop = list[_size - 1];
    _size--;
    return to_pop;
}

template <class T>
int ArrayList<T>::size() { return _size; }

template <class T>
bool ArrayList<T>::empty() { return _size == 0; }

template <class T>
void ArrayList<T>::clear() {
    delete[] list;
    list = new T[_capacity];
    _size = 0;
}

template <class T>
int ArrayList<T>::find(T x) {
    for (int i = 0; i < _size; i++) {
        if (list[i] == x)
            return i;
    }
    return -1;
}

template <class T>
T ArrayList<T>::erase(int idx) {
    if (empty())
        throw std::out_of_range("List is empty!");
    if (idx > _size - 1)
        throw std::out_of_range("The index is out of bounds!");
    T to_erase = list[idx];
    for (int i = idx; i < _size; i++) {
        list[i] = list[i + 1];
    }
    _size--;
    return to_erase;
}

template <class T>
void ArrayList<T>::insert(int idx, T x) {
    if (_capacity == _size)
        throw std::out_of_range("List is full!");
    if (idx > _size - 1)
        throw std::out_of_range("The index is out of bounds!");
    for (int i = _size; i > idx; i--)
        list[i] = list[i - 1];
    list[idx] = x;
    _size++;
}

template <class T>
int ArrayList<T>::remove(T x) {
    int occurencies = 0;
    for (int i = _size - 1; i >= 0; i--) {
        if (list[i] == x) {
            occurencies++;
            move(i);
            _size--;
        }
    }
    return occurencies;
}

template <class T>
void ArrayList<T>::move(int idx) {
    for (int i = idx; i < _size; i++) {
        list[i] = list[i + 1];
    }
}

#endif