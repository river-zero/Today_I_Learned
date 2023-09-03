#include <iostream>
#include <vector>
#include <algorithm>

struct Student {
	int mNumber;
	int mScore;
	std::string mName;
};

int main() {
	std::vector<Student> students = {
		{1, 100, "Doggy"},
		{2, 50, "Kitty"},
		{3, 90, "Piggy"},
		{4, 20, "Bunny"}
	};

	std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
		return a.mScore < b.mScore; 
	});

	std::cout << "--- 오름차순 ---" << std::endl;
	for (const auto& student : students) {
		std::cout << "[" << student.mNumber << "] " 
			<< student.mName << ", " 
			<< student.mScore << std::endl;
	}

	std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
		return a.mScore > b.mScore; 
	});

	std::cout << "--- 내림차순 ---" << std::endl;
	for (const auto& student : students) {
		std::cout << "[" << student.mNumber << "] " 
			<< student.mName << ", " 
			<< student.mScore << std::endl;
	}
}