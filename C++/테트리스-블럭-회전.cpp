#include <iostream>

const int SIZE{ 3 };
int rotate{};

enum {
    stop, left, right
};

int block[SIZE][SIZE]{
    { 0, 1, 0 },
    { 0, 1, 1 },
    { 0, 1, 0 }
};

void PrintBlock(int block[SIZE][SIZE]) {
    for (int i{}; i < SIZE; i++) {
        for (int j{}; j < SIZE; j++) {
            std::cout << block[i][j];
        }
        std::cout << std::endl;
    }
}

void LeftRotateBlock(int block[SIZE][SIZE]) {
    int temp[SIZE][SIZE]{};

    for (int i{}; i < SIZE; i++) {
        for (int j{}; j < SIZE; j++) {
            temp[i][j] = block[j][SIZE - i - 1];
        }
    }

    for (int i{}; i < SIZE; i++) {
        for (int j{}; j < SIZE; j++) {
            block[i][j] = temp[i][j];
        }
    }
}

void RightRotateBlock(int block[SIZE][SIZE]) {
    int temp[SIZE][SIZE]{};

    for (int i{}; i < SIZE; i++) {
        for (int j{}; j < SIZE; j++) {
            temp[i][j] = block[SIZE - j - 1][i];
        }
    }

    for (int i{}; i < SIZE; i++) {
        for (int j{}; j < SIZE; j++) {
            block[i][j] = temp[i][j];
        }
    }
}

int main() {
    PrintBlock(block);

    while (true) {
        std::cout << "왼쪽으로 90도 회전은 1, 오른쪽으로 90도 회전은 2, 종료하려면 0 : ";
        std::cin >> rotate;

        if (rotate == left) {
            std::cout << "==========" << std::endl;
            LeftRotateBlock(block);
            PrintBlock(block);
        }
        else if (rotate == right) {
            std::cout << "==========" << std::endl;
            RightRotateBlock(block);
            PrintBlock(block);
        }
        else if (rotate == stop) {
            break;
        }
        else {
            std::cout << "다시 시도해주세요." << std::endl;
        }
    }
}