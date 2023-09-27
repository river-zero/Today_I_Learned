/*------------------------------
    시간 복잡도는 O(n x m^2)
    공간 복잡도는 O(m)
------------------------------*/

#include <iostream>
#include <vector>
#include <string>

bool CanGenerate(const std::string target, const std::vector<std::string>& stringlist) {
	std::vector<bool> table(target.size() + 1, false);

	table[0] = true;

	for (unsigned int i = 0; i <= target.size(); i++) {
		if (table[i] == true) {
			for (auto e : stringlist) {
				if (target.substr(i, e.size()) == e) {
					if (i + e.size() <= target.size()) {
						table[i + e.size()] = true;
					}
				}
			}
		}
	}

	return table[target.size()];
}

int main() {
	std::cout << std::boolalpha;
	std::cout << CanGenerate("abcdef", { "ab", "abc", "cd", "def", "abcd" }) << std::endl;
	std::cout << CanGenerate("", { "a", "b", "c", "d" }) << std::endl;
	std::cout << CanGenerate("abcdef", { "ab", "abc", "de", "abcd" }) << std::endl;
}