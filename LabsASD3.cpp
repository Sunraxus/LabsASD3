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


int Partition(vector<int>& vec, int start, int end) {

	int supp_elem = end;
	int j = start;
	for (int i = start; i < end; ++i) {
		if (vec[i] < vec[supp_elem]) {
			swap(vec[i], vec[j]);
			++j;
		}
	}
	swap(vec[j], vec[supp_elem]);
	return j;
}

void Quicksort(vector<int>& vec, int start, int end) {

	if (start < end) {
		int p = Partition(vec, start, end);
		Quicksort(vec, start, p - 1);
		Quicksort(vec, p + 1, end);
	}

}

void PrintVector(vector<int> vec) {
	for (int i = 0; i < vec.size(); ++i)
		cout << vec[i] << " ";
	cout << "\n\n";
}

int main() {
	vector<int> v = { 1 , 10 , 11 , 9 , 14 , 3 , 2 , 20 , 19 };

	cout << "Vector Before Sorting: " << endl;
	PrintVector(v);

	stats statistics = BubbleSort(v);

	cout << "Vector After Sorting: " << endl;
	PrintVector(v);
	std::cout << "Comparison Count: " << statistics.comparison_count << std::endl;
	std::cout << "Copy Count: " << statistics.copy_count << std::endl;
}