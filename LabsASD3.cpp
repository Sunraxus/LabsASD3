#include<iostream>
#include<vector>
#include <cstdlib> 
#include <stdexcept>
#include <ctime>

using namespace std;

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};

template <typename T>
void custom_swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

class MyClass {
private:
    int value;
public:
    MyClass() :value(0) {};
    MyClass(const int value) :value(value) {};
    int get_value() const {
        return this->value;
    }
    bool operator>(const MyClass& rhs) {
        return this->value > rhs.value;
    }
    bool operator<(const MyClass& rhs) {
        return !(*this > rhs);
    }
};

template<typename T>
stats& BubbleSort(vector<T>& vec) {
	stats statistics;
	for (int i(0); i < (vec.size() - 1); ++i) {
		for (int j(0); j < (vec.size() - i - 1); ++j) {
			statistics.comparison_count += 1;
			if (vec[j] > vec[j + 1]) {
                custom_swap(vec[j], vec[j + 1]);
				statistics.copy_count += 3;
			}
		}
	}
	return statistics;
}

template <typename T>
stats& QuickSortSeparation(vector<T>& vec, int start, int end) {
    stats statistics;

    int i = start;
    int j = end;
    T middle = vec[(start + end) / 2];

    do {
        while (vec[i] < middle) {
            i++;
            statistics.comparison_count++;
        }
        while (vec[j] > middle) {
            j--;
            statistics.comparison_count++;
        }

        if (i <= j) {
            custom_swap(vec[i], vec[j]);
            i++;
            j--;
            statistics.copy_count += 3;
        }
    } while (i <= j);

    if (j > start) {
        stats left_statistics = QuickSortSeparation(vec, start, j);
        statistics.comparison_count += left_statistics.comparison_count;
        statistics.copy_count += left_statistics.copy_count;
    }
    if (i < end) {
        stats right_statistics = QuickSortSeparation(vec, i, end);
        statistics.comparison_count += right_statistics.comparison_count;
        statistics.copy_count += right_statistics.copy_count;
    }

    return statistics;
}

template <typename T>
stats& QuickSort(vector<T>& vec) {
    return QuickSortSeparation(vec, 0, vec.size() - 1);
}

template <typename T>
void Heapify(vector<T>& vec, int size, int i, stats& statistics) {
    int max = i; 
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < size) {
        statistics.comparison_count ++;
        if (vec[left] > vec[max]) {
            max = left;
        }
    }

    if (right < size) {
        statistics.comparison_count ++;
        if (vec[right] > vec[max]) {
            max = right;
        }
    }

    if (max != i) {
        custom_swap(vec[i], vec[max]);
        statistics.copy_count += 3;
        Heapify(vec, size, max, statistics);
    }
}

template <typename T>
stats& HeapSort(vector<T>& vec) {
    stats statistics;
    int size = vec.size();
    for (int i = size / 2 - 1; i >= 0; i--) {
        Heapify(vec, size, i, statistics);
    }

    for (int i = size - 1; i >= 0; i--) {
        custom_swap(vec[0], vec[i]);
        statistics.copy_count += 3;
        Heapify(vec, i, 0, statistics);
    }
    return statistics;
}

template <typename T>
vector<T> RandomVec(size_t size) {
    vector<T> vec(size);
    srand(static_cast<unsigned int>(time(0)));
    for (size_t i = 0; i < size; ++i) {
        vec[i] = rand();
    }
    return vec;
}

template <typename T>
vector<T> SortedVec(size_t size) {
    vector<T> vec(size);
    for (size_t i = 0; i < size; ++i) {
        vec[i] = i;
    }
    return vec;
}

template <typename T>
vector<T> ReverseSortedVec(size_t size) {
    vector<T> vec(size);
    for (size_t i = 0; i < size; ++i) {
        vec[i] = size - i;
    }
    return vec; 
}

template <typename T>
void PrintVector(vector<T> vec) {
	for (int i = 0; i < vec.size(); ++i)
		cout << vec[i] << " ";
	cout << "\n\n";
}

