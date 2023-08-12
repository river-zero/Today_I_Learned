#include <iostream>

class String {
private:
    char* mString;
    int mLength;

public:
    // 기본 생성자로 빈 문자열 생성
    String() : mLength{}, mString{ new char[1] } {
        mString[0] = '\0';
    }

    // 입력 크기만큼 공백 문자열 생성
    String(int size) : mLength{ size }, mString{ new char[size + 1] } {
        for (int i{}; i < size; i++) {
            mString[i] = ' ';
        }

        mString[size] = '\0';
    }

    // 문자열 리터럴 입력 시 문자열 생성
    String(const char* data) : mLength{}, mString{} {
        while (data[mLength] != '\0') {
            mLength++;
        }

        mString = new char[mLength + 1];

        for (int i{}; i <= mLength; i++) {
            mString[i] = data[i];
        }
    }

    // 다른 문자열 복사
    String(const String& string) : mLength{ string.mLength }, mString{ new char[string.mLength + 1] } {
        for (int i{}; i <= mLength; i++) {
            mString[i] = string.mString[i];
        }
    }

    // + 연산자 오버로딩으로 두 문자열 이어붙이기
    String operator+(const String& string) const {
        int totalLength = mLength + string.mLength;
        char* totalString = new char[totalLength + 1];

        for (int i{}; i < mLength; i++) {
            totalString[i] = mString[i];
        }

        for (int i{}; i < totalLength - mLength; i++) {
            totalString[mLength + i] = string.mString[i];
        }

        totalString[totalLength] = '\0';

        String result(totalString);
        delete[] totalString;

        return result;
    }

    // += 연산자 오버로딩으로 두 문자열 이어붙이기
    String& operator+=(const String& string) {
        *this = *this + string;
        return *this;
    }

    // [] 연산자 오버로딩으로 배열 표기 (출력만)
    const char& operator[](int index) const {
        // 방어 코드
        if (index < 0) {
            index = 0;
        } else if (index >= mLength) {
            index = mLength - 1;
        }

        return mString[index];
    }

    // [] 연산자 오버로딩으로 배열 표기 (입력)
    char& operator[](int index) {
        if (index < 0) {
            index = 0;
        } else if (index >= mLength) {
            index = mLength - 1;
        }

        return mString[index];
    }

    // = 연산자 오버로딩으로 대입
    String& operator=(const String& string) {
        if (this == &string) {
            return *this;
        }

        delete[] mString;

        mLength = string.mLength;
        mString = new char[mLength + 1];

        for (int i{}; i <= mLength; i++) {
            mString[i] = string.mString[i];
        }

        return *this;
    }

    ~String() {
        delete[] mString;
    }

    void Print() const {
        std::cout << mString << std::endl;
    }
};

int main() {
    String empty;
    std::cout << "empty 문자열\t(빈 문자열)\t";
    empty.Print();

    String sized(10);
    std::cout << "sized 문자열\t(공백 10칸)\t";
    sized.Print();

    String s1("hello");
    std::cout << "s1 문자열\t(hello)\t\t";
    s1.Print();

    String s2(s1);
    std::cout << "s2 문자열\t(s1 복사)\t";
    s2.Print();

    String s3 = s1 + s2;
    std::cout << "s3 문자열\t(s1 + s2)\t";
    s3.Print();

    String s4;
    s4 += s3;
    std::cout << "s4 문자열\t(s4 += s3)\t";
    s4.Print();

    std::cout << "s4[0]: " << s4[0] << ", s4[1]: " << s4[1] << std::endl;
    std::cout << "인덱스 범위 초과: " << s4[99] << std::endl;
    std::cout << "인덱스 범위 미만: " << s4[-10] << std::endl;

    s4[0] = 'H';
    std::cout << "s4 문자열\t(s4[0] = 'H')\t";
    s4.Print();

    empty = s4;
    std::cout << "empty 문자열\t(empty = s4)\t";
    empty.Print();

    s4 = s4;
    std::cout << "s4 문자열\t(s4 = s4)\t";
    s4.Print();
}