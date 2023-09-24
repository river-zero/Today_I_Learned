/*------------------------
    시간 복잡도는 O(n)
    공간 복잡도는 O(n)
------------------------*/

#include <iostream>
#include <vector>

int64_t Fibonacci(const int n) {
	std::vector<int64_t> table(n + 1, 0);

	// base case
	table[0] = 0;
	table[1] = 1;

	// traverse
	for (int i = 2; i <= n; i++) {
		table[i] = table[i - 1] + table[i - 2];
	}
	/*for (int i = 0; i <= n; i++) {
		if (i + 1 <= n) {
			table[i + 1] += table[i];
		}
		if (i + 2 <= n) {
			table[i + 2] += table[i];
		}
	}*/

	return table[n];
}

int main() {
	std::cout << Fibonacci(50) << std::endl;
}