#include <iostream>

int main() {
    const int SIZE{ 7 }, JUMP{ 'a' - 'A' };
    char myString[SIZE]{};

    std::cout << "문자열을 입력 : ";
    std::cin >> myString;

    std::cout << "대문자 문자열 : ";
    for (int i{}; i < SIZE; i++) {
        if (myString[i] >= 'a') {
        std::cout << char(myString[i] - JUMP);
        }
        else {
            std::cout << char(myString[i]);
        }
    }
}