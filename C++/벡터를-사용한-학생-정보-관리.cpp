#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

class Student {
public:
	int mNumber{};
	std::string mName{};
	int mScore{};

public:
	void Print() const {
		std::cout << "[" << mNumber << "] "
			<< mName << " : "
			<< mScore << std::endl;
	}
};

void AddStudent(std::vector<Student>& v) {
	std::cout << "학생 정보 입력 (번호, 이름, 점수) : ";

	Student newStudent;
	if (std::cin >> newStudent.mNumber >> newStudent.mName >> newStudent.mScore) {
		/*for (const auto& e : v) {
			if (e.mNumber == newStudent.mNumber) {
				std::cout << "중복된 학생 번호입니다." << std::endl;
				return;
			}
		}*/
		auto itr = std::find_if(v.begin(), v.end(), [&](const auto& e) {
			return e.mNumber == newStudent.mNumber;
		});
		if (itr != v.end()) { // 값을 찾지 못하면 v.end()를 반환하기 때문
			std::cout << "중복된 학생 번호입니다." << std::endl;
			return;
		}

		v.push_back(newStudent);
	} else {
		std::cout << "잘못된 입력입니다." << std::endl;
	}
}

void RemoveStudent(std::vector<Student>& v) {
	std::cout << "삭제할 번호 : ";
	int number;
	if (std::cin >> number) {
		/*for (auto itr = v.begin(); itr != v.end(); itr++) {
			if (itr->mNumber == number) {
				v.erase(itr);
				return;
			}
		}*/
		v.erase(std::remove_if(v.begin(), v.end(), [&](auto& e) {
			return e.mNumber == number;
		}), v.end());
		// std::remove_if 함수로 원소를 끝으로 이동
		// 해당 부분부터 v.end()까지 erase 함수로 삭제
		// 이를 erase-remove idiom이라고 부름
	} else {
		std::cout << "잘못된 입력입니다." << std::endl;
	}
}

void PrintStudents(const std::vector<Student>& v) {
	/*for (const auto& e : v) {
		e.Print();
	}*/
	std::for_each(v.begin(), v.end(), [](const auto& e) {
		e.Print();
	});
}

void PrintScoreInfo(std::vector<Student>& v) {
	if (v.empty()) {
		std::cout << "입력된 학생 정보가 없습니다." << std::endl;
		return;
	}

	int total{};
	
	/*for (const auto& e : v) {
		total += e.mScore;
	}*/
	total = std::accumulate(v.begin(), v.end(), 0, [](int accum, const auto& e) {
		return accum += e.mScore;
	});
	// (시작, 끝, 초기값, 누적 작업)

	std::cout << "총점 : " << total
		<< ", 평균 : " << total / v.size() 
		<< std::endl;
}

void PrintOverAverage(const std::vector<Student>& v) {
	int average{};
	for (const auto& e : v) {
		average += e.mScore;
	}
	average /= static_cast<int>(v.size());

	/*for (const auto& e : v) {
		if (e.mScore >= average) {
			e.Print();
		}
	}*/
	std::for_each(v.begin(), v.end(), [&](const auto& e) {
		if (e.mScore >= average) {
			e.Print();
		}
	});
}

int main() {
	std::vector<Student> students{
		{ 1, "Kim", 80 },
		{ 2, "Lee", 20 },
		{ 3, "Park", 40 },
		{ 4, "Choi", 30 }
	};

	bool isQuit{ false };

	while (!isQuit) {
		std::cout << "1. 학생 추가" << std::endl
			<< "2. 학생 제거(번호)" << std::endl
			<< "3. 전체 학생 출력" << std::endl
			<< "4. 총점 및 평균 출력" << std::endl
			<< "5. 평균 이상의 학생 목록" << std::endl
			<< "6. 종료" << std::endl;

		std::cout << "> ";
		int command{};
		std::cin >> command;

		switch (command) {
		case 1:
			AddStudent(students);
			break;
		case 2:
			RemoveStudent(students);
			break;
		case 3:
			PrintStudents(students);
			break;
		case 4:
			PrintScoreInfo(students);
			break;
		case 5:
			PrintOverAverage(students);
			break;
		case 6:
			isQuit = true;
			break;
		default:
			std::cerr << "잘못된 명령입니다." << std::endl;
		}
	}
}