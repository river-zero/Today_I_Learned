#include <iostream>

const int NAME_LENGTH = 10;

struct Monster {
	char name[NAME_LENGTH]{};
	int hp{};

	Monster* pNext{};
	Monster* pPrev{};
};

struct MonsterList {
	Monster* pHead{};
	Monster* pTail{};
};

Monster* CreateMonster(MonsterList& list, const char* name, const int hp) {
	Monster* pElement = new Monster;

	strcpy_s(pElement->name, NAME_LENGTH, name);
	pElement->hp = hp;

	if (!list.pTail) {
		list.pHead = pElement;
	}
	else {
		pElement->pPrev = list.pTail;
		list.pTail->pNext = pElement;
	}

	list.pTail = pElement;

	return pElement;
}

int GetMonsterCount(const MonsterList& list) {
	Monster* pElement = list.pHead;

	int count{};

	while (pElement) {
		pElement = pElement->pNext;
		count++;
	}

	return count;
}

void PrintMonsters(const MonsterList& list) {
	Monster* pElement = list.pHead;

	while (pElement) {
		std::cout << pElement->name << ", " << pElement->hp << std::endl;
		pElement = pElement->pNext;
	}
}

void PrintMonstersR(Monster* pMonster) {
	if (!pMonster) {
		return;
	}

	std::cout << pMonster->name << ", " << pMonster->hp << std::endl;
	PrintMonstersR(pMonster->pNext);
}

Monster* FindMonster(const MonsterList& list, const char* name) {
	Monster* pElement = list.pHead;

	while (pElement) {
		if (strcmp(pElement->name, name) == 0) {
			return pElement;
		}

		pElement = pElement->pNext;
	}

	return nullptr;
}

void DeleteAll(MonsterList& list) {
	Monster* pElement = list.pHead;
	Monster* pNext{};

	while (pElement) {
		pNext = pElement->pNext;
		delete pElement;
		pElement = pNext;
	}

	list.pHead = nullptr;
	list.pTail = nullptr;
}

bool DeleteMonster(MonsterList& list, const char* name) {
	Monster* pElement = list.pHead;

	while (pElement) {
		if (strcmp(pElement->name, name) == 0) {
			if (pElement == list.pHead) {
				list.pHead = pElement->pNext;
			}
			else {
				pElement->pPrev->pNext = pElement->pNext;
			}

			if (pElement == list.pTail) {
				list.pTail = pElement->pPrev;
			}
			else {
				pElement->pNext->pPrev = pElement->pPrev;
			}

			delete pElement;

			return true;
		}

		pElement = pElement->pNext;
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

	Monster* pResult = FindMonster(myList, "Wolf");
	if (pResult) {
		std::cout << pResult->name << " Found!" << std::endl;
	}
	else {
		std::cout << "Not Found!" << std::endl;
	}

	DeleteMonster(myList, "Wolf");
	PrintMonsters(myList);
	DeleteMonster(myList, "Demon");
	PrintMonsters(myList);
	DeleteMonster(myList, "Slime");
	PrintMonsters(myList);

	DeleteAll(myList);
	std::cout << GetMonsterCount(myList) << std::endl;
}