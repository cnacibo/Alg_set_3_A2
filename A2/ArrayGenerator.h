#ifndef ARRAYGENERATOR_H
#define ARRAYGENERATOR_H

#include <vector>
#include <random>
#include <algorithm>

class ArrayGenerator {

public:

    static std::vector<int> RandomArray(int n, int start, int end) {
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(start, end);

        std::vector<int> res(n);
        for (int i = 0; i < n; ++i) {
            res[i] = dist(rng);
        }
        return res;
    }

    static std::vector<int> ReverseSortedArray(int n, int start, int end) {
        std::vector<int> res  = RandomArray(n, start, end);
        std::ranges::sort(res, std::greater<int>());
        return res;
    }

    static std::vector<int> AlmostSortedArray(int n, int start, int end, int swaps) {
        std::vector<int> res  = RandomArray(n, start, end);
        std::sort(res.begin(), res.end());

        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(0, n - 1);

        for (int i = 0; i < swaps; ++i) {
            int index_1 = dist(rng);
            int index_2 = dist(rng);
            std::swap(res[index_1], res[index_2]);
        }

        return res;
    }


};

#endif //ARRAYGENERATOR_H
