#include <iostream>

const int NAME_LENGTH = 10;

struct Monster {
	char name[NAME_LENGTH]{};
	int hp{};

	Monster* pNext{};
};

struct MonsterList {
	Monster* pHead{};
	Monster* pTail{};
};

Monster* CreateMonster(MonsterList& list, const char* name, const int hp) {
	Monster* p = new Monster;

	strcpy_s(p->name, NAME_LENGTH, name);
	p->hp = hp;

	if (list.pTail == nullptr) {
		list.pHead = p;
	}
	else {
		list.pTail->pNext = p;
	}

	list.pTail = p;

	return p;
}

int GetMonsterCount(const MonsterList& list) {
	Monster* p = list.pHead;

	int count{};

	while (p != nullptr) {
		p = p->pNext;
		count++;
	}

	return count;
}

void PrintMonsters(const MonsterList& list) {
	Monster* p = list.pHead;

	while (p) {
		std::cout << p->name << ", " << p->hp << std::endl;
		p = p->pNext;
	}
}

void PrintMonstersR(Monster* pMonster) {
	if (pMonster == nullptr) {
		return;
	}

	std::cout << pMonster->name << ", " << pMonster->hp << std::endl;
	PrintMonstersR(pMonster->pNext);
}

Monster* FindMonster(const MonsterList& list, const char* name) {
	Monster* p = list.pHead;

	while (p) {
		if (strcmp(p->name, name) == 0) {
			return p;
		}

		p = p->pNext;
	}

	return nullptr;
}

void DeleteAll(MonsterList& list) {
	Monster* p = list.pHead;
	Monster* pNext{};

	while (p) {
		pNext = p->pNext;
		delete p;
		p = pNext;
	}

	list.pHead = nullptr;
	list.pTail = nullptr;
}

bool DeleteMonster(MonsterList& list, const char* name) {
	Monster* p = list.pHead;
	Monster* prev{};

	while (p) {
		if (strcmp(p->name, name) == 0) {
			if (p == list.pHead) {
				list.pHead = p->pNext;
			}
			else {
				prev->pNext = p->pNext;
			}

			if (p == list.pTail) {
				list.pTail = prev;
			}

			delete p;

			return true;
		}

		prev = p;
		p = p->pNext;
	}

	return false;
}

int main() {
	MonsterList myList;

	CreateMonster(myList, "Demon", 100);
	CreateMonster(myList, "Wolf", 50);
	CreateMonster(myList, "Slime", 10);

	PrintMonsters(myList);
	std::cout << GetMonsterCount(myList) << std::endl;

	Monster* pResult = FindMonster(myList, "Bear");
	if (pResult) {
		std::cout << pResult->name << " Found!" << std::endl;
	}
	else {
		std::cout << "Not Found!" << std::endl;
	}

	bool isDeleted = DeleteMonster(myList, "Wolf");
	if (isDeleted) {
		std::cout << "Monster deleted!" << std::endl;
	}
	else {
		std::cout << "Monster not found!" << std::endl;
	}
	PrintMonsters(myList);

	DeleteAll(myList);
	std::cout << GetMonsterCount(myList) << std::endl;
}