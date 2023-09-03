#include <iostream>

int main() {
    int num{}, row{}, col{};

    int myArray[15]{
        0, 0, 1, 0, 0,
        0, 1, 1, 1, 0,
        1, 1, 1, 1, 1
    };

    // 인덱스에서 행렬을 추출 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    std::cout << "원하는 인덱스 값 : ";
    std::cin >> num;

    std::cout << "인덱스 값 " << num << "은 " << num / 5 + 1 << "행, " << num % 5 + 1 << "열입니다." << std::endl;

    // 행렬에서 인덱스를 추출 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    std::cout << "원하는 행 : ";
    std::cin >> row;
    std::cout << "원하는 열 : ";
    std::cin >> col;

    std::cout << "행 " << row << ", 열 " << col << "의 인덱스 값은 " << (row - 1) * 5 + col - 1 << "입니다." << std::endl;
}