#include <iostream>
#include <vector>

class Array2D {
private:
	int row;
	int col;
	std::vector<std::vector<int>> array;

public:
	Array2D(int row, int col) : row{ row }, col{ col }, array(row, std::vector<int>(col, -1)) {}

	friend std::ostream& operator<<(std::ostream& os, const Array2D a);
};

std::ostream& operator<<(std::ostream& os, const Array2D a) {
	os << "{" << std::endl;
	for (int i{}; i < a.row; i++) {
		os << "{ ";
		for (int j{}; j < a.col; j++) {
			os << a.array[i][j];
			if (j < a.col - 1) {
				os << ", ";
			}
		}
		os << " }";
		if (i < a.row - 1) {
			os << ",";
		}
		os << std::endl;
	}
	os << "}" << std::endl;
	return os;
}

int main() {
	int m{};
	int n{};

	std::cout << "m : ";
	std::cin >> m;
	std::cout << "n : ";
	std::cin >> n;

	Array2D array(m, n);

	std::cout << array;
}