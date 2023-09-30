#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<string> OptimizeCombination(string target, const vector<string>& stringlist) {
    vector<vector<string>> table(target.size() + 1);
    vector<bool> canMake(target.size() + 1, false);
    canMake[0] = true;

    for (int i = 0; i <= target.size(); i++) {
        if (canMake[i]) {
            for (const auto& word : stringlist) {
                if (i + word.size() > target.size()) continue;
                if (target.substr(i, word.size()) != word) continue;

                if (!canMake[i + word.size()] || table[i + word.size()].size() > 1 + table[i].size()) {
                    canMake[i + word.size()] = true;
                    table[i + word.size()] = table[i];
                    table[i + word.size()].push_back(word);
                }
            }
        }
    }

    return table[target.size()];
}

void Print(const vector<string>& r) {
    cout << "{ ";
    for (auto i = r.begin(); i != r.end(); i++) {
        cout << *i;
        if (next(i) != r.end()) {
            cout << ", ";
        }
    }
    cout << " }" << endl;
}

int main() {
    Print(OptimizeCombination("hello", { "he", "h", "e", "llo", "hell" }));
    Print(OptimizeCombination("abcdef", { "ab", "abc", "cd", "def", "abcd" }));
    Print(OptimizeCombination("programmer", { "pro", "gram", "mer", "program", "er", "m" }));
    Print(OptimizeCombination("impossible", { "i", "p", "si", "ble" }));
}