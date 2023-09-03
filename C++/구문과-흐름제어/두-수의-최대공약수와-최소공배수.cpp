#include <iostream>

int main() {
    int num1{}, num2{}, keep{}, multiply{};

    std::cout << "원하는 두 수를 입력: ";
    std::cin >> num1 >> num2;

    multiply = num1 * num2;

    while (num2 != 0) {
        keep = num1 % num2;
        num1 = num2;
        num2 = keep;
    }

    std::cout << "최대공약수: " << num1 << std::endl;
    std::cout << "최소공배수: " << multiply / num1 << std::endl;
}