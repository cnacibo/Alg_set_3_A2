#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include "ArrayGenerator.h"
#include "SortTester.h"

void saveResultsToFile(const std::string& filename, const std::string& label,
                       const std::vector<std::vector<long long>>& times,
                       const std::vector<int>& sizes, const std::vector<int>& thresholds) {
    std::ofstream outFile(filename);

    if (!outFile) {
        std::cerr << "Error: Unable to open file for writing: " << filename << "\n";
        return;
    }

    outFile << "Size,Standard";
    for (int t : thresholds) {
        outFile << ",Hybrid (Threshold=" << t << ")";
    }
    outFile << "\n";

    for (size_t i = 0; i < sizes.size(); ++i) {
        outFile << sizes[i];
        for (size_t t = 0; t < times.size(); ++t) {
            outFile << "," << times[t][i];
        }
        outFile << "\n";
    }

    outFile.close();
    std::cout << "Results saved to file: " << filename << "\n";
}

void printResults(const std::string& label, const std::vector<std::vector<long long>>& times, const std::vector<int>& sizes, const std::vector<int>& thresholds) {
    const int colWidth = 15;

    std::cout << label << "\n";
    std::cout << std::setw(10) << "Size" << std::setw(colWidth) << "Standard";
    for (int t : thresholds) {
        std::cout << std::setw(colWidth) << ("Hybrid (" + std::to_string(t) + ")");
    }
    std::cout << "\n";

    for (size_t i = 0; i < sizes.size(); ++i) {
        std::cout << std::setw(10) << sizes[i];
        for (size_t t = 0; t < times.size(); ++t) {
            std::cout << std::setw(colWidth) << times[t][i];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main() {
    std::vector<int> thresholds = {5, 10, 20, 30, 50};

    std::vector<int> sizes;
    for (int size = 500; size <= 10000; size += 100) {
        sizes.push_back(size);
    }

    std::vector<std::vector<long long>> randomTimes(thresholds.size() + 1, std::vector<long long>(sizes.size()));
    std::vector<std::vector<long long>> reverseTimes(thresholds.size() + 1, std::vector<long long>(sizes.size()));
    std::vector<std::vector<long long>> nearlySortedTimes(thresholds.size() + 1, std::vector<long long>(sizes.size()));

    for (size_t i = 0; i < sizes.size(); ++i) {
        int size = sizes[i];
        std::vector<int> randomArray = ArrayGenerator::RandomArray(size, 0, 6000);
        std::vector<int> reverseArray = ArrayGenerator::ReverseSortedArray(size, 0, 6000);
        std::vector<int> nearlySortedArray = ArrayGenerator::AlmostSortedArray(size, 0, 6000, size / 100);

        randomTimes[0][i] = SortTester::timeMergeSort(randomArray, 0, size - 1);
        reverseTimes[0][i] = SortTester::timeMergeSort(reverseArray, 0, size - 1);
        nearlySortedTimes[0][i] = SortTester::timeMergeSort(nearlySortedArray, 0, size - 1);

        for (size_t t = 0; t < thresholds.size(); ++t) {
            int threshold = thresholds[t];

            std::vector<int> randomCopy = randomArray;
            std::vector<int> reverseCopy = reverseArray;
            std::vector<int> nearlyCopy = nearlySortedArray;

            randomTimes[t + 1][i] = SortTester::timeHybridMergeSort(randomCopy, 0, size - 1, threshold);
            reverseTimes[t + 1][i] = SortTester::timeHybridMergeSort(reverseCopy, 0, size - 1, threshold);
            nearlySortedTimes[t + 1][i] = SortTester::timeHybridMergeSort(nearlyCopy, 0, size - 1, threshold);
        }
    }

    printResults("\nRandom Array Times", randomTimes, sizes, thresholds);
    saveResultsToFile("random_times.csv", "Random Array Times", randomTimes, sizes, thresholds);

    printResults("\nReverse Sorted Array Times", reverseTimes, sizes, thresholds);
    saveResultsToFile("reverse_times.csv", "Reverse Sorted Array Times", reverseTimes, sizes, thresholds);

    printResults("\nNearly Sorted Array Times", nearlySortedTimes, sizes, thresholds);
    saveResultsToFile("nearly_sorted_times.csv", "Nearly Sorted Array Times", nearlySortedTimes, sizes, thresholds);

    return 0;
}
