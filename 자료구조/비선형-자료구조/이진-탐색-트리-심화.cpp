#include <iostream>
#include <memory>

namespace mytree {
	struct Node {
		int mData;
		std::unique_ptr<Node> mpLeft;
		std::unique_ptr<Node> mpRight;

		Node(int data = 0, Node* pLeft = nullptr, Node* pRight = nullptr)
			: mData(data), mpLeft(pLeft), mpRight(pRight) {
		}
	};

	class BinaryTree {
	protected:
		std::unique_ptr<Node> mpRoot;

	public:
		BinaryTree() : mpRoot(nullptr) {}

		Node* CreateNode(int value, Node* pLeft = nullptr, Node* pRight = nullptr) {
			return new Node(value, pLeft, pRight);
		}

		Node* GetRoot() { return mpRoot.get(); }

		Node* InsertLeft(Node* parent, int value) {
			parent->mpLeft = std::unique_ptr<Node>(CreateNode(value));
			return parent->mpLeft.get();
		}

		Node* InsertRight(Node* parent, int value) {
			parent->mpRight = std::unique_ptr<Node>(CreateNode(value));
			return parent->mpRight.get();
		}

		Node* Find(Node* parent, int value) {
			if (!parent) return nullptr;

			if (value < parent->mData) {
				return Find(parent->mpLeft.get(), value);
			} else if (value > parent->mData) {
				return Find(parent->mpRight.get(), value);
			}

			return parent;
		}

		Node* Max(Node* parent) {
			while (parent && parent->mpRight) {
				parent = parent->mpRight.get();
			}
			return parent;
		}

		void Visit(Node* node) {
			std::cout << node->mData << " ";
		}

		void InOrder(Node* node) {
			if (!node) return;
			InOrder(node->mpLeft.get());
			Visit(node);
			InOrder(node->mpRight.get());
		}
	};

	class BinarySearchTree : public BinaryTree {
	public:
		Node* Insert(Node* parent, int value) {
			if (!parent) {
				if (parent == GetRoot()) {
					mpRoot = std::unique_ptr<Node>(CreateNode(value));
					return GetRoot();
				} else {
					return CreateNode(value);
				}
			}

			if (value < parent->mData) {
				parent->mpLeft.reset(Insert(parent->mpLeft.release(), value));
			} else if (value > parent->mData) {
				parent->mpRight.reset(Insert(parent->mpRight.release(), value));
			}

			return parent;
		}

		Node* Erase(Node* parent, int value) {
			if (!parent) return nullptr;

			// 탐색
			if (value < parent->mData) {
				parent->mpLeft.reset(Erase(parent->mpLeft.release(), value));
			} else if (value > parent->mData) {
				parent->mpRight.reset(Erase(parent->mpRight.release(), value));
			} else {
				// 삭제 - 자식에 따라 분류
				if (!parent->mpLeft && !parent->mpRight) {
					delete parent;
					return nullptr;
				} else if (!parent->mpLeft) {
					Node* temp = parent->mpRight.release();
					delete parent;
					return temp;
				} else if (!parent->mpRight) {
					Node* temp = parent->mpLeft.release();
					delete parent;
					return temp;
				} else { // 이진 탐색 트리의 속성 유지
					Node* temp = Max(parent->mpLeft.get());
					parent->mData = temp->mData;
					parent->mpLeft.reset(Erase(parent->mpLeft.release(), temp->mData));
				}
			}

			return parent;
		}
	};
}

using namespace mytree;

int main() {
	BinarySearchTree bst;

	int data[] = { 5,9,1,4,2,3,8,7,6 };
	for (int e : data) {
		bst.Insert(bst.GetRoot(), e);
	}

	bst.InOrder(bst.GetRoot());
	std::cout << std::endl;

	Node* search = bst.Find(bst.GetRoot(), 5);
	if (search) {
		std::cout << search->mData << " exists" << std::endl;
	} else {
		std::cout << "no such data" << std::endl;
	}

	bst.Erase(bst.GetRoot(), 5);
	bst.InOrder(bst.GetRoot());
}