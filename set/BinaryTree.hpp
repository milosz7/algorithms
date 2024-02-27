#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <math.h>
#include <functional>
#include <iostream>

template <class T>
class BinaryTree {
    public:
    struct Node {
        T value;
        Node *left;
        Node *right;
        Node *parent;
        Node(T _value) : value{_value}, left{nullptr}, right{nullptr}, parent{nullptr} {}
    };

    ~BinaryTree();
    Node* getRoot();
    void insert(T x);
    Node* search(T x);
    int size();
    void inorder();
    void remove(Node* to_remove);
    void shift(Node* node, Node* other);
    Node* node_successor(Node* node);
    Node* minimum(Node* node);
    void clear();

    private:
        int _size = 0;
        Node *root;
};

template <class T>
BinaryTree<T>::~BinaryTree() { clear(); }

template <class T>
typename BinaryTree<T>::Node* BinaryTree<T>::getRoot() { return root; }

template <class T>
void BinaryTree<T>::insert(T x) {
    Node *to_insert = new Node(x);
    Node *parent = nullptr;
    Node *current = root;
    
    while (current != nullptr) {
        parent = current;
        if (to_insert->value < current->value)
            current = current->left;
        else
            current = current->right;
    }
    to_insert->parent = parent;
    _size++;
    if (parent == nullptr)
        root = to_insert;
    else if (to_insert->value < parent->value)
        parent->left = to_insert;
    else
        parent->right = to_insert;
    
}

template <class T>
typename BinaryTree<T>::Node* BinaryTree<T>::search(T x) {
    Node *current = root;
    while (current != nullptr && current->value != x) {
        if (x < current->value)
            current = current->left;
        else
            current = current->right;
    }
    return current;
}

template <class T>
int BinaryTree<T>::size() { return _size; }

template <class T>
void BinaryTree<T>::inorder() {
    std::function<void(Node*)> traverse = [&](Node* current) {
        if (current != nullptr) {
            traverse(current->left);
            std::cout << current->value << " ";
            traverse(current->right);
        }  
    };
    traverse(root);
}

template <class T>
void BinaryTree<T>::remove(Node *to_remove) {
    if (to_remove->left == nullptr)
        shift(to_remove, to_remove->right);
    else if (to_remove->right == nullptr)
        shift(to_remove, to_remove->left);
    else {
        Node *successor = node_successor(to_remove);
        if (successor->parent != to_remove) {
            shift(successor, successor->right);
            successor->right = to_remove->right;
            successor->right->parent = successor;
        }
        shift(to_remove, successor);
        successor->left = to_remove->left;
        successor->left->parent = successor;
    }
    _size--;
}

template <class T>
void BinaryTree<T>::shift(Node* node, Node* other) {
    if (node->parent == nullptr)
        root = other;
    else if (node == node->parent->left)
        node->parent->left = other;
    else
        node->parent->right = other;
    if (other != nullptr)
        other->parent = node->parent;
}

template <class T>
typename BinaryTree<T>::Node* BinaryTree<T>::node_successor(Node* node) {
    Node* current = node;
    if (current->right != nullptr)
        return minimum(current->right);
    Node* successor = current->parent;
    while (successor != nullptr && current == successor->right) {
        current = successor;
        successor = successor->parent;
    }
    return successor;
}

template <class T>
typename BinaryTree<T>::Node* BinaryTree<T>::minimum(Node *node) {
    Node *current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

template <class T>
void BinaryTree<T>::clear() {
    std::function<void(Node*)> clean_up = [&](Node* current) {
        if (current != nullptr) {
            clean_up(current->left);
            clean_up(current->right);
            delete current;
        }  
    };
    clean_up(root);
    root = nullptr;
    _size = 0;
}

#endif