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

void SequentialSort(int input[], int size) {
	for (int i{}; i < size - 1; i++) {
		for (int j{ i + 1 }; j < size; j++) {
			if (input[i] > input[j]) {
				Swap(input[i], input[j]);
			}
		}
	}
}

int main() {
	const int ARRAY_SIZE{ 5 };
	int array[ARRAY_SIZE]{ 8,7,2,3,1 };

	SequentialSort(array, ARRAY_SIZE);

	Print(array, ARRAY_SIZE);
}