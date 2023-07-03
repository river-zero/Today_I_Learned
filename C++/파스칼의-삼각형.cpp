#include <iostream>

int main() {
    const int nums{ 5 };
    int pascal[nums][nums]{};

    for (int i{}; i < nums; i++) {
        for (int k{}; k < nums - i - 1; k++) {
        std::cout << " ";
        }
 
        for (int j{}; j <= i; j++) {
            if (i == j || j == 0) {
                pascal[i][j] = 1;
            }
            else {
                pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
            }
 
            std::cout << pascal[i][j] << " ";
        }
 
        std::cout << std::endl;
    }
}