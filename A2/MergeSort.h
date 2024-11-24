#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>


class MergeSort {
public:
    static void merge(std::vector<int>& arr, int left, int mid, int right) {
        int n_left = mid - left + 1;
        int n_right = right - mid;

        std::vector<int> left_array(n_left);
        std::vector<int> right_array(n_right);

        for (int i = 0; i < n_left; ++i) {
            left_array[i] = arr[left + i];
        }

        for (int i = 0; i < n_right; ++i) {
            right_array[i] = arr[mid + 1 + i];
        }

        int i = 0, j = 0, k = left;
        while (i < n_left && j < n_right) {
            if (left_array[i] <= right_array[j]) {
                arr[k] = left_array[i];
                ++i;
            } else {
                arr[k] = right_array[j];
                ++j;
            }
            ++k;
        }

        while (i < n_left) {
            arr[k] = left_array[i];
            ++i;
            ++k;
        }

        while (j < n_right) {
            arr[k] = right_array[j];
            ++j;
            ++k;
        }
    }

    static void mergeSort(std::vector<int>& array, int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSort(array, l, m);
            mergeSort(array, m + 1, r);
            merge(array, l, m, r);
        }
    }
};



#endif //MERGESORT_H
