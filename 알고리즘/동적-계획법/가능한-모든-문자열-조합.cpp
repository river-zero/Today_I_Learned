/*--------------------------
    시간 복잡도는 O(n^m)
    공간 복잡도는 O(m^2)
--------------------------*/

#include <iostream>
#include <string>
#include <list>
#include <vector> 
#include <map>

using result = std::list<std::list<std::string>>;
using gen_history = std::map<std::string, result>;

result AllCombination(std::string target, const std::vector<std::string>& stringlist, gen_history& h) {
	if (h.count(target) == 1) {
		return h[target];
	}
	if (target == "") {
		return result{ {} };
	}

	result r;

	for (auto e : stringlist) {
		if (target.find(e) == 0) {
			const std::string subs = target.substr(e.length());
			auto ret = AllCombination(subs, stringlist, h);

			for (auto f : ret) {
				f.push_front(e);
				r.push_front(f);
			}
		}
	}

	h[target] = r;
	return r;
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
	gen_history h;

	Print(AllCombination("hello", { "he", "h", "e", "llo", "hell" }, h));
	Print(AllCombination("abcdef", { "ab", "abc", "cd", "def", "abcd " }, h));
	Print(AllCombination("programmer", { "pro", "gram", "mer", "program", "er", "m" }, h));
	Print(AllCombination("impossible", { "i", "p", "si", "ble" }, h));
}