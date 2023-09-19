/*--------------------------------------------------------------------------------
    m x n인 맵에서 좌상단에서 우하단으로 가는 경로의 수를 구하세요.
    단, 방향은 아래쪽 또는 오른쪽으로만 가능합니다.

    모든 셀을 한 번씩만 방문하므로 시간 복잡도는 O(m x n)
    행과 열을 고려하므로 공간 복잡도는 O(m + n)
--------------------------------------------------------------------------------*/

#include <iostream>
#include <map>
#include <string>

using way_history = std::map<std::string, int>;

int FindWays(int m, int n, way_history& h) {
    const std::string key = std::to_string(m) + "," + std::to_string(n);
    if (h.count(key) == 1) {
        return h[key];
    }

    const std::string rkey = std::to_string(n) + "," + std::to_string(m);
    if (h.count(rkey) == 1) {
        return h[rkey];
    }

    if (m == 0 || n == 0) {
        return 0;
    }
    if (m == 1 && n == 1) {
        return 1;
    }

    h[key] = FindWays(m - 1, n, h) + FindWays(m, n - 1, h);
    return h[key];
}

int main() {
    way_history h;
    std::cout << FindWays(3, 3, h) << std::endl;
}