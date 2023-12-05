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
    bool operator>(const MyClass& rhs) const {
        return this->value > rhs.value;
    }

    bool operator<(const MyClass& rhs) const {
        return this->value < rhs.value;  
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
				statistics.copy_count += 3; // ИЛИ 2
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
            statistics.comparison_count++;
            i++;
        }
        while (vec[j] > middle) {
            statistics.comparison_count++;
            j--;
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

ostream& operator<<(std::ostream& os, stats& stat)
{
    os << "comparison_count = " << stat.comparison_count << " copy_count = " << stat.copy_count;
    return os;
}

int main() {
    const int num_vectors = 100;
    const vector<size_t> vector_lengths = { 1000, 2000, 3000 , 4000, 5000,6000, 7000, 8000, 9000, 10000, 25000, 50000, 100000 };

    for (size_t length : vector_lengths) {
        stats bubble_random_stats_sum{ 0, 0 };
        stats bubble_sorted_stats_sum{ 0, 0 };
        stats bubble_reverse_sorted_stats_sum{ 0, 0 };   

        stats quick_random_stats_sum{ 0, 0 };
        stats quick_sorted_stats_sum{ 0, 0 };
        stats quick_reverse_sorted_stats_sum{ 0, 0 };

        stats heap_random_stats_sum{ 0, 0 };
        stats heap_sorted_stats_sum{ 0, 0 };
        stats heap_reverse_sorted_stats_sum{ 0, 0 };

        for (int i = 0; i < num_vectors; ++i) {
            vector<int> random_vector = RandomVec<int>(length);

            vector<int> bubble_random_vector = random_vector;
            stats bubble_random_stats = BubbleSort(bubble_random_vector);
            bubble_random_stats_sum.comparison_count += bubble_random_stats.comparison_count;
            bubble_random_stats_sum.copy_count += bubble_random_stats.copy_count; 

            vector<int> quick_random_vector = random_vector;
            stats quick_random_stats = QuickSort(quick_random_vector);
            quick_random_stats_sum.comparison_count += quick_random_stats.comparison_count;
            quick_random_stats_sum.copy_count += quick_random_stats.copy_count;

            vector<int> heap_random_vector = random_vector;
            stats heap_random_stats = HeapSort(heap_random_vector);
            heap_random_stats_sum.comparison_count += heap_random_stats.comparison_count;
            heap_random_stats_sum.copy_count += heap_random_stats.copy_count;
            
        }
        vector<int> sorted_vector = SortedVec<int>(length);

        vector<int> bubble_sorted_vector = sorted_vector;
        stats bubble_sorted_stats = BubbleSort(bubble_sorted_vector);
        bubble_sorted_stats_sum.comparison_count += bubble_sorted_stats.comparison_count;
        bubble_sorted_stats_sum.copy_count += bubble_sorted_stats.copy_count;

        vector<int> quick_sorted_vector = sorted_vector;
        stats quick_sorted_stats = QuickSort(quick_sorted_vector);
        quick_sorted_stats_sum.comparison_count += quick_sorted_stats.comparison_count;
        quick_sorted_stats_sum.copy_count += quick_sorted_stats.copy_count;
      
        vector<int> heap_sorted_vector = sorted_vector;
        stats heap_sorted_stats = HeapSort(heap_sorted_vector);
        heap_sorted_stats_sum.comparison_count += heap_sorted_stats.comparison_count;
        heap_sorted_stats_sum.copy_count += heap_sorted_stats.copy_count;

        vector<int> reverse_sorted_vector = ReverseSortedVec<int>(length);

        vector<int> bubble_reverse_sorted_vector = reverse_sorted_vector;
        stats bubble_reverse_sorted_stats = BubbleSort(bubble_reverse_sorted_vector);
        bubble_reverse_sorted_stats_sum.comparison_count += bubble_reverse_sorted_stats.comparison_count;
        bubble_reverse_sorted_stats_sum.copy_count += bubble_reverse_sorted_stats.copy_count;

        vector<int> quick_reverse_sorted_vector = reverse_sorted_vector;
        stats quick_reverse_sorted_stats = QuickSort(quick_reverse_sorted_vector);
        quick_reverse_sorted_stats_sum.comparison_count += quick_reverse_sorted_stats.comparison_count;
        quick_reverse_sorted_stats_sum.copy_count += quick_reverse_sorted_stats.copy_count;

        vector<int> heap_reverse_sorted_vector = reverse_sorted_vector;
        stats heap_reverse_sorted_stats = HeapSort(heap_reverse_sorted_vector);
        heap_reverse_sorted_stats_sum.comparison_count += heap_reverse_sorted_stats.comparison_count;
        heap_reverse_sorted_stats_sum.copy_count += heap_reverse_sorted_stats.copy_count;


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
     

        cout << "Vector Length: " << length << "\n";
        cout << "Random Vectors - Bubble Sort Average Stats:\n";
        cout << "   Comparisons: " << bubble_random_average_stats.comparison_count << "\n";
        cout << "   Copies: " << bubble_random_average_stats.copy_count << "\n\n";

        cout << "Sorted Vectors - Bubble Sort Average Stats:\n";
        cout << "   Comparisons: " << bubble_sorted_stats_sum.comparison_count << "\n";
        cout << "   Copies: " << bubble_sorted_stats_sum.copy_count << "\n\n";
            
        cout << "Reverse Sorted Vectors - Bubble Sort Average Stats:\n";
        cout << "   Comparisons: " << bubble_reverse_sorted_stats_sum.comparison_count << "\n";
        cout << "   Copies: " << bubble_reverse_sorted_stats_sum.copy_count << "\n\n";

        //

        cout << "Random Vectors - Quick Sort Average Stats:\n";
        cout << "   Comparisons: " << quick_random_average_stats.comparison_count << "\n";
        cout << "   Copies: " << quick_random_average_stats.copy_count << "\n\n";

        cout << "Sorted Vectors - Quick Sort Average Stats:\n";
        cout << "   Comparisons: " << quick_sorted_stats_sum.comparison_count << "\n";
        cout << "   Copies: " << quick_sorted_stats_sum.copy_count << "\n\n";

        cout << "Reverse Sorted Vectors - Quick Sort Average Stats:\n";
        cout << "   Comparisons: " << quick_reverse_sorted_stats_sum.comparison_count << "\n";
        cout << "   Copies: " << quick_reverse_sorted_stats_sum.copy_count << "\n\n";

        //

        cout << "Random Vectors - Heap Sort Average Stats:\n";
        cout << "   Comparisons: " << heap_random_average_stats.comparison_count << "\n";
        cout << "   Copies: " << heap_random_average_stats.copy_count << "\n\n";

        cout << "Sorted Vectors - Heap Sort Average Stats:\n";
        cout << "   Comparisons: " << heap_sorted_stats_sum.comparison_count << "\n";
        cout << "   Copies: " << heap_sorted_stats_sum.copy_count << "\n\n";

        cout << "Reverse Sorted Vectors - Heap Sort Average Stats:\n";
        cout << "   Comparisons: " << heap_reverse_sorted_stats_sum.comparison_count << "\n";
        cout << "   Copies: " << heap_reverse_sorted_stats_sum.copy_count << "\n\n";

    }
    vector<string> v1s = { "d", "f", "c" , "v", "a", "r" , "n", "e", "s", "m", "j", "a", "x", "t", "y" , "u", "b", "e" , "q", "k", "l", "g", "b", "r" };
    vector<string> v2s = { "d", "f", "c" , "v", "a", "r" , "n", "e", "s", "m", "j", "a", "x", "t", "y" , "u", "b", "e" , "q", "k", "l", "g", "b", "r" };
    vector<string> v3s = { "d", "f", "c" , "v", "a", "r" , "n", "e", "s", "m", "j", "a", "x", "t", "y" , "u", "b", "e" , "q", "k", "l", "g", "b", "r" };

    cout << "Vector Before Sorting: " << endl;
    PrintVector(v1s);
    stats statistics1 = BubbleSort(v1s);
    cout << "Vector After Bubble Sorting: " << endl;
    PrintVector(v1s);
    cout << "Bubble Sorting Comparison Count: " << statistics1.comparison_count << endl;
    cout << "Bubble Sorting Copy Count: " << statistics1.copy_count << endl << endl;

    cout << "Vector Before Sorting: " << endl;
    PrintVector(v2s);
    stats statistics2 = QuickSort(v2s);
    cout << "Vector After Quick Sorting: " << endl;
    PrintVector(v1s);
    cout << "Quick Sorting Comparison Count: " << statistics2.comparison_count << endl;
    cout << "Quick Sorting Copy Count: " << statistics2.copy_count << endl << endl;

    cout << "Vector Before Sorting: " << endl;
    PrintVector(v3s);
    stats statistics3 = HeapSort(v3s);
    cout << "Vector After Heap Sorting: " << endl;
    PrintVector(v3s);
    cout << "Heap Sorting Comparison Count: " << statistics3.comparison_count << endl;
    cout << "Heap Sorting Copy Count: " << statistics3.copy_count << endl << endl;

    vector<MyClass> v1;
    vector<MyClass> v2;
    vector<MyClass> v3;

    srand(static_cast<unsigned int>(time(0)));
    for (size_t i = 0; i < 50; ++i) {
        v1.push_back(rand() %100);
    }

    srand(static_cast<unsigned int>(time(0)));
    for (size_t i = 0; i < 50; ++i) {
        v2.push_back(rand() % 100);
    }

    srand(static_cast<unsigned int>(time(0)));
    for (size_t i = 0; i < 50; ++i) {
        v3.push_back(rand() % 100);
    }
    
    cout << "Vector Before Sorting: " << endl;
    for(const auto& obj : v1) {
        cout << obj.get_value() << " ";
    }
    stats statistics4 = BubbleSort(v1);
    cout << endl;
    cout << "Vector After Bubble Sorting: " << endl;
    for (const auto& obj : v1) {
        cout << obj.get_value() << " ";
    }
    cout << endl;
    cout << endl;
    cout << "Vector Before Sorting: " << endl;
    for (const auto& obj : v2) {
        cout << obj.get_value() << " ";
    }
    stats statistics5 = QuickSort(v2);
    cout << endl;
    cout << "Vector After Quick Sorting: " << endl;
    for (const auto& obj : v2) {
        cout << obj.get_value() << " ";
    }
    cout << endl;

    cout << endl;
    cout << "Vector Before Sorting: " << endl;
    for (const auto& obj : v3) {
        cout << obj.get_value() << " ";
    }
    stats statistics6 = HeapSort(v3);
    cout << endl;
    cout << "Vector After Heap Sorting: " << endl;
    for (const auto& obj : v3) {
        cout << obj.get_value() << " ";
    }
    cout << endl;
    return 0;
}
