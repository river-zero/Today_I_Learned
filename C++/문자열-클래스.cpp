#include <iostream>

class String {
private:
	char* mString;
	int mLength;

public:
	String(const char* data) : mLength{}, mString{} {
		while (data[mLength] != '\0') {
			mLength++;
		}

		mString = new char[mLength + 1];

		for (int i{}; i <= mLength; i++) {
			mString[i] = data[i];
		}
	}

	~String() {
		delete[] mString;
	}

	void Print() const {
		std::cout << mString << std::endl;
	}
};

int main() {
	String s1{ "Hello World" };

	s1.Print();
}