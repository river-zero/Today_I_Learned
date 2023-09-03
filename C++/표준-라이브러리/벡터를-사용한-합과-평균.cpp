#include <iostream>
#include <vector>

std::vector<int> Input() {
    std::cout << "정수를 입력: ";

    std::vector<int> input;

    while (std::cin >> num) {
        input.push_back(num); // int가 아닌 입력 시 종료
    }

    return input;
}

int Sum(const std::vector<int>& array) {
    int sum{};
    for (int num : array) {
        sum += num;
    }
    return sum;
}

int WhereMin(const std::vector<int>& array) {
    int min = array[0];
    int minIndex = 0;
    int index = 0;

    for (int num : array) {
        if (num < min) {
            min = num;
            minIndex = index;
        }
        index++;
    }

    return minIndex;
}

int main() {
    std::vector<int> array = Input();
    std::cout << "입력한 정수들의 합: " << Sum(array) << std::endl;
    std::cout << "최소값의 위치: " << WhereMin(array) << std::endl;
}

/*---------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <sstream>

std::vector<int> Input() {
    std::cout << "정수를 입력: ";

    std::vector<int> input;
    std::string line;

    std::getline(std::cin, line); // 한 줄을 통째로 입력받음

    if (line.empty()) {
        std::cout << "입력이 없습니다." << std::endl;
        return {}; // 빈 벡터 반환
    }
    
    std::stringstream ss(line); // stringstream으로 변환

    // 문자열에서 정수들을 읽어와 벡터에 저장
    int num;
    while (ss >> num) {
        input.push_back(num);

        // 다음 문자가 공백인 경우 스트림에서 제거
        if (ss.peek() == ' ') {
            ss.ignore();
        }
    }

    return input;
}

int Sum(const std::vector<int>& array) {
    int sum{};
    for (int num : array) {
        sum += num;
    }
    return sum;
}

int WhereMin(const std::vector<int>& array) {
    int min      = array[0];
    int minIndex = 0;
    int index    = 0;

    for (int num : array) {
        if (num < min) {
            min = num;
            minIndex = index;
        }
        index++;
    }

    return minIndex;
}

int main() {
    std::vector<int> array = Input();

    if (!array.empty()) { // 입력이 있는 경우에만 출력
        std::cout << "입력한 정수들의 합: " << Sum(array) << std::endl;
        std::cout << "최소값의 위치: " << WhereMin(array) << std::endl;
    }
}
---------------------------------------------------------------------*/