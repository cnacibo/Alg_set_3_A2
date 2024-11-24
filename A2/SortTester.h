#ifndef SORTTESTER_H
#define SORTTESTER_H

#include <vector>
#include <chrono>
#include "MergeInsertionSort.h"
#include "MergeSort.h"

class SortTester {
public:

    static long long  timeMergeSort(std::vector<int>& A, int l, int r) {
        auto start = std::chrono::high_resolution_clock::now();
        MergeSort::mergeSort(A, l, r);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        return msec;
    }

    static long long timeHybridMergeSort(std::vector<int>& array, int l, int r, int threshold) {
        auto start = std::chrono::high_resolution_clock::now();
        MergeInsertionSort::mergeInsertionSort(array, l, r, threshold);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    }
};




#endif //SORTTESTER_H
