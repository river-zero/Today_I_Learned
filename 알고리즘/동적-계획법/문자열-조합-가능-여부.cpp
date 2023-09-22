/*------------------------------
    시간 복잡도는 O(n x m^2)
    공간 복잡도는 O(m^2)
------------------------------*/

#include <iostream>
#include <string>
#include <vector>
#include <map>

using gen_history = std::map<std::string, bool>;

bool CanGenerate(std::string target, const std::vector<std::string>& stringlist, gen_history& h) {
	if (h.count(target) == 1) {
		return h[target];
	}
	if (target.empty()) {
		return true;
	}

	for (auto e : stringlist) {
		if (target.find(e) == 0) {
			const std::string subs = target.substr(e.length()); 
			if (CanGenerate(subs, stringlist, h)) {
				h[target] = true;
				return h[target];
			}
		}
	}

	h[target] = false; 
	return h[target];
}

int main() {
	gen_history h;

	std::cout << std::boolalpha;
	std::cout << CanGenerate("abcdef", { "ab", "abc", "cd", "def", "abcd" }, h);
}