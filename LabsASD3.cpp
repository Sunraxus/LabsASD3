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
    vector<string> v1 = { "d", "f", "c" , "b", "a", "r"};
    vector<string> v2 = { "d", "f", "c" , "b", "a", "r" };
    vector<string> v3 = { "d", "f", "c" , "b", "a", "r" };
    //1 , 10 , 11 , 9 , 14 , 3 , 2 , 20 , 19
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

    vector<MyClass> v4;
    v4.push_back(MyClass(5));
    v4.push_back(MyClass(2));
    v4.push_back(MyClass(8));
    cout << "Vector Before Sorting: " << endl;
    for (const auto& obj : v4) {
        std::cout << obj.get_value() << " ";
    }
    stats statistics4 = BubbleSort(v4);
    cout << endl;
    for (const auto& obj : v4) {
        std::cout << obj.get_value() << " ";
    }
}