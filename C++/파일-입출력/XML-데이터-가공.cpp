/*---------------------------------------------------------------------
    mydata.xml

    <?xml version="1.0" encoding="UTF-8"?>
    <TextureAtlas imagePath="sprites.png" width="256" height="256">
        <sprite n="bug1_1.png" x="0" y="0" w="24" h="24"/>
        <sprite n="bug1_2.png" x="24" y="0" w="24" h="24"/>
        <sprite n="bug1_3.png" x="48" y="0" w="24" h="24"/>
        <sprite n="bug1_4.png" x="72" y="0" w="24" h="24"/>
    </TextureAtlas> 
---------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>

class Sprite {
public:
	std::string n;
	int x;
	int y;
	int w;
	int h;
};

void LoadXML(const char* filename, std::vector<Sprite>& sprites) {
	sprites.clear();
	
	std::ifstream file(filename, std::ifstream::binary);
	std::string line;
	std::regex pattern("\"([^\"]*)\""); // "([^"]*)"

	while (!file.eof()) {
		std::getline(file, line);

		size_t result = line.find("<sprite");
		if (result != std::string::npos) {
			std::sregex_iterator current(line.begin(), line.end(), pattern);
			std::sregex_iterator end;

			Sprite s;
			s.n = (*current)[1];
			current++;
			s.x = std::stoi((*current)[1]);
			current++;
			s.y = std::stoi((*current)[1]);
			current++;
			s.w = std::stoi((*current)[1]);
			current++;
			s.h = std::stoi((*current)[1]);

			sprites.push_back(s);
		}
	}

	file.close();
}

int main() {
	std::vector<Sprite> sprites;

	LoadXML("Data/mydata.xml", sprites);

	for (const auto& e : sprites) {
		std::cout << e.n << ", " << e.x << ", " << e.y << ", " << e.w << ", " << e.h << std::endl;
	}
}