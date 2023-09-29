/*--------------------------
    시간 복잡도는 O(n^m)
    공간 복잡도는 O(n^m)
--------------------------*/

#include <iostream>
#include <vector>
#include <string>
#include <list>

using string_list = std::list<std::string>;
using result = std::list<string_list>;

result AllGenerate(const std::string target, const string_list& stringlist) {
	std::vector<result> table(target.length() + 1);

	table[0] = result{ {} };

	for (unsigned int i = 0; i <= target.length(); i++) {
		for (auto e : stringlist) {
			if (target.substr(i, e.length()) == e) {
				if (i + e.length() <= target.length()) {
					if (i + e.length() <= target.length()) {
						for (auto f : table[i]) {
							f.push_back(e);
							table[i + e.length()].push_back(f);
						}
					}
				}
			}
		}
	}

	return table[target.length()];
}

void Print(const result& r) {
	std::cout << "{" << std::endl;
	for (auto i = r.begin(); i != r.end(); i++) {
		std::cout << "    { ";
		for (auto j = i->begin(); j != i->end(); j++) {
			std::cout << *j;
			if (std::next(j) != i->end()) {
				std::cout << ", ";
			}
		}
		std::cout << " }";
		if (std::next(i) != r.end()) {
			std::cout << ",";
		}
		std::cout << std::endl;
	}
	std::cout << "}" << std::endl;
}

int main() {
	Print(AllGenerate("abcdef", { "ab", "abc", "cd", "def", "abcd" }));
	Print(AllGenerate("hello", { "a", "b", "c", "d" }));
	Print(AllGenerate("", { "a", "b", "c", "d" }));
	Print(AllGenerate("hello", { "he", "h", "e", "llo", "hell" }));
}