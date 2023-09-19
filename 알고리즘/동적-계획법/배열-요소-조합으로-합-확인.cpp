/*------------------------------------------------------------------------------
    최대 sum까지 각각 크기 n의 숫자 배열을 반복하므로 시간 복잡도는 O(m x n)
    맵의 크기는 가능한 sum 값의 범위에 비례하므로 공간 복잡도는 O(m)
------------------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// 다이나믹 프로그래밍을 위한 메모이제이션을 위한 해시맵
unordered_map<int, bool> memo;

// 다이나믹 프로그래밍 함수
bool CanSum(int sum, const vector<int>& numbers) {
    // 이미 계산한 결과가 있는 경우, 바로 반환
    // memo.end(): unordered_map에서 키를 찾지 못한 경우를 나타내는 반복자(iterator)의 끝을 나타내는 특수한 값입니다.
    if (memo.find(sum) != memo.end()) {
        return memo[sum];
    }

    // 기저 사례: sum이 0이면 항상 만들 수 있음
    if (sum == 0) {
        return true;
    }

    // sum이 음수면 만들 수 없음
    if (sum < 0) {
        return false;
    }

    // numbers 배열을 순회하면서 가능한 조합을 찾음
    for (int num : numbers) {
        int remainder = sum - num;
        if (canSum(remainder, numbers)) {
            // 가능한 조합을 찾으면 true를 반환하고 메모이제이션
            memo[sum] = true;
            return true;
        }
    }

    // 가능한 조합을 찾지 못하면 false를 반환하고 메모이제이션
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