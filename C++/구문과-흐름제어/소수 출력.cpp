#include <iostream>

int main() {
    int num{ 2 };

    for (; num <= 100; num++) {
        int divide{ 2 };

        for (; divide < num; divide++) {
            if (num % divide == 0) {
                break;
            }
        }

        if (num == divide) {
            std::cout << num << std::endl;
        }
    }
}