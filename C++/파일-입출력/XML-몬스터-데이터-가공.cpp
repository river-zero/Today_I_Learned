/*-------------------------------------------------------------
    monsters.xml

    <?xml version="1.0" encoding="EUC-KR"?>
    <monsters>
        <monster name="슬라임">
                <status level="1" hp="1" mp="1"/>
                <items>
                        <item name="끈적한 젤리" gold="1"/>
                </items>
        </monster>
        <monster name="늑대인간">
                <status level="5" hp="5" mp="5"/>
                <items>
                        <item name="발톱" gold="2"/>
                        <item name="늑대가죽" gold="5"/>
                </items>
        </monster>
        <monster name="악마">
                <status level="10" hp="10" mp="10"/>
                <items>
                        <item name="날개" gold="10"/>
                        <item name="손톱" gold="5"/>
                </items>
        </monster>
    </monsters>

    https://github.com/leethomason/tinyxml2/
-------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <vector>
#include "tinyxml2.h"

struct Status {
	int mLevel{};
	int mHP{};
	int mMP{};
};

struct Item {
	std::string mName{};
	int mGold{};
};

class Monster2 {
private:
	std::string mName{};
	Status mStatus{};
	std::vector<Item> mDropItems{};

public:
	void SetName(std::string name) { mName = name; }
	void SetStatus(const Status& status) { mStatus = status; }
	void AddDropItem(const Item& item) { mDropItems.push_back(item); }

	std::string GetName() const { return mName; }
	// Status GetStatus() const { return mStatus; }
	Status& GetStatus() { return mStatus; }
	std::vector<Item>& GetDropItems() { return mDropItems; }
	// std::vector<Item> GetDropItems() const { return mDropItems; }
};

void SaveToXML(std::string path, std::vector<Monster2>& monsters) {
	using namespace tinyxml2; // only here
	XMLDocument doc;
	
	XMLDeclaration* dec1 = doc.NewDeclaration(R"(xml version="1.0 encoding="EUC-KR")");
	doc.LinkEndChild(dec1);

	XMLElement* root = doc.NewElement("monsters");
	doc.LinkEndChild(root);

	for (auto& monster : monsters) {
		auto monElement = doc.NewElement("monster");
		monElement->SetAttribute("name", monster.GetName().c_str());
		
		auto statusElement = doc.NewElement("status");
		statusElement->SetAttribute("level", monster.GetStatus().mLevel);
		statusElement->SetAttribute("hp", monster.GetStatus().mHP);
		statusElement->SetAttribute("mp", monster.GetStatus().mMP);
		monElement->LinkEndChild(statusElement);

		auto itemsElement = doc.NewElement("items");
		for (auto& item : monster.GetDropItems()) {
			auto itemElement = doc.NewElement("item");
			itemElement->SetAttribute("name", item.mName.c_str());
			itemElement->SetAttribute("gold", item.mGold);
			itemsElement->LinkEndChild(itemElement);
		}
		monElement->LinkEndChild(itemsElement);

		root->LinkEndChild(monElement);
	}

	doc.SaveFile(path.c_str());
}

void LoadFromXML(std::string path, std::vector<Monster2>& monsters) {
	using namespace tinyxml2;
	XMLDocument doc;

	doc.LoadFile(path.c_str());

	auto root = doc.FirstChildElement("monsters");
	for (auto monElement = root->FirstChildElement("monster"); 
		monElement != nullptr;
		monElement = monElement->NextSiblingElement()) 
	{
		Monster2 monster;
		monster.SetName(monElement->Attribute("name"));

		auto statusElement = monElement->FirstChildElement("status");
		Status status;
		status.mLevel = statusElement->IntAttribute("level");
		status.mHP = statusElement->IntAttribute("hp");
		status.mMP = statusElement->IntAttribute("mp");
		monster.SetStatus(status);

		auto itemsElement = monElement->FirstChildElement("items");
		for (auto itemElement = itemsElement->FirstChildElement();
			itemElement;
			itemElement = itemElement->NextSiblingElement()) 
		{
			Item item;
			item.mName = itemElement->Attribute("name");
			item.mGold = itemElement->IntAttribute("gold");
			monster.AddDropItem(item);
		}

		monsters.push_back(monster);
	}
}

int main() {
	std::vector<Monster2> monsters;

	Monster2 m;
	m.SetName("슬라임");
	m.SetStatus({ 1,1,1 });
	m.AddDropItem({ "끈적한 젤리", 1 });
	monsters.push_back(m);

	m.GetDropItems().clear();
	m.SetName("늑대인간");
	m.SetStatus({ 5,5,5 });
	m.AddDropItem({ "발톱", 2 });
	m.AddDropItem({ "늑대가죽", 5 });
	monsters.push_back(m);

	m.GetDropItems().clear();
	m.SetName("악마");
	m.SetStatus({ 10,10,10 });
	m.AddDropItem({ "날개", 10 });
	m.AddDropItem({ "손톱", 5 });
	monsters.push_back(m);

	SaveToXML("Data/monsters.xml", monsters);
	monsters.clear();
	LoadFromXML("Data/monsters.xml", monsters);

	for (auto& monster : monsters) {
        std::cout << "Monster Name: " << monster.GetName() << std::endl
                  << "Status - Level: " << monster.GetStatus().mLevel
                  << ", HP: " << monster.GetStatus().mHP
                  << ", MP: " << monster.GetStatus().mMP << std::endl
                  << "Drop Items:" << std::endl;

		for (auto& item : monster.GetDropItems()) {
			std::cout << "  Item Name: " << item.mName
                      << ", Gold: " << item.mGold << std::endl;
		}
		std::cout << std::endl;
	}
}