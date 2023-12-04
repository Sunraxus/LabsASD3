#include<iostream>
#include<vector>
#include <cstdlib> 
#include <stdexcept>

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

stats& QuickSort(vector<int>& vec, int start, int end) {
    stats statistics;

    int i = start;
    int j = end;
    int middle = vec[(start + end) / 2];

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
        stats left_statistics = QuickSort(vec, start, j);
        statistics.comparison_count += left_statistics.comparison_count;
        statistics.copy_count += left_statistics.copy_count;
    }
    if (i < end) {
        stats right_statistics = QuickSort(vec, i, end);
        statistics.comparison_count += right_statistics.comparison_count;
        statistics.copy_count += right_statistics.copy_count;
    }

    return statistics;
}

stats& QuickSort(vector<int>& vec) {
    return QuickSort(vec, 0, vec.size() - 1);
}

void Heapify(vector<int>& vec, int size, int i, stats& statistics) {
    int max = i; 
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < size && vec[left] > vec[max]) {
        max = left;
        statistics.comparison_count++;
        statistics.copy_count++;
    }
    if (right < size && vec[right] > vec[max]) {
        max = right;
        statistics.comparison_count++;
        statistics.copy_count++;
    }
    if (max != i) {
        custom_swap(vec[i], vec[max]);
        statistics.copy_count += 3;
        Heapify(vec, size, max, statistics);
    }
}

stats& HeapSort(vector<int>& vec) {
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
void PrintVector(vector<T> vec) {
	for (int i = 0; i < vec.size(); ++i)
		cout << vec[i] << " ";
	cout << "\n\n";
}

int main() {
    vector<string> v1 = { "d","f", "c" , "b", "a", "r"};
    vector<int> v2 = { 11 , 10 , 11 , 9 , 14 , 3 , 2 , 20 , 19 };
    vector<int> v3 = { 1 , 10 , 11 , 9 , 14 , 3 , 2 , 20 , 19 };

	cout << "Vector Before Sorting: " << endl;
	PrintVector(v1);

	stats statistics1 = BubbleSort(v1);

	cout << "Vector After Sorting: " << endl;
	PrintVector(v1);
	cout << "Comparison Count: " << statistics1.comparison_count << endl;
	cout << "Copy Count: " << statistics1.copy_count << endl;

    cout << "Vector Before Sorting: " << endl;
    PrintVector(v2);

    stats statistics2 = QuickSort(v2);

    cout << "Vector After Sorting: " << endl;
    PrintVector(v2);
    cout << "Comparison Count: " << statistics2.comparison_count << endl;
    cout << "Copy Count: " << statistics2.copy_count << endl;

    cout << "Vector Before Sorting: " << endl;
    PrintVector(v3);
    stats statistics3 = HeapSort(v3);
    cout << "Vector After Sorting: " << endl;
    PrintVector(v3);
    cout << "Comparison Count: " << statistics3.comparison_count << endl;
    cout << "Copy Count: " << statistics3.copy_count << endl;
}