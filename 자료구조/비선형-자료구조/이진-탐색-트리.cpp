#include <iostream>

namespace mytree {
	struct Node {
		int mData;
		Node* mpLeft;
		Node* mpRight;

		Node(int data = 0, Node* pLeft = nullptr, Node* pRight = nullptr) {
			mData = data;
			mpLeft = pLeft;
			mpRight = pRight;
		}
	};

	class BinarySearchTree {
	private:
		Node* mpRoot;

	public:
		BinarySearchTree() {
			mpRoot = CreateNode(0);
		}

		Node* CreateNode(int value, Node* pLeft = nullptr, Node* pRight = nullptr) {
			return new Node(value, pLeft, pRight);
		}

		Node* GetRoot() { return mpRoot; }

		Node* Insert(Node* parent, int data) {
			// base case
			if (parent == nullptr) {
				return CreateNode(data);
			}

			// recursive case
			if (data < parent->mData) {
				parent->mpLeft = Insert(parent->mpLeft, data);
			} else if (data > parent->mData) {
				parent->mpRight = Insert(parent->mpRight, data);
			}

			return parent;
		}

	public:
		void Visit(Node* node) { 
			std::cout << node->mData << " "; 
		}

		void InOrder(Node* node) {
			if (node == nullptr) return;

			InOrder(node->mpLeft);
			Visit(node);
			InOrder(node->mpRight);
		}
	};
}

int main() {
	using namespace mytree;

	BinarySearchTree bst;

	auto root = bst.Insert(nullptr, 8);
	bst.Insert(root, 3);
	bst.Insert(root, 10);
	bst.Insert(root, 1);
	bst.Insert(root, 6);

	bst.InOrder(root); // 1 3 6 8 10
}