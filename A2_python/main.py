import matplotlib.pyplot as plt
import pandas as pd


def plot_results(file, title, thresholds, output_file):
    data = pd.read_csv(file)

    sizes = data["Size"]

    plt.figure(figsize=(10, 6))
    plt.plot(sizes, data["Standard"], label="Merge Sort", marker='o')

    for t in thresholds:
        plt.plot(sizes, data[f"Hybrid (Threshold={t})"], label=f"Hybrid (Threshold={t})", marker='x')

    plt.title(title)
    plt.xlabel("Array Size")
    plt.ylabel("Execution Time (ms)")
    plt.legend()
    plt.grid()
    plt.savefig(output_file)
    plt.show()

thresholds = [5, 10, 20, 30, 50]
plot_results("../A2/cmake-build-debug/random_times.csv", "Random Array Sorting Time", thresholds, "random_graph.png")
plot_results("../A2/cmake-build-debug/reverse_times.csv", "Reverse Sorted Array Sorting Time", thresholds, "reverse_graph.png")
plot_results("../A2/cmake-build-debug/nearly_sorted_times.csv", "Almost Sorted Array Sorting Time", thresholds, "almost_sorted_graph.png")
