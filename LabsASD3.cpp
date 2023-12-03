#include<iostream>
#include<vector>
#include <cstdlib> 
#include <stdexcept>

using namespace std;

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};

stats& BubbleSort(vector<int>& vector) {
	stats statistics;
	for (int i(0); i < (vector.size() - 1); ++i) {
		statistics.comparison_count += 1;
		for (int j(0); j < (vector.size() - i - 1); ++j) {
			statistics.comparison_count += 1;
			if (vector[j] > vector[j + 1]) {
				swap(vector[j], vector[j + 1]);
				statistics.copy_count += 3;
			}
			statistics.comparison_count += 1;
		}
		statistics.comparison_count += 1;
	}
	statistics.comparison_count += 1;
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
            swap(vec[i], vec[j]);
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

void PrintVector(vector<int> vec) {
	for (int i = 0; i < vec.size(); ++i)
		cout << vec[i] << " ";
	cout << "\n\n";
}

int main() {
	vector<int> v1 = { 1 , 10 , 11 , 9 , 14 , 3 , 2 , 20 , 19 };
    vector<int> v2 = { 11 , 10 , 11 , 9 , 14 , 3 , 2 , 20 , 19 };

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
}