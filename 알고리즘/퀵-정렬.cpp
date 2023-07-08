#include <iostream>

void Print(int input[], int size) {
	for (int i{}; i < size; i++) {
		std::cout << input[i] << " ";
	}
	std::cout << std::endl;
}

void Swap(int& value1, int& value2) {
	int temp = value1;
	value1 = value2;
	value2 = temp;
}

void QuickSort(int input[], int left, int right) {
	int i = left;
	int j = right;
	int pivot = input[(left + right) / 2];

	do {
		while (input[i] < pivot) {
			i++;
		}
		while (input[j] > pivot) {
			j--;
		}

		if (i <= j) {
			Swap(input[i], input[j]);
			i++;
			j--;
		}
	} while (i <= j);

	if (left < j) {
		QuickSort(input, left, j);
	}
	if (i < right) {
		QuickSort(input, i, right);
	}
}

int main() {
	const int ARRAY_SIZE{ 5 };
	int array[ARRAY_SIZE]{ 8,7,2,3,1 };

	QuickSort(array, 0, ARRAY_SIZE - 1);

	Print(array, ARRAY_SIZE);
}