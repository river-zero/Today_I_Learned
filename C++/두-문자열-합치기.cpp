#include <iostream>

int main() {
    const int SIZE{ 6 }, SIZE2{ 11 };
    char myString1[SIZE]{}, myString2[SIZE]{}, myString3[SIZE2]{};

    std::cout << "두 문자열을 입력 : ";
    std::cin >> myString1 >> myString2;

    std::cout << "합쳐진 문자열 : ";

    for (int i{}; i < SIZE - 1; i++) {
        myString3[i] = myString1[i];
    }

    for (int i{ SIZE - 1 }; i < SIZE2 - 1; i++) {
        myString3[i] = myString2[i - SIZE + 1];
    }

    std::cout << myString3;
}