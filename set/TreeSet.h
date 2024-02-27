#pragma once
#include <iostream>
#include "BinaryTree.hpp"
#include <functional>

class TreeSet {
    using Node = BinaryTree<int>::Node; 
public:
    BinaryTree<int> tree;
    int getSize();  
    void printSet(); 
    void insert(int x);
    void withdraw(int x);
    bool isInSet(int x); 
    void clearSet();
    TreeSet operator+(TreeSet& other);  
    TreeSet operator*(TreeSet& other);   
    TreeSet operator-(TreeSet& other);
    bool operator==(TreeSet& other);  
    bool operator<=(TreeSet& other);
};
