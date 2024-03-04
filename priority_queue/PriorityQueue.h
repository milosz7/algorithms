#pragma once
#include <vector>
#include <stdexcept>
#include <iostream>

class PriorityQueue {
    public:
        void insert(int x);
        int removeRootElem();
        void print();
        int getRootElem();
    private:
        void heapifyUp(int idx);
        void heapifyDown(int idx);
        std::vector<int> heap;
};