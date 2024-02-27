#pragma once
#include <iostream>
#include <vector>
#include <list>

class setList {
    std::list<int> vec;
public:
    int getSize();  
    void printSet(); 
    void insert(int x);
    void withdraw(int x);
    bool isInSet(int x); 
    void clearSet();
    setList operator+(setList& other);  
    setList operator*(setList& other);   
    setList operator-(setList& other);
    bool operator==(setList& other);  
    bool operator<=(setList& other);
};
