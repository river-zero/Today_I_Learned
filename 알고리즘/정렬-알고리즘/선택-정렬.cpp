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

void SelectionSort(int input[], int size) {
	for (int i{}; i < size - 1; i++) {
		int minIndex{ i };

		for (int j{ i + 1 }; j < size; j++) {
			if (input[minIndex] > input[j]) {
				minIndex = j;
			}
		}

		Swap(input[i], input[minIndex]);
	}
}

int main() {
	const int ARRAY_SIZE{ 5 };
	int array[ARRAY_SIZE]{ 8,7,2,3,1 };

	SelectionSort(array, ARRAY_SIZE);

	Print(array, ARRAY_SIZE);
}