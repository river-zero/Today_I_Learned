/*---------------------------------------------------------------------------------
    최대 sum까지 각각 크기 n의 숫자 배열을 반복하므로 시간 복잡도는 O(m x n)
    std::copy 시간을 고려한다면 공간 복잡도는 O(m^2 x n), 그렇지 않다면 O(m^2)
---------------------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <map>

using int_vector = std::vector<int>;
using sum_history = std::map<int, std::shared_ptr<int_vector>>;

std::shared_ptr<int_vector> OptimizeSum(
	int sum,
	const int_vector& numbers,
	std::shared_ptr<sum_history> h
) {
	if (h->count(sum) == 1) {
		return (*h)[sum];
	}
	if (sum == 0) {
		return std::make_shared<int_vector>();
	}
	if (sum < 0) {
		return nullptr;
	}

	int remain = 0;
	std::shared_ptr<int_vector> optimized = nullptr;

	for (auto e : numbers) {
		remain = sum - e;
		auto ret = OptimizeSum(remain, numbers, h);

		if (ret != nullptr) {
			std::shared_ptr<int_vector> v = std::make_shared<int_vector>();
			v->resize(ret->size());
			std::copy(ret->begin(), ret->end(), v->begin());
			v->push_back(e);
			if (optimized == nullptr || v->size() < optimized->size()) {
				optimized = v;
			}
		}
	}

	(*h)[sum] = optimized;
	return (*h)[sum];
}

void Print(std::shared_ptr<int_vector> r) {
	std::cout << "{ ";

	if (r != nullptr) {
		for (auto e : *r) {
			std::cout << e << " ";
		}
	}

	std::cout << "}" << std::endl;
}

int main() {
	Print(OptimizeSum(7, { 5,3,4,7 }, std::make_shared<sum_history>()));
	Print(OptimizeSum(7, { 1, 4 }, std::make_shared<sum_history>()));
	Print(OptimizeSum(900, { 7, 14 }, std::make_shared<sum_history>()));
	Print(OptimizeSum(1750, { 10, 50, 100, 500, 1000 }, std::make_shared<sum_history>()));
}