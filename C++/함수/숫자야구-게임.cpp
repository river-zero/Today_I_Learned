#include <iostream>
#include <random>

void ComputerNum(int answer[], int size);
void GuessNum(int guess[], int size);
bool CheckNum(int answer[], int guess[], int size);

int main() {
    const int numSize{ 3 };
    int answer[numSize]{}, guess[numSize]{};

    ComputerNum(answer, numSize);
    std::cout << "숫자야구를 시작합니다! : ";

    //for (int i{}; i < numSize; i++) {
    //    std::cout << answer[i] << " ";
    //}

    while (true) {
        GuessNum(guess, numSize);
        if (CheckNum(answer, guess, numSize)) { break; }
    }
}

void ComputerNum(int answer[], int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 9);

    while (true) {
        bool isOverlap = false;

        for (int i{}; i < size; i++) {
            answer[i] = dis(gen);
            for (int j{}; j < i; j++) {
                if (answer[i] == answer[j]) {
                    isOverlap = true;
                    break;
                }
            }
            if (isOverlap) { break; }
        }
        if (!isOverlap && answer[0] != 0) { return; }
    }
}

void GuessNum(int guess[], int size) {
    const int numSize{ 3 };
    char input[numSize + 1]{};

    std::cin >> input;
    for (int i{}; i < size; i++) {
        guess[i] = input[i] - '0';
    }
}

bool CheckNum(int answer[], int guess[], int size) {
    int ball{}, strike{}, out{};

    for (int i{}; i < size; i++) {
        for (int j{}; j < size; j++) {
            if (answer[i] == guess[j]) {
                if (i == j) { strike++; }
                else { ball++; }
            }
        }
    }
    out = size - ball - strike;

    if (strike == size) {
        std::cout << "정답입니다!" << std::endl;
        return true;
    }
    else {
        std::cout << strike << " STRIKE, " << ball << " BALL, " << out << " OUT";
        std::cout << std::endl << "다시 입력해주세요. : ";
        return false;
    }
}