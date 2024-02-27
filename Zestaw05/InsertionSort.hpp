#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H
#include <vector>

template <typename T>
void sort(std::vector<T> &v) {
    int n = v.size();
    for (int i = 1; i < n; i++) {
        T value = v.at(i);
        int j = i - 1;
        while (j >= 0 && v.at(j) > value) {
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = value;
    }
}

#endif