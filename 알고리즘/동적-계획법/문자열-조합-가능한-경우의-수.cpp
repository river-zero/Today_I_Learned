/*------------------------------
    시간 복잡도는 O(n x m^2)
    공간 복잡도는 O(m^2)
------------------------------*/

#include <iostream>
#include <string> 
#include <vector> 
#include <map>

using gen_history = std::map<std::string, int>;

int HowManyGenerate(std::string target, const std::vector<std::string>& stringlist, gen_history& h) {
	if (h.count(target) == 1) {
		return h[target];
	}
	if (target == "") {
		return 1;
	}

	int count{};

	for (auto e : stringlist) {
		if (target.find(e) == 0) {
			const std::string subs = target.substr(e.length());
			count += HowManyGenerate(subs, stringlist, h);
		}
	}

	h[target] = count;
	return count;
}

int main() {
	gen_history h;

	std::cout << HowManyGenerate("abcdef", { "ab", "abc", "cd", "def", "abcd " }, h) << std::endl;
	std::cout << HowManyGenerate("hello", { "he", "l", "o", "ll" }, h) << std::endl;
	std::cout << HowManyGenerate("programmer", { "pro", "gram", "mer", "program", "er", "m" }, h) << std::endl;
}
