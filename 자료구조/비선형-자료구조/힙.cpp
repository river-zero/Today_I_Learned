#include <iostream>
#include <vector>
#include <limits>

class Heap {
private:
	std::vector<int> mHeap;

public:
	void insert(int value) {
		mHeap.push_back(value);

		int i = static_cast<int>(mHeap.size() - 1);
		int half = (i - 1) / 2;

		while (i != 0 && value > mHeap[half]) {
			mHeap[i] = mHeap[half];
			mHeap[half] = value;
			i = half;

			half = (i - 1) / 2;
		}
	}

	void Print() {
		for (auto e : mHeap) {
			std::cout << e << " ";
		}
	}

	int Pop() {
		if (mHeap.size() == 0) {
			// INT_MAX, INT_MIN
			return std::numeric_limits<int>::min();
		}

		int value = mHeap.front();
		mHeap[0] = mHeap.back();
		mHeap.pop_back();

		int i = 0;
		while (i < mHeap.size()) {
			int bigChild = i * 2 + 1;
			if (bigChild >= mHeap.size()) {
				break;
			}

			if (bigChild + 1 < mHeap.size() && 
				mHeap[bigChild] < mHeap[bigChild + 1]) {
				bigChild++;
			}

			if (mHeap[i] >= mHeap[bigChild]) {
				break;
			}

			std::swap(mHeap[i], mHeap[bigChild]);
			i = bigChild;
		}

		return value;
	}
};

int main() {
	Heap h;

	h.insert(1);
	h.insert(2);
	h.insert(3);
	h.insert(4);
	h.insert(5);

	h.Print(); // 5 4 2 1 3
	std::cout << std::endl;

	std::cout << h.Pop() << std::endl; // 5
	h.Print(); // 4 3 2 1
	std::cout << std::endl;
	std::cout << h.Pop() << std::endl; // 4
	h.Print(); // 3 1 2
	std::cout << std::endl;
	std::cout << h.Pop() << std::endl; // 3
	h.Print(); // 2 1
	std::cout << std::endl;
	std::cout << h.Pop() << std::endl; // 2
	h.Print(); // 1
	std::cout << std::endl;
	std::cout << h.Pop() << std::endl; // 1
	std::cout << std::endl;
}