#ifndef DICT_H
#define DICT_H
#include <utility>
#include <string>
#include <iostream>
#include "LinkedList.hpp"
#include "hash.hpp"

constexpr int KEY_NOT_FOUND = -1;

template <class K, class V>
class Dict {
    using Pair = std::pair<K, V>;
    public:
        Dict(int n_buckets_);
        ~Dict();
        void clear();
        bool insert(const Pair& pair);
        bool find(const K& key);
        V& operator[](const K& key);
        bool erase(const K& key);
        int size();
        bool empty();
        void buckets();

    private:
        int size_ = 0;
        int n_buckets;
        LinkedList<K, V>** buckets_;
};

template <class K, class V>
Dict<K, V>::Dict(int n_buckets_) {
    n_buckets = n_buckets_;
    buckets_ = new LinkedList<K,V>*[n_buckets];
    for (int i = 0; i < n_buckets; i++) {
        buckets_[i] = new LinkedList<K, V>();
    }
};

template <class K, class V>
Dict<K, V>::~Dict() {
    for (int i = 0; i < n_buckets; i++)
        delete buckets_[i];
    delete buckets_;
}


template <class K, class V>
void Dict<K, V>::clear() {
    for (int i = 0; i < n_buckets; i++)
        buckets_[i]->clear();
    size_ = 0;
}

template <class K, class V>
bool Dict<K, V>::insert(const Pair& pair) {
    K key = pair.first;
    V value = pair.second;
    int idx = hash(code(key), n_buckets);
    if (buckets_[idx]->find(key) == KEY_NOT_FOUND) {
        size_++;
        buckets_[idx]->push_front(pair);
        return true;
    }
    return false;
}

template <class K, class V>
bool Dict<K, V>::find(const K& key) {
    int idx = hash(code(key), n_buckets);
    return (buckets_[idx]->find(key) != KEY_NOT_FOUND);
}

template <class K, class V>
V& Dict<K, V>::operator[](const K& key) {
    int idx = hash(code(key), n_buckets);
    int key_idx = buckets_[idx]->find(key);
    
    if (key_idx == KEY_NOT_FOUND) {
        size_++;
        return buckets_[idx]->allocate(key);
    }
    return buckets_[idx]->address_at(key_idx);
}

template <class K, class V>
bool Dict<K, V>::erase(const K& key) {
    int idx = hash(code(key), n_buckets);
    return buckets_[idx]->erase(key);
}

template <class K, class V>
int Dict<K, V>::size() { return size_; }

template <class K, class V>
bool Dict<K, V>::empty() { return size_ == 0; }

template <class K, class V>
void Dict<K, V>::buckets() {
    for (int i = 0; i < n_buckets; i++) {
        int n_elements = buckets_[i]->size();
        if (n_elements)
            std::cout << "Bucket " << i << "(elements: " << n_elements << "):" << std::endl;
        for (int j = 0; j < n_elements; j++) {
            Pair p = buckets_[i]->pair_at(j);
            std::cout << p.first << "=" << p.second << std::endl;
        }
        std::cout << "-----" << std::endl;
    }
}

#endif
