#include <iostream>
#include <memory>

namespace mytree {
	struct Point {
		int x;
		int y;

		Point() : x{}, y{} {}
		Point(int x, int y) : x(x), y(y) {}
	};

	struct Node {
		Point pos;
		int data;

		Node() : pos{}, data{} {}
		Node(Point p, int data) : pos(p), data(data) {}
	};

	class QuadTree {
		Point topLeft;     // 좌상단
		Point bottomRight; // 우하단

		Node* node;

		std::unique_ptr<QuadTree> nw; // 북서
		std::unique_ptr<QuadTree> ne; // 북동
		std::unique_ptr<QuadTree> sw; // 남서
		std::unique_ptr<QuadTree> se; // 남동

	private:
		bool IsInBound(Point pt) {
			return pt.x >= topLeft.x && pt.x <= bottomRight.x
				&& pt.y >= topLeft.y && pt.y <= bottomRight.y;
		}

	public:
		QuadTree()
			: topLeft(Point()),
			bottomRight(Point()),
			node(nullptr),
			nw(nullptr),
			ne(nullptr),
			sw(nullptr),
			se(nullptr) {
		}

		QuadTree(Point tl, Point br) : QuadTree() {
			topLeft = tl;
			bottomRight = br;
		}

		void Insert(Node* node) {
			// base case
			// 빈 경우
			if (node == nullptr) return;

			// 현재 영역이 아닌 경우
			if (!IsInBound(node->pos)) return;

			// 더 이상 나눌 수 없는 경우
			if (std::abs(topLeft.x - bottomRight.x) <= 1 &&
				std::abs(topLeft.y - bottomRight.y) <= 1) {
				if (this->node == nullptr) {
					this->node = node;
				}
				return;
			}

			// recursive case
			// 서쪽
			if ((topLeft.x + bottomRight.x) / 2 >= node->pos.x) {
				// 북서
				if (node->pos.y <= (topLeft.y + bottomRight.y) / 2) {
					if (nw == nullptr) {
						nw = std::make_unique<QuadTree>(
							Point(topLeft.x, topLeft.y),
							Point((topLeft.x + bottomRight.x) / 2, (topLeft.y + bottomRight.y) / 2));
					}
					nw->Insert(node);
				}
				// 남서
				else {
					if (sw == nullptr) {
						sw = std::make_unique<QuadTree>(
							Point(topLeft.x, (topLeft.y + bottomRight.y) / 2),
							Point((topLeft.x + bottomRight.x) / 2, bottomRight.y));
					}
					sw->Insert(node);
				}
			}
			// 동쪽
			else {
				// 북동
				if (node->pos.y <= (topLeft.y + bottomRight.y) / 2) {
					if (ne == nullptr) {
						ne = std::make_unique<QuadTree>(
							Point((topLeft.x + bottomRight.x) / 2, topLeft.y),
							Point(bottomRight.x, (topLeft.y + bottomRight.y) / 2));
					}
					ne->Insert(node);
				}
				// 남동
				else {
					if (se == nullptr) {
						se = std::make_unique<QuadTree>(
							Point((topLeft.x + bottomRight.x) / 2, (topLeft.y + bottomRight.y) / 2),
							Point(bottomRight.x, bottomRight.y));
					}
					se->Insert(node);
				}
			}
		}

		Node* Search(Point pt) {
			// 현재 영역이 아닌 경우
			if (!IsInBound(pt)) return nullptr;

			// 더 이상 나눌 수 없는 경우
			if (node != nullptr) return node;

			// 서쪽
			if ((topLeft.x + bottomRight.x) / 2 >= pt.x) {
				// 북서
				if ((topLeft.y + bottomRight.y) / 2 >= pt.y) {
					if (nw == nullptr) {
						return nullptr;
					}
					return nw->Search(pt);
				}
				// 남서
				else {
					if (sw == nullptr) {
						return nullptr;
					}
					return sw->Search(pt);
				}
			}
			// 동쪽
			else {
				// 북동
				if ((topLeft.y + bottomRight.y) / 2 >= pt.y) {
					if (ne == nullptr) {
						return nullptr;
					}
					return ne->Search(pt);
				}
				// 남동
				else {
					if (se == nullptr) {
						return nullptr;
					}
					return se->Search(pt);
				}
			}
		}
	};
}

using namespace mytree;

int main() {
	QuadTree q(Point(0, 0), Point(8, 8));

	std::unique_ptr<Node> a = std::make_unique<Node>(Point(1, 1), 1);
	std::unique_ptr<Node> b = std::make_unique<Node>(Point(2, 2), 2);
	std::unique_ptr<Node> c = std::make_unique<Node>(Point(3, 3), 3);
	std::unique_ptr<Node> d = std::make_unique<Node>(Point(4, 4), 4);

	q.Insert(a.get());
	q.Insert(b.get());
	q.Insert(c.get());
	q.Insert(d.get());

	std::cout << "Node b : " << q.Search(Point(2, 2))->data;
}