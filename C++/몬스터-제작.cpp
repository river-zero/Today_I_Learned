#include <iostream>
#include <string>

enum MonsterType {
    Wolf, Demon, Slime
};

struct Monster {
    MonsterType type;
    std::string name;
    int hp;
};

void Print(Monster monster);
std::string TypeName(MonsterType type);

int main() {
    std::cout << "들판에 몬스터가 가득합니다." << std::endl;

    Monster sickWolf{ Wolf, "병든 늑대", 10 };
    Monster netherWolf{ Wolf, "황천 늑대", 1000 };
    Monster pitLord{ Demon, "구덩이 군주", 400 };

    Print(sickWolf);
    Print(netherWolf);
    Print(pitLord);
}

void Print(Monster monster) {
    std::string type = TypeName(monster.type);

    std::cout << "- " << monster.name
                      << "(" << type
                      << ", 체력 : " << monster.hp
                      << ")" << std::endl;
}

std::string TypeName(MonsterType type) {
    switch (type) {
    case Wolf:
        return "늑대족";
        break;
    case Demon:
        return "악마족";
        break;
    case Slime:
        return "슬라임족";
        break;
    defualt:
        return "불명";
    }
}