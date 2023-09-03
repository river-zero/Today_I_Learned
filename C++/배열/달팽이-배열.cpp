#include <iostream>

int main() {
    const int nums{ 5 };
    int snail[nums][nums]{}, line{ nums }, row{}, col{ -1 }, input{ 1 }, index{ 1 };

    while (true) {
        if (line <= 0) {
            break;
        }

        for (int i{}; i < line; i++) {
            col += index;
            snail[row][col] = input;
            input++;
        }

        line--;

        for (int i{}; i < line; i++) {
            row += index;
            snail[row][col] = input;
            input++;
        }

        index *= -1;
    }

    for (int i{}; i < nums; i++) {
        for (int j{}; j < nums; j++) {
            std::cout << snail[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}