int main() {
    const int num_vectors = 100;
    const vector<size_t> vector_lengths = { 1000, 2000, 3000, 4000, 5000,6000, 7000, 8000, 9000, 10000, 25000, 50000, 100000 };

    for (size_t length : vector_lengths) {
        stats bubble_random_stats_sum{ 0, 0 };
        stats quick_random_stats_sum{ 0, 0 };
        stats heap_random_stats_sum{ 0, 0 };

        stats bubble_sorted_stats_sum{ 0, 0 };
        stats quick_sorted_stats_sum{ 0, 0 };
        stats heap_sorted_stats_sum{ 0, 0 };

        stats bubble_reverse_sorted_stats_sum{ 0, 0 };
        stats quick_reverse_sorted_stats_sum{ 0, 0 };
        stats heap_reverse_sorted_stats_sum{ 0, 0 };

        for (int i = 0; i < num_vectors; ++i) {
            vector<int> random_vector = RandomVec<int>(length);

            vector<int> bubble_random_vector = random_vector;
            bubble_random_stats_sum.comparison_count += BubbleSort(bubble_random_vector).comparison_count;
            bubble_random_stats_sum.copy_count += BubbleSort(bubble_random_vector).copy_count;

            vector<int> quick_random_vector = random_vector;
            quick_random_stats_sum.comparison_count += QuickSort(quick_random_vector).comparison_count;
            quick_random_stats_sum.copy_count += QuickSort(quick_random_vector).copy_count;

            vector<int> heap_random_vector = random_vector;
            heap_random_stats_sum.comparison_count += HeapSort(heap_random_vector).comparison_count;
            heap_random_stats_sum.copy_count += HeapSort(heap_random_vector).copy_count;

            vector<int> sorted_vector = SortedVec<int>(length);

            vector<int> bubble_sorted_vector = sorted_vector;
            bubble_sorted_stats_sum.comparison_count += BubbleSort(bubble_sorted_vector).comparison_count;
            bubble_sorted_stats_sum.copy_count += BubbleSort(bubble_sorted_vector).copy_count;

            vector<int> quick_sorted_vector = sorted_vector;
            quick_sorted_stats_sum.comparison_count += QuickSort(quick_sorted_vector).comparison_count;
            quick_sorted_stats_sum.copy_count += QuickSort(quick_sorted_vector).copy_count;

            vector<int> heap_sorted_vector = sorted_vector;
            heap_sorted_stats_sum.comparison_count += HeapSort(heap_sorted_vector).comparison_count;
            heap_sorted_stats_sum.copy_count += HeapSort(heap_sorted_vector).copy_count;

            vector<int> reverse_sorted_vector = ReverseSortedVec<int>(length);

            vector<int> bubble_reverse_sorted_vector = reverse_sorted_vector;
            bubble_reverse_sorted_stats_sum.comparison_count += BubbleSort(bubble_reverse_sorted_vector).comparison_count;
            bubble_reverse_sorted_stats_sum.copy_count += BubbleSort(bubble_reverse_sorted_vector).copy_count;

            vector<int> quick_reverse_sorted_vector = reverse_sorted_vector;
            quick_reverse_sorted_stats_sum.comparison_count += QuickSort(quick_reverse_sorted_vector).comparison_count;
            quick_reverse_sorted_stats_sum.copy_count += QuickSort(quick_reverse_sorted_vector).copy_count;

            vector<int> heap_reverse_sorted_vector = reverse_sorted_vector;
            heap_reverse_sorted_stats_sum.comparison_count += HeapSort(heap_reverse_sorted_vector).comparison_count;
            heap_reverse_sorted_stats_sum.copy_count += HeapSort(heap_reverse_sorted_vector).copy_count;
        }

        stats bubble_random_average_stats{
            bubble_random_stats_sum.comparison_count / num_vectors,
            bubble_random_stats_sum.copy_count / num_vectors
        };

        stats quick_random_average_stats{
            quick_random_stats_sum.comparison_count / num_vectors,
            quick_random_stats_sum.copy_count / num_vectors
        };

        stats heap_random_average_stats{
            heap_random_stats_sum.comparison_count / num_vectors,
            heap_random_stats_sum.copy_count / num_vectors
        };

        stats bubble_sorted_average_stats{
            bubble_sorted_stats_sum.comparison_count / num_vectors,
            bubble_sorted_stats_sum.copy_count / num_vectors
        };

        stats quick_sorted_average_stats{
            quick_sorted_stats_sum.comparison_count / num_vectors,
            quick_sorted_stats_sum.copy_count / num_vectors
        };

        stats heap_sorted_average_stats{
            heap_sorted_stats_sum.comparison_count / num_vectors,
            heap_sorted_stats_sum.copy_count / num_vectors
        };

        stats bubble_reverse_sorted_average_stats{
            bubble_reverse_sorted_stats_sum.comparison_count / num_vectors,
            bubble_reverse_sorted_stats_sum.copy_count / num_vectors
        };

        stats quick_reverse_sorted_average_stats{
            quick_reverse_sorted_stats_sum.comparison_count / num_vectors,
            quick_reverse_sorted_stats_sum.copy_count / num_vectors
        };

        stats heap_reverse_sorted_average_stats{
            heap_reverse_sorted_stats_sum.comparison_count / num_vectors,
            heap_reverse_sorted_stats_sum.copy_count / num_vectors
        };

        cout << "Vector Length: " << length << "\n";
        cout << "Random Vectors - Bubble Sort Average Stats:\n";
        cout << "   Comparisons: " << bubble_random_average_stats.comparison_count << "\n";
        cout << "   Copies: " << bubble_random_average_stats.copy_count << "\n\n";

        cout << "Random Vectors - Quick Sort Average Stats:\n";
        cout << "   Comparisons: " << quick_random_average_stats.comparison_count << "\n";
        cout << "   Copies: " << quick_random_average_stats.copy_count << "\n\n";

        cout << "Random Vectors - Heap Sort Average Stats:\n";
        cout << "   Comparisons: " << heap_random_average_stats.comparison_count << "\n";
        cout << "   Copies: " << heap_random_average_stats.copy_count << "\n\n";

        cout << "Sorted Vectors - Bubble Sort Average Stats:\n";
        cout << "   Comparisons: " << bubble_sorted_average_stats.comparison_count << "\n";
        cout << "   Copies: " << bubble_sorted_average_stats.copy_count << "\n\n";

        cout << "Sorted Vectors - Quick Sort Average Stats:\n";
        cout << "   Comparisons: " << quick_sorted_average_stats.comparison_count << "\n";
        cout << "   Copies: " << quick_sorted_average_stats.copy_count << "\n\n";

        cout << "Sorted Vectors - Heap Sort Average Stats:\n";
        cout << "   Comparisons: " << heap_sorted_average_stats.comparison_count << "\n";
        cout << "   Copies: " << heap_sorted_average_stats.copy_count << "\n\n";
        cout << "Reverse Sorted Vectors - Bubble Sort Average Stats:\n";
        cout << "   Comparisons: " << bubble_reverse_sorted_average_stats.comparison_count << "\n";
        cout << "   Copies: " << bubble_reverse_sorted_average_stats.copy_count << "\n\n";

        cout << "Reverse Sorted Vectors - Quick Sort Average Stats:\n";
        cout << "   Comparisons: " << quick_reverse_sorted_average_stats.comparison_count << "\n";
        cout << "   Copies: " << quick_reverse_sorted_average_stats.copy_count << "\n\n";

        cout << "Reverse Sorted Vectors - Heap Sort Average Stats:\n";
        cout << "   Comparisons: " << heap_reverse_sorted_average_stats.comparison_count << "\n";
        cout << "   Copies: " << heap_reverse_sorted_average_stats.copy_count << "\n\n";
    }
                                                                                                                                                                                                                                        
    return 0;
}
