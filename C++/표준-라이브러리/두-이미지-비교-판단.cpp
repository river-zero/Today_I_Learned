#include <iostream>
#include <string>
#include <algorithm>

bool CheckImage(std::string s, std::string t) {
	if (s.size() != t.size()) {
		return 0;
	}

	std::sort(s.begin(), s.end());
	std::sort(t.begin(), t.end());
	return s == t;
}

int main() {
	std::string s{};
	std::string t{};

	std::cout << "first string : ";
	std::cin >> s;
	std::cout << "second string : ";
	std::cin >> t;

	std::cout << std::boolalpha << CheckImage(s, t);
}