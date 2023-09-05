/*--------------------------------------------------------------------
    monsters.json

    {
        "monsters": [
            {
                "name": "슬라임",
                "status": {
                    "level": 1,
                    "hp": 1,
                    "mp": 1
                },
                "items": [
                    {
                        "name": "끈적한 젤리",
                        "gold": 1
                    }
                ]
            },
            {
                "name": "늑대인간",
                "status": {
                    "level": 5,
                    "hp": 5,
                    "mp": 5
                },
                "items": [
                    {
                        "name": "발톱",
                        "gold": 2
                    },
                    {
                        "name": "늑대가죽",
                        "gold": 5
                    }
                ]
            },
            {
                "name": "악마",
                "status": {
                    "level": 10,
                    "hp": 10,
                    "mp": 10
                },
                "items": [
                    {
                        "name": "날개",
                        "gold": 10
                    },
                    {
                        "name": "손톱",
                        "gold": 5
                    }
                ]
            }
        ]
    }

    Visual Studio 프로젝트 > NuGet 패키지 관리 > tencent.rapidjson
--------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#pragma warning(push) // 경고 무시
#pragma warning(disable : 26451 26495)
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#pragma warning(pop)

using namespace rapidjson;

struct Status {
	int mLevel{};
	int mHP{};
	int mMP{};
};

struct Item {
	std::string mName{};
	int mGold{};
};

class Monster {
private:
	std::string mName;
	Status mStatus;
	std::vector<Item> mItems;

public:
	void SetName(const std::string& name) { mName = name; }
	void SetStatus(const Status& status) { mStatus = status; }
	void AddDropItem(const Item& item) { mItems.push_back(item); }

	std::string& GetName() { return mName; }
	Status& GetStatus() { return mStatus; }
	std::vector<Item>& GetDropItem() { return mItems; }
};

bool SaveToJson(const std::string& path, std::vector<Monster>& monsters) {
	StringBuffer sb; // rapidjson 제공
	PrettyWriter<StringBuffer> writer(sb);

	// 가독성을 위해 들여쓰기와 중괄호 조절
	writer.StartObject();
	writer.Key("monsters");
		writer.StartArray();
		for (auto monster : monsters) {
			writer.StartObject();
			{
				writer.Key("name"); writer.String(monster.GetName().c_str());

				writer.Key("status");
					writer.StartObject();
					{
						auto status = monster.GetStatus();
						writer.Key("level"); writer.Int(status.mLevel);
						writer.Key("hp"); writer.Int(status.mHP);
						writer.Key("mp"); writer.Int(status.mMP);
					}
					writer.EndObject();

				writer.Key("items");
					writer.StartArray();
					{
						for (auto item : monster.GetDropItem()) {
							writer.StartObject();
							writer.Key("name"); writer.String(item.mName.c_str());
							writer.Key("gold"); writer.Int(item.mGold);
							writer.EndObject();
						}
					}
					writer.EndArray();
			}
			writer.EndObject();
		}
		writer.EndArray();
	writer.EndObject();
	
	std::ofstream ofs;
	ofs.exceptions(std::ofstream::badbit | std::ofstream::failbit);

	try {
		ofs.open(path);
		ofs << sb.GetString();
		ofs.close();
	} catch (std::ofstream::failure& e) {
		std::cerr << "invalid operatiron in SaveToJson()" << std::endl;
		std::cerr << e.what() << std::endl;
		ofs.close();
		return false;
	}

	return true;
}

bool LoadFromJson(const std::string& path, std::vector<Monster>& monsters) {
	std::ifstream ifs;
	ifs.exceptions(std::ifstream::badbit | std::ifstream::failbit);

	std::stringstream ss;

	try {
		ifs.open(path);

		// std::cout << ifs.rdbuf() << std::endl;

		ss << ifs.rdbuf();

		ifs.close();
	} catch (std::ifstream::failure& e) {
		std::cerr << "invalid operation in LoadFromJson()" << std::endl;
		std::cerr << e.what() << std::endl;
		ifs.close();
		return false;
	}

	Document doc;
	doc.Parse(ss.str().c_str());

	for (auto& monObject : doc["monsters"].GetArray()) {
		Monster monster;
		monster.SetName(monObject["name"].GetString());

		Status status;
		status.mLevel = monObject["status"].GetObject()["level"].GetInt();
		status.mHP = monObject["status"].GetObject()["hp"].GetInt();
		status.mMP = monObject["status"].GetObject()["mp"].GetInt();
		monster.SetStatus(status);

		for (auto& itemObject : monObject["items"].GetArray()) {
			Item item;
			item.mName = itemObject["name"].GetString();
			item.mGold = itemObject["gold"].GetInt();
			monster.AddDropItem(item);
		}

		monsters.push_back(monster);
	}

	return true;
}

int main() {
	std::vector<Monster> monsters;

	Monster m;
	m.SetName("슬라임");
	m.SetStatus({ 1,1,1 });
	m.AddDropItem({ "끈적한 젤리", 1 });
	monsters.push_back(m);

	m.GetDropItem().clear();
	m.SetName("늑대인간");
	m.SetStatus({ 5,5,5 });
	m.AddDropItem({ "발톱", 2 });
	m.AddDropItem({ "늑대가죽", 5 });
	monsters.push_back(m);

	m.GetDropItem().clear();
	m.SetName("악마");
	m.SetStatus({ 10,10,10 });
	m.AddDropItem({ "날개", 10 });
	m.AddDropItem({ "손톱", 5 });
	monsters.push_back(m);

	SaveToJson("Data/monsters.json", monsters);
	monsters.clear();
	LoadFromJson("Data/monsters.json", monsters);

	for (auto& monster : monsters) {
		std::cout << "Monster Name: " << monster.GetName() << std::endl
			<< "Status - Level: " << monster.GetStatus().mLevel
			<< ", HP: " << monster.GetStatus().mHP
			<< ", MP: " << monster.GetStatus().mMP << std::endl
			<< "Drop Items:" << std::endl;

		for (auto& item : monster.GetDropItem()) {
			std::cout << "  Item Name: " << item.mName
				<< ", Gold: " << item.mGold << std::endl;
		}
		std::cout << std::endl;
	}
}