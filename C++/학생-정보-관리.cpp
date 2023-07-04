#include <iostream>

using Comparison = bool (*)(int, int);

struct Student {
    int number;
    std::string name;
    int score;
};

enum {
    quit, print, sum, sort
};

int InputStudentNum();
void InputData(Student* student, int size);
void PrintData(Student* student, int size);
void Sort(Student* student, int size, Comparison compare, int Student::* member);
bool Ascending(int x, int y);
bool Dscending(int x, int y);
int Sum(Student* student, int size);

int main() {
    int studentNum = InputStudentNum();
    Student* studentArray{ new Student[studentNum]{} };

    if (studentArray) {
        InputData(studentArray, studentNum);
        std::cout << std::endl;
    }

    while (true) {
        std::cout << "0. 종료" << std::endl
                  << "1. 리스트 출력" << std::endl
                  << "2. 총점" << std::endl
                  << "3. 점수 내림차순 정렬" << std::endl;

        int choice{};
        std::cin >> choice;
       
        switch (choice) {
        case quit:
            delete[] studentArray;
            return 0;
        case print:
            Sort(studentArray, studentNum, Ascending, &Student::number);
            PrintData(studentArray, studentNum);
            break;
        case sum:
            std::cout <<"총점 : " << Sum(studentArray, studentNum) << std::endl << std::endl;
            break;
        case sort:
            Sort(studentArray, studentNum, Dscending, &Student::score);
            PrintData(studentArray, studentNum);
            break;
        default:
            std::cout << "다시 입력해주세요." << std::endl;
        }
    }
}

int InputStudentNum() {
    int num{};
    std::cout << "학생 수를 입력 : ";
    std::cin >> num;
    std::cout << std::endl;
    return num;
}

void InputData(Student* student, int size) {
    for (int i{}; i < size; i++) {
        std::cout << i + 1 << "번째 학생 번호 : ";
        std::cin >> student[i].number;
        std::cout << i + 1 << "번째 학생 이름 : ";
        std::cin >> student[i].name;
        std::cout << i + 1 << "번째 학생 점수 : ";
        std::cin >> student[i].score;
        std::cout << std::endl;
    }
}

void PrintData(Student* student, int size) {
    for (int i{}; i < size; i++) {
        std::cout << "[" << student[i].number << "] "
                  << student[i].name << ", "
                  << student[i].score << std::endl;
    }
    std::cout << std::endl;
}

void Sort(Student* student, int size, Comparison compare, int Student::* member) {
    for (int i{}; i < size; i++) {
        for (int j{ i + 1 }; j < size; j++) {
            if (compare(student[i].*member, student[j].*member)) {
                int tempNumber = student[i].number;
                student[i].number = student[j].number;
                student[j].number = tempNumber;
                std::string tempName = student[i].name;
                student[i].name = student[j].name;
                student[j].name = tempName;
                int tempScore = student[i].score;
                student[i].score = student[j].score;
                student[j].score = tempScore;
            }
        }
    }
}

bool Ascending(int x, int y) {
    return x >= y;
}

bool Dscending(int x, int y) {
    return x <= y;
}

int Sum(Student* student, int size) {
    int count{};
    for (int i{}; i < size; i++) {
        count += student[i].score;
    }
    return count;
}