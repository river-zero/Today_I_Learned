/*------------------------------
    시간 복잡도는 O(m^2 x n)
    공간 복잡도는 O(m^2)
------------------------------*/

#include <iostream>
#include <vector>

using int_vector = std::vector<int>;

std::shared_ptr<int_vector> HowSum(int sum, const int_vector& numbers) {
	std::vector<std::shared_ptr<int_vector>> table(sum + 1, nullptr);

	table[0] = std::make_shared<int_vector>(0);

	for (int i = 0; i <= sum; i++) {
		if (table[i] != nullptr) {
			for (auto e : numbers) {
				if (i + e <= sum) {
					table[i + e] = std::make_shared<int_vector>(*table[i]);
					table[i + e]->push_back(e);
				}
			}
		}
	}

	return table[sum];
}

int main() {
	auto ret = HowSum(8, { 2, 3, 5 });

	std::cout << "{ ";
	if (ret != nullptr) {
		for (size_t i = 0; i < ret->size(); ++i) {
			std::cout << (*ret)[i];
			if (i != ret->size() - 1) {
				std::cout << ", ";
			}
		}
	}
	std::cout << " }" << std::endl;
}