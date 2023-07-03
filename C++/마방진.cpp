 #include <iostream>

int main() {
    const int nums{ 5 };
    int magicSquare[nums][nums]{}, row{}, col{ nums / 2 }, keepRow{}, keepCol{};

    for (int i{ 1 }; i <= nums * nums; i++) {
        magicSquare[row][col] = i;

        keepRow = row--;
        keepCol = col++;

        if (row < 0) {
            row = nums - 1;
        }
        else if (col >= nums) {
            col = 0;
        }

       if (magicSquare[row][col] != 0) {
           row = ++keepRow;
           col = keepCol;
       }
 
    for  (int i{}; i < nums; i++) {
        for (int j{}; j < nums; j++) {
            std::cout << magicSquare[i][j] << "\t";
        }
        std::cout << std::endl; 
     }
}