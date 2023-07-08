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

void Merge(int input[], int start, int half, int end, int temp[]) {
	int i = start;
	int j = half + 1;
	int tempIndex = 0;

	while (i <= half && j <= end) {
		if (input[i] < input[j]) {
			temp[tempIndex++] = input[i++];
		}
		else {
			temp[tempIndex++] = input[j++];
		}
	}

	while (i <= half) {
		temp[tempIndex++] = input[i++];
	}

	while (j <= end) {
		temp[tempIndex++] = input[j++];
	}

	tempIndex = 0;
	for (int i{ start }; i <= end; i++) {
		input[i] = temp[tempIndex++];
	}
}

void MergeSort(int input[], int start, int end, int temp[]) {
	if (start >= end) {
		return;
	}

	int half = (start + end) / 2;

	MergeSort(input, start, half, temp);
	MergeSort(input, half + 1, end, temp);

	Merge(input, start, half, end, temp);
}

int main() {
	const int ARRAY_SIZE{ 5 };
	int array[ARRAY_SIZE]{ 8,7,2,3,1 };

	int tempArray[ARRAY_SIZE]{};
	MergeSort(array, 0, ARRAY_SIZE - 1, tempArray);
	
    Print(array, ARRAY_SIZE);
}