/*------------------------------------------------------------------------------
    최대 sum까지 각각 크기 n의 숫자 배열을 반복하므로 시간 복잡도는 O(m x n)
    맵의 크기는 가능한 sum 값의 범위에 비례하므로 공간 복잡도는 O(m)
------------------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<int, bool> memo;

bool CanSum(int sum, const vector<int>& numbers) {
    if (memo.find(sum) != memo.end()) {
        return memo[sum];
    }
    if (sum == 0) {
        return true;
    }
    if (sum < 0) {
        return false;
    }

    for (int num : numbers) {
        int remainder = sum - num;
        if (canSum(remainder, numbers)) {
            memo[sum] = true;
            return true;
        }
    }

    memo[sum] = false;
    return false;
}

int main() {
    vector<int> numbers1 = {2, 3, 5};
    int sum1 = 8;
    
    vector<int> numbers2 = {8,6};
    int sum2 = 7;

    std::cout << std::boolalpha;
    std::cout << canSum(sum1, numbers1) << std::endl;        
    std::cout << canSum(sum2, numbers2) << std::endl;
}