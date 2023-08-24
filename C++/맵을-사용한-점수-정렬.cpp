#include <iostream>
#include <map>
#include <string>

struct Student {
	int mNumber;
	int mScore;
	std::string mName;
};

int main() {
	/*std::map<int, Student> students = {
		{1, {1, 100, "Doggy"}},
		{2, {2, 50, "Kitty"}},
		{3, {3, 90, "Piggy"}},
		{4, {4, 20, "Bunny"}}
	};*/

	std::map<int, Student> students;

	students.insert({ 1, {1, 100, "Doggy"} });
	students.insert({ 2, {2, 50, "Kitty"} });
	students.insert({ 3, {3, 90, "Piggy"} });
	students.insert({ 4, {4, 20, "Bunny"} });

	students.insert(std::make_pair<int, Student>(5, { 5, 80, "Mansu" }));

	for (const auto& e : students) {
		std::cout << e.first << ", " 
			<< e.second.mName << ", " 
			<< e.second.mScore << std::endl;
	}
}