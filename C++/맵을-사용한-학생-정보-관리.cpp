#include <iostream>
#include <map>
#include <algorithm>
#include <numeric>

class Student {
public:
	int mNumber{};
	std::string mName{};
	int mScore{};
};

std::ostream& operator<<(std::ostream& os, const Student& s) {
	os << "[" << s.mNumber << "] "
		<< s.mName << " : "
		<< s.mScore << std::endl;
	return os;
}

// using Students = std::map<int, Student>;
// 위 별칭을 사용하면 아래 모든 std::map<int, Student>를 Students로 대체 가능

void AddStudent(std::map<int, Student>& m) {
	std::cout << "학생 정보 입력 (번호, 이름, 점수) : ";

	Student newStudent;
	if (std::cin >> newStudent.mNumber >> newStudent.mName >> newStudent.mScore) {
		auto result = m.insert({ newStudent.mNumber, newStudent });
		// auto는 원래 std::map<int, Student>::iterator
		// m.insert()는 std::pair<std::map<int, Student>::iterator, bool> 반환

		if (!result.second) { // bool에 성공 여부를 나타내는 값이 false인 경우
			std::cout << "중복된 학생 번호입니다." << std::endl;
			return;
		}
	} else {
		std::cout << "잘못된 입력입니다." << std::endl;
	}
}

void RemoveStudent(std::map<int, Student>& m) {
	std::cout << "삭제할 번호 : ";
	int number;
	if (std::cin >> number) {
		// 연관 컨테이너인 map은 전방 반복자가 없어 remove_if 불가능
		// 대신 훨씬 쉽게 erase(key)로 삭제 가능
		m.erase(number);
	} else {
		std::cout << "잘못된 입력입니다." << std::endl;
	}
}

void PrintStudents(const std::map<int, Student>& m) {
	for (const auto& e : m) {
		std::cout << e.second; // 연산자 오버로딩 작동
	}
}

void PrintScoreInfo(std::map<int, Student>& m) {
	if (m.empty()) {
		std::cout << "입력된 학생 정보가 없습니다." << std::endl;
		return;
	}

	int total{};
	total = std::accumulate(m.begin(), m.end(), 0, [](int accum, const auto& pair) {
		return accum += pair.second.mScore;
		});

	std::cout << "총점 : " << total
		<< ", 평균 : " << total / m.size()
		<< std::endl;
}

void PrintOverAverage(const std::map<int, Student>& m) {
	int average{};
	average = std::accumulate(m.begin(), m.end(), 0, [](int accum, const auto& pair) {
		return accum += pair.second.mScore;
		});
	average /= m.size();

	std::for_each(m.begin(), m.end(), [&](const auto& pair) {
		if (pair.second.mScore >= average) {
			std::cout << pair.second << std::endl;
		}
		});
}

int main() {
	std::map<int, Student> students{
		{1, { 1, "Kim", 80 }},
		{2, { 2, "Lee", 20 }},
		{3, { 3, "Park", 40 }},
		{4, { 4, "Choi", 30 }}
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