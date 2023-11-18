#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H
#include <vector>

template <typename T>
void sort(std::vector<T> &v) {
    int n = v.size();
    int min_idx;
    for (int i = 0; i < n-1; i++) {
        min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (v.at(j) < v.at(min_idx))
                min_idx = j;
        }
        std::swap(v.at(i), v.at(min_idx));
    }
}

#endif

