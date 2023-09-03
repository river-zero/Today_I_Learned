#include <iostream>

enum Object {
	OBJ_SPACE,
	OBJ_WALL,
	OBJ_GOAL,
	OBJ_BLOCK,
	OBJ_BLOCK_ON_GOAL,
	OBJ_PLAYER,
	OBJ_PALYER_ON_GOAL,

	OBJ_MAX // 카운트 또는 검증 용도
};

const char gStageData[]{ "\
########\n\
# .. p #\n\
# oo   #\n\
#      #\n\
########"
};

const int gStageWidth  = 8;
const int gStageHeight = 5;

void Initialize(Object* stage, int w, int h, const char* data);
void Draw(const Object* stage, int w, int h);
void Update(Object* stage, char input, int w, int h);
bool IsClear(const Object* stage, int w, int h);

int main() {
	Object* stage = new Object[gStageWidth * gStageHeight];

	Initialize(stage, gStageWidth, gStageHeight, gStageData);

	while (true) {
		Draw(stage, gStageWidth, gStageHeight);

		if (IsClear(stage, gStageWidth, gStageHeight)) {
			break;
		}

		std::cout << "a:left, b:right, w:up, s:down. command?";
		char input;
		std::cin >> input;

		Update(stage, input, gStageWidth, gStageHeight);
	}

	std::cout << "You Win!" << std::endl;
	delete[] stage;
	stage = nullptr;
}

void Initialize(Object* stage, int w, int h, const char* data) {
	const char* p = data;
	int x = 0;
	int y = 0;

	while (*p != '\0') {
		Object t;

		switch (*p) {
		case '#':
			t = OBJ_WALL;
			break;
		case ' ':
			t = OBJ_SPACE;
			break;
		case 'o':
			t = OBJ_BLOCK;
			break;
		case 'O':
			t = OBJ_BLOCK_ON_GOAL;
			break;
		case '.':
			t = OBJ_GOAL;
			break;
		case 'p':
			t = OBJ_PLAYER;
			break;
		case 'P':
			t = OBJ_PALYER_ON_GOAL;
			break;
		case '\n':
			y++;
			x = 0;
			t = OBJ_MAX;
			break;
		default:
			t = OBJ_MAX;
			break;
		}

		if (t != OBJ_MAX) {
			stage[y * w + x] = t;
			x++;
		}

		p++;
	}
}

void Draw(const Object* stage, int w, int h) {
	const char table[]{ ' ', '#', '.', 'o', 'O', 'p', 'P' };

	for (int y{}; y < h; y++) {
		for (int x{}; x < w; x++) {
			Object o = stage[y * w + x];
			std::cout << table[o];
		}
		std::cout << std::endl;
	}
}

void Update(Object* stage, char input, int w, int h) {
	int dx{};
	int dy{};
	switch (input) {
	case 'a':
		dx = -1;
		break;
	case 'd':
		dx = 1;
		break;
	case 'w':
		dy = -1;
		break;
	case 's':
		dy = 1;
		break;
	}

	// 플레이어 현재 위치
	int i{};
	for (; i < w * h; i++) {
		if (stage[i] == OBJ_PLAYER || stage[i] == OBJ_PALYER_ON_GOAL) {
			break;
		}
	}
	int x = i % w;
	int y = i / w;

	int tx = x + dx;
	int ty = y + dy;

	if (tx < 0 || ty < 0 || tx >= w || ty >= h) {
		std::cerr << "Invaild Player Position" << std::endl;
		return;
	}

	int p  = y * w + x;
	int tp = ty * w + tx;

	if (stage[tp] == OBJ_SPACE || stage[tp] == OBJ_GOAL) {
		stage[tp] = (stage[tp] == OBJ_GOAL) ? OBJ_PALYER_ON_GOAL : OBJ_PLAYER;
		stage[p] = (stage[p] == OBJ_PALYER_ON_GOAL) ? OBJ_GOAL : OBJ_SPACE;
	}
	else if (stage[tp] == OBJ_BLOCK || stage[tp] == OBJ_BLOCK_ON_GOAL) {
		int tx2 = tx + dx;
		int ty2 = ty + dy;

		if (tx2 < 0 || ty2 < 0 || tx >= w || ty2 >= h) {
			std::cerr << "Invalid Box Block Position" << std::endl;
			return;
		}

		int tp2 = ty2 * w + tx2;
		if (stage[tp2] == OBJ_SPACE || stage[tp2] == OBJ_GOAL) {
			stage[tp2] = (stage[tp2] == OBJ_GOAL) ? OBJ_BLOCK_ON_GOAL : OBJ_BLOCK;
			stage[tp] = (stage[tp] == OBJ_BLOCK_ON_GOAL) ? OBJ_PALYER_ON_GOAL : OBJ_PLAYER;
			stage[p] = (stage[p] == OBJ_PALYER_ON_GOAL) ? OBJ_GOAL : OBJ_SPACE;
		}
	}
}

bool IsClear(const Object* stage, int w, int h) {
	for (int i{}; i < w * h; i++) {
		if (stage[i] == OBJ_BLOCK) {
			return false;
		}
	}
	return true;
}