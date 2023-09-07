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

void BubbleSort(int input[], int size) {
	for (int i{}; i < size - 1; i++) {
		for (int j{}; j < size - i - 1; j++) {
			if (input[j] > input[j + 1]) {
				Swap(input[j], input[j + 1]);
			}
		}
	}
}

int main() {
	const int ARRAY_SIZE{ 5 };
	int array[ARRAY_SIZE]{ 8,7,2,3,1 };

	BubbleSort(array, ARRAY_SIZE);

	Print(array, ARRAY_SIZE);
}