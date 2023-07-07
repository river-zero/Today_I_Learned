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

void InsertionSort(int input[], int size) {
	for (int i{ 1 }; i < size; i++) {
		int j = i;
		int target = input[i];

		while (--j >= 0 && target < input[j]) {
			input[j + 1] = input[j];
			input[j] = target;
		}
	}
}

int main() {
	const int ARRAY_SIZE{ 5 };
	int array[ARRAY_SIZE]{ 8,7,2,3,1 };

	InsertionSort(array, ARRAY_SIZE);

	Print(array, ARRAY_SIZE);
}