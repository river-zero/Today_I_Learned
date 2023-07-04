// 하노이의 탑 - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#include <iostream>

int UserInput();
void Hanoi(int num, char from, char temp, char to);
void Move(char from, char to);

int main() {
    int num{ UserInput() };
    Hanoi(num, 'A', 'B', 'C');
}

int UserInput() {
    int num{};
    std::cout << "원판의 개수 : ";
    std::cin >> num;
    return num;
}

void Hanoi(int num, char from, char temp, char to) {
    if (num == 1) {
        Move(from, to);
        return;
    }

    Hanoi(num - 1, from, to, temp);
    Move(from, to);
    Hanoi(num - 1, temp, from, to);
}

void Move(char from, char to) {
    std::cout << from << "에서 " << to << "로 옮깁니다." << std::endl;
}

// 옮기는 원반의 번호 추가 - - - - - - - - - - - - - - - - - - - - - -
#include <iostream>

int UserInput();
void Hanoi(int num, char from, char temp, char to);
void Move(char from, char to, int disk);

int main() {
    int num{ UserInput() };
    Hanoi(num, 'A', 'B', 'C');
}

int UserInput() {
    int num{};
    std::cout << "원판의 개수 : ";
    std::cin >> num;
    return num;
}

void Hanoi(int num, char from, char temp, char to) {
    if (num == 1) {
        Move(from, to, num);
        return;
    }

    Hanoi(num - 1, from, to, temp);
    Move(from, to, num);
    Hanoi(num - 1, temp, from, to);
}

void Move(char from, char to, int disk) {
    std::cout << from << "에서 " << to << "로 원반 " << disk << "을 옮깁니다." << std::endl;
}

// 이동횟수 추가 - - - - - - - - - - - - - - - - - - - - - - - - - - -
#include <iostream>

int UserInput();
int Hanoi(int num, char from, char temp, char to, int count);
int Move(char from, char to, int disk, int count);

int main() {
    int num{ UserInput() }, count{};
    Hanoi(num, 'A', 'B', 'C', count);
}

int UserInput() {
    int num{};
    std::cout << "원판의 개수 : ";
    std::cin >> num;
    return num;
}

int Hanoi(int num, char from, char temp, char to, int count) {
    if (num == 1) {
        count = Move(from, to, num, count);
    }
    else {
        count = Hanoi(num - 1, from, to, temp, count);
        count = Move(from, to, num, count);
        count = Hanoi(num - 1, temp, from, to, count);
    }
    return count;
}

int Move(char from, char to, int disk, int count) {
    count++;
    std::cout << count << " : " << from << "에서 " << to << "로 원반 " << disk << "을 옮깁니다." << std::endl;
    return count;
}

// 게임으로 제작 - - - - - - - - - - - - - - - - - - - - - - - - - - -
#include <iostream>

void Print(int tower[][3]);
bool Move(int tower[][3], int from, int to);
bool CheckEnd(int tower[][3]);

int main() {
    int tower[3][3]{ { 1, }, { 2, }, { 3, } },
        from{}, to{};

    Print(tower);

    while (true) {
        if (CheckEnd(tower)) {
            std::cout << "완성되었습니다!" << std::endl;
            break;
        }

        std::cout << "어떻게 움직일까요? ";
        std::cin >> from >> to;

        if (Move(tower, from, to)) {
            std::cout << "움직일 수 없습니다." << std::endl;
            continue;
        }

        Print(tower);
    }
}

void Print(int tower[][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << tower[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool CheckEnd(int tower[][3]) {
    if (tower[0][2] == 1 &&
        tower[1][2] == 2 &&
        tower[2][2] == 3) {
        return true;
    }
    return false;
}

bool Move(int tower[][3], int from, int to) {
    if (tower[2][from - 1] == 0) { return true; }
    else if (tower[0][to - 1] != 0) { return true; }

    int fromDisk{}, toDisk{}, fromIndex{}, toIndex{};

    for (int i{}; i < 3; ++i) {
        if (tower[i][from - 1] != 0) {
            fromDisk = tower[i][from - 1];
            fromIndex = i;
            break;
        }
    }
    for (int i{}; i < 3; ++i) {
        if (tower[i][to - 1] != 0) {
            toDisk = tower[i][to - 1];
            toIndex = i;
            break;
        }
    }

    if (fromDisk > toDisk && toDisk != 0) { return true; }

    tower[fromIndex][from - 1] = 0;

    switch (toIndex)
    {
    case 0:
        tower[2][to - 1] = fromDisk;
        break;
    case 1:
        tower[0][to - 1] = fromDisk;
        break;
    case 2:
        tower[1][to - 1] = fromDisk;
        break;
    }

    return false;
}