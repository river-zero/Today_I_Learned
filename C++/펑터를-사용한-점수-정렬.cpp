#include <iostream>
#include <vector>
#include <algorithm>

struct Student {
	int mNumber;
	int mScore;
	std::string mName;
};

class Ascending {
public:
	bool operator()(const Student& s1, const Student& s2) const {
		return s1.mScore < s2.mScore;
	}
};

class Descending {
public:
	bool operator()(const Student& s1, const Student& s2) const {
		return s1.mScore > s2.mScore;
	}
};

int main() {
	std::vector<Student> students = {
		{1, 100, "Doggy"},
		{2, 50, "Kitty"},
		{3, 90, "Piggy"},
		{4, 20, "Bunny"}
	};

	std::sort(students.begin(), students.end(), Ascending());

	std::cout << "--- 오름차순 ---" << std::endl;
	for (const auto& student : students) {
		std::cout << "[" << student.mNumber << "] "
			<< student.mName << ", "
			<< student.mScore << std::endl;
	}

	std::sort(students.begin(), students.end(), Descending());

	std::cout << "--- 내림차순 ---" << std::endl;
	for (const auto& student : students) {
		std::cout << "[" << student.mNumber << "] " 
			<< student.mName << ", " 
			<< student.mScore << std::endl;
	}
}