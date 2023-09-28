/*------------------------------
    시간 복잡도는 O(n x m^2)
    공간 복잡도는 O(m)
------------------------------*/

#include <iostream>
#include <vector>
#include <string>

int HowManyGenerate(const std::string target, const std::vector<std::string>& stringlist) {
	std::vector<int> table(target.length() + 1, 0);

	table[0] = 1;

	for (unsigned int i = 0; i <= target.length(); i++) {
		if (table[i] > 0) {
			for (auto e : stringlist) {
				if (target.substr(i, e.length()) == e) {
					if (i + e.length() <= target.length()) {
						table[i + e.length()] += table[i];
					}
				}
			}
		}
	}

	return table[target.length()];
}

int main() {
	std::cout << HowManyGenerate("abcdef", { "ab", "abc", "cd", "def", "abcd" }) << std::endl;
	std::cout << HowManyGenerate("hello", { "a", "b", "c", "d" }) << std::endl;
	std::cout << HowManyGenerate("", { "a", "b", "c", "d" }) << std::endl;
	std::cout << HowManyGenerate("hello", { "he", "h", "e", "llo", "hell" }) << std::endl;
}