/*--------------------------
	SimpleData.txt

	--- MONSTER DATA ---
	SLIME,1,1,1
	WOLF,5,5,5
	DEMON,10,10,10
--------------------------*/

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

class Monster {
private:
    std::string mName;
    int mLevel;
    int mHP;
    int mMP;

public:
    Monster() : mName(), mLevel(), mHP(), mMP() {}
    Monster(std::string name, int level, int hp, int mp)
        : mName(name), mLevel(level), mHP(hp), mMP(mp) {
    }

    friend std::istream& operator>>(std::istream& is, Monster& m) {
        std::string line;

        try {
            std::getline(is, line, ',');
            m.mName = line;
            std::getline(is, line, ',');
            m.mLevel = std::stoi(line);
            std::getline(is, line, ',');
            m.mHP = std::stoi(line);
            std::getline(is, line);
            m.mMP = std::stoi(line);
        } catch (std::exception& e) {
            std::cerr << "operator input error occurred." << std::endl;
        }

        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Monster& m) {
        try {
            os << m.mName << "," << m.mLevel << "," << m.mHP << "," << m.mMP;
        } catch (std::exception& e) {
            std::cerr << "operator output error occurred." << std::endl;
        }

        return os;
    }
};

bool LoadFile(const char* filename, std::vector<Monster>& monsters) {
    std::ifstream ifs;
    ifs.exceptions(std::ifstream::badbit);

    try {
        ifs.open(filename);

        std::string line;
        std::vector<std::string> data;

        getline(ifs, line); // 헤더

        while (!ifs.eof()) {
            if (ifs.peek() == EOF) {
                break;
            }

            Monster m;
            ifs >> m;
            monsters.push_back(m);
        }

        ifs.close();
    } catch (const std::ifstream::failure& e) {
        std::cerr << std::endl << e.code() << " ... " << e.what() << std::endl;
        ifs.close();
        return false;
    }

    return true;
}

bool SaveFile(const char* filename, const std::vector<Monster>& monsters) {
    std::ofstream ofs;
    ofs.exceptions(std::ofstream::badbit);

    try {
        ofs.open(filename);

        ofs << "--- MONSTER DATA ---" << std::endl;

        for (const auto& m : monsters) {
            ofs << m << std::endl;
        }

        ofs.close();
    } catch (const std::ofstream::failure& e) {
        std::cerr << std::endl << e.code() << " ... " << e.what() << std::endl;
        ofs.close();
        return false;
    }

    return true;
}

int main() {
    std::vector<Monster> monsters;

    if (LoadFile("Data/SimpleData.txt", monsters)) {
        for (const auto& e : monsters) {
            std::cout << e << std::endl;
        }
    }

    monsters.push_back(Monster("ORK", 15, 15, 15));

    if (SaveFile("Data/SimpleData_copy.txt", monsters)) {
        std::cout << "New monster added." << std::endl;
    }
}