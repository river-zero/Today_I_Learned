/*--------------------------------------------------------------------------------
    m x n인 맵에서 좌상단에서 우하단으로 가는 경로의 수를 구하세요.
    단, 방향은 아래쪽 또는 오른쪽으로만 가능합니다.

    모든 셀을 한 번씩만 방문하므로 시간 복잡도는 O(m x n)
    바로 위쪽 셀과 바로 왼쪽 셀의 정보만 필요하므로 공간 복잡도는 O(min(m, n))
--------------------------------------------------------------------------------*/

#include <iostream>
#include <vector>

using namespace std;

int FindWays(int m, int n) {
    // 더 작은 값으로 m 또는 n을 선택
    if (m > n) {
        swap(m, n);
    }

    // 1차원 배열을 만들고 초기화
    vector<int> dp(m, 1);

    // dp 배열을 업데이트
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            dp[j] += dp[j - 1];
        }
    }

    return dp[m - 1];
}

int main() {
    int m, n;
    cout << "행 수를 입력하세요: ";
    cin >> m;
    cout << "열 수를 입력하세요: ";
    cin >> n;

    int result = uniquePaths(m, n);
    cout << "좌상단에서 우하단으로 가는 경로의 수: " << result << endl;
}