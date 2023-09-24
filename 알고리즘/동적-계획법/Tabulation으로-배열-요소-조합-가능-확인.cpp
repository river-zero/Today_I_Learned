/*----------------------------
    시간 복잡도는 O(m x n)
    공간 복잡도는 O(m)
----------------------------*/

#include <iostream>
#include <vector>

bool CanSum(int sum, const std::vector<int>& numbers) {
	std::vector<bool> table(sum + 1, false);
	
	table[0] = true;

	for (int i = 0; i <= sum; i++) {
		if (table[i] == true) {
			for (auto e : numbers) {
				if (i + e <= sum) {
					table[i + e] = true;
				}
			}
		}
	}

	return table[sum];
}

int main() {
	std::cout << std::boolalpha;
	std::cout << CanSum(8, { 2, 3, 5 });
}