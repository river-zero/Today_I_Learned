#include <iostream>
#include <string>
#include <map>

int main() {
	std::map<char, int> count;
	int maxCount{};
	char maxAlpha{};

	std::string s;
	std::cout << "input string : ";
	std::cin >> s;

	for (char c : s) {
		if (std::isalpha(c)) {
			count[c]++;
		}
	}

	for (const auto& e : count) {
		if (e.second > maxCount) {
			maxAlpha = e.first;
			maxCount = e.second;
		}
	}

	if (maxAlpha != '\0') {
		std::cout << maxAlpha << std::endl;
	} else {
		std::cout << "not found." << std::endl;
	}
}