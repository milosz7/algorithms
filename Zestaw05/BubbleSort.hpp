#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H
#include <vector>

template <typename T>
void sort(std::vector<T> &v) {
    bool swapped;
    int n = v.size();
    for (int i = 0; i < n; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (v.at(j) > v.at(j+1)) {
                swapped = true;
                std::swap(v.at(j), v.at(j+1));
            }
        }
        if (!swapped)
            break;
    }
}

#endif