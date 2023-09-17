/*-------------------------------------------------------------------
    각 항은 한 번만 계산되고 메모에 저장되므로 시간 복잡도는 O(n)
    공간 복잡도는 사용된 메모이제이션 배열에 따라 결정되므로 O(n)
-------------------------------------------------------------------*/

#include <iostream>
#include <map>

int64_t Fibonacci_memo(int n, std::map<int, int64_t>& memo) {
	if (memo.count(n) == 1) {
		return memo[n];
	}
	
	if (n <= 2) {
		return 1;
	}

	memo[n] = Fibonacci_memo(n - 1, memo) + Fibonacci_memo(n - 2, memo);
	return memo[n];
}

int main() {
	std::map<int, int64_t> memo;
	std::cout << Fibonacci_memo(50, memo);
}