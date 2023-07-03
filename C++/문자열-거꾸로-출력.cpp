#include <iostream>

int main() {
    const int SIZE{ 7 };
    char myString[SIZE]{};

    std::cout << "문자열을 입력 : ";
    std::cin >> myString;

    std::cout << "거꾸로 문자열 : ";
    for (int i{ SIZE - 1 }; i >= 0; i--) {
        std::cout << myString[i];
    }
}