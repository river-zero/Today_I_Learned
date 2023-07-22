#include <iostream>
#include <string>

class Student {
private:
	std::string name;
	int number;
	double score;

public:
	Student() : name{}, number{}, score{} {
		std::cout << "이름 : ";
		std::cin >> name;

		std::cout << "번호 : ";
		std::cin >> number;

		std::cout << "점수 : ";
		std::cin >> score;
		std::cout << std::endl;
	}

	double GetScore() const {
		return score;
	}

	void Print() const {
		std::cout << "[" << number << "] " << name << ", " << score << std::endl;
	}
};

class Students {
private:
	int studentNum{};
	Student* students{};

public:
	Students() {
		std::cout << "학생 수 입력 : ";
		std::cin >> studentNum;

		students = new Student[studentNum];
	}

	~Students() {
		delete[] students;
	}

	void PrintAll() const {
		std::cout << "----- 학생들 정보 -----" << std::endl;
		for (int i{}; i < studentNum; i++) {
			students[i].Print();
		}
	}

	void SortScore() {
		for (int i{}; i < studentNum - 1; i++) {
			for (int j{}; j < studentNum - i - 1; j++) {
				if (students[j].GetScore() > students[j + 1].GetScore()) {
					Student temp = students[j];
					students[j] = students[j + 1];
					students[j + 1] = temp;
				}
			}
		}
	}
};

int main() {
	Students students;
	students.PrintAll();
	students.SortScore();
	students.PrintAll();
}