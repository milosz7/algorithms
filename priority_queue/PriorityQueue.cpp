#include "PriorityQueue.h"

void PriorityQueue::insert(int x) {
    heap.push_back(x);
    int idx = heap.size() - 1;
    heapifyUp(idx);
}

int PriorityQueue::removeRootElem() {
    if (heap.empty())
        throw std::out_of_range("Heap is empty!");
        
    int to_remove = heap[0];
    int last_elem = heap[heap.size() - 1];
    heap[0] = last_elem;
    heap.pop_back();
    heapifyDown(0);
    return to_remove;
}

int PriorityQueue::getRootElem() {
    if (heap.empty())
        throw std::out_of_range("Heap is empty!");  
    return heap[0];
}

void PriorityQueue::heapifyUp(int idx) {
    int parent_idx = (idx - 1) / 2;
    int parent = heap[parent_idx];
    int current = heap[idx];
    if (parent_idx >= 0 && current > parent) {
        heap[parent_idx] = current;
        heap[idx] = parent;
        heapifyUp(parent_idx);
    }
}

void PriorityQueue::heapifyDown(int idx) {
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    int largest = idx;
    int size = heap.size();

    if (left < size && heap[left] > heap[largest])
        largest = left;
    if (right < size && heap[right] > heap[largest])
        largest = right;
    if (largest != idx) {
        int temp = heap[largest];
        heap[largest] = heap[idx];
        heap[idx] = temp;
        heapifyDown(largest);
    }
}

void PriorityQueue::print() {
    std::cout << "[ ";
    for (int elem : heap) std::cout << elem << " ";
    std::cout << "]";
}