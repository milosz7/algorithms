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
    void insert(T x);
    Node* search(T x);
    Node* search_recursive(T x, Node* current);
    int size();
    T maximum();
    T minimum();
    int depth();
    void inorder();
    void preorder();
    void postorder();

    private:
        int _size = 0;
        Node *root;
};

template <class T>
BinaryTree<T>::~BinaryTree() {
    std::function<void(Node*)> clean_up = [&](Node* current) {
        if (current != nullptr) {
            clean_up(current->left);
            clean_up(current->right);
            delete current;
        }  
    };
    clean_up(root);
}

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
typename BinaryTree<T>::Node* BinaryTree<T>::search_recursive(T x, Node* current) {
    if (current == nullptr || current->value == x)
        return current;
    if (x < current->value)
        return search_recursive(x, current->left);
    else
        return search_recursive(x, current->right);
}

template <class T>
int BinaryTree<T>::size() { return _size; }

template <class T>
T BinaryTree<T>::maximum() {
    Node *current = root;
    while (current->right != nullptr)
        current = current->right;
    return current->value;
}

template <class T>
T BinaryTree<T>::minimum() {
    Node *current = root;
    while (current->left != nullptr)
        current = current->left;
    return current->value;
}

template <class T>
int BinaryTree<T>::depth() {
    std::function<int(Node*)> find_depth = [&](Node* current) {
        if (current == nullptr)
            return 0;
        int left_height = find_depth(current->left);
        int right_height = find_depth(current->right);
        return (int)fmax(left_height, right_height) + 1;
    };
    return find_depth(root);
}

template <class T>
void BinaryTree<T>::inorder() {
    std::function<void(Node*)> traverse = [&](Node* current) {
        if (current != nullptr) {
            traverse(current->left);
            std::cout << current->value << std::endl;
            traverse(current->right);
        }  
    };
    traverse(root);
}

template <class T>
void BinaryTree<T>::preorder() {
    std::function<void(Node*)> traverse = [&](Node* current) {
        if (current != nullptr) {
            std::cout << current->value << std::endl;
            traverse(current->left);
            traverse(current->right);
        }  
    };
    traverse(root);
}

template <class T>
void BinaryTree<T>::postorder() {
    std::function<void(Node*)> traverse = [&](Node* current) {
        if (current != nullptr) {
            traverse(current->left);
            traverse(current->right);
            std::cout << current->value << std::endl;
        }  
    };
    traverse(root);
}

#endif