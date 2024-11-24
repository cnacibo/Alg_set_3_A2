#ifndef MERGEINSERTIONSORT_H
#define MERGEINSERTIONSORT_H

#include <vector>

#include "MergeSort.h"

class MergeInsertionSort {
private:
    static void insertionSort(std::vector<int>& A, int l, int r) {
        for (int i = l + 1; i <= r; ++i) {
            int key = A[i];
            int j = i - 1;
            while (j >= l && A[j] > key) {
                A[j + 1] = A[j];
                --j;
            }
            A[j + 1] = key;
        }
    }

public:
    static void mergeInsertionSort(std::vector<int>& A, int l, int r, int threshold) {
        if (r - l <= threshold) {
            insertionSort(A, l, r);
            return;
        }
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeInsertionSort(A, l, m, threshold);
            mergeInsertionSort(A, m + 1, r, threshold);
            MergeSort::merge(A, l, m, r);
        }
    }
};



#endif //MERGEINSERTIONSORT_H
