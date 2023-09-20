/*------------------------------------------------------------------------------
    최대 sum까지 각각 크기 n의 숫자 배열을 반복하므로 시간 복잡도는 O(m x n)
    맵의 크기는 가능한 sum 값의 범위에 비례하므로 공간 복잡도는 O(m)
    입력과 출력을 모두 고려한다면 공간 복잡도는 O(m^2)
------------------------------------------------------------------------------*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <algorithm>

using namespace std;

using result = shared_ptr<vector<int>>;

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
    std::cout << "{";
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i];
        if (i < v.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "}";
    return os;
}

result HowSum(const vector<int>& numbers, int sum, unordered_map<int, result>& memo) {
    if (memo.count(sum) == 1) {
        return memo[sum];
    }

    if (sum == 0) {
        return make_shared<vector<int>>();
    }
    if (sum < 0) {
        return nullptr;
    }

    for (const auto e : numbers) {
        auto r = canSum(numbers, sum - e, memo);
        if (r != nullptr) {
            r->push_back(e);
            memo[sum] = r;
            return memo[sum];
        }
    }

    // 다 돌아도 반환이 없으니 오답
    memo[sum] = nullptr;
    return memo[sum];
}

int main() {
    vector<int> numbers1 = { 2, 3, 5 };
    int sum1 = 8;

    vector<int> numbers2 = { };
    int sum2 = 7;

    unordered_map<int, result> memo;

    result result1 = canSum(numbers1, sum1, memo);
    result result2 = canSum(numbers2, sum2, memo);

    std::cout << std::boolalpha;

    if (result1 != nullptr) {
        std::cout << "Result for the first scenario: " << *result1 << std::endl;
    } else {
        std::cout << "No combination found for the first scenario." << std::endl;
    }

    if (result2 != nullptr) {
        std::cout << "Result for the second scenario: " << *result2 << std::endl;
    } else {
        std::cout << "No combination found for the second scenario." << std::endl;
    }
}