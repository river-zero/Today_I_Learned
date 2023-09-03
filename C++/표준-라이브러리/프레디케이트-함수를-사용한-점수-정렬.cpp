#include <iostream>
#include <vector>
#include <algorithm>

class Student {
public:
	int mNumber;
	int mScore;
	std::string mName;

public:
	bool operator<(const Student& another) const {
		return mScore > another.mScore; // 내림차순
	}
};

std::ostream& operator<<(std::ostream& os, const Student& student) {
	os << student.mScore << " : "
		<< student.mName << ", " 
		<< student.mNumber << std::endl;
	return os;
}

int main() {
	std::vector<Student> students = {
		{1, 100, "Doggy"},
		{2, 50, "Kitty"},
		{3, 90, "Piggy"},
		{4, 20, "Bunny"}
	};

	std::sort(students.begin(), students.end());

	for (const auto& student : students) {
		std::cout << student << std::endl;
	}
}