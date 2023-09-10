#include <iostream>
#include <queue>
#include <stack>
#include <memory>

namespace mytree {
	struct Node { // 너무 일반적인 이름이기 때문에 namespace 사용
		int mData;
		std::unique_ptr<Node> mpLeft;
		std::unique_ptr<Node> mpRight;

		Node(int data = 0, Node* pLeft = nullptr, Node* pRight = nullptr)
			: mData(data), mpLeft(pLeft), mpRight(pRight) {
		}
	};

	class BinaryTree {
	private:
		std::unique_ptr<Node> mpRoot;

	public:
		BinaryTree() {
			mpRoot = CreateNode(0);
		}

		std::unique_ptr<Node> CreateNode(int value, Node* pLeft = nullptr, Node* pRight = nullptr) {
			return std::make_unique<Node>(value, pLeft, pRight);
		}

		Node* GetRoot() { return mpRoot.get(); }

		Node* InsertLeft(Node* parent, int value) {
			parent->mpLeft = CreateNode(value);
			return parent->mpLeft.get();
		}

		Node* InsertRight(Node* parent, int value) {
			parent->mpRight = CreateNode(value);
			return parent->mpRight.get();
		}

	public:
		void Visit(Node* node) {
			std::cout << node->mData << " ";
		}

		void BreadthFirstSearch() {
			std::queue<Node*> q;

			q.push(mpRoot.get());

			while (!q.empty()) {
				auto node = q.front();
				Visit(node);
				q.pop();

				if (node->mpLeft) {
					q.push(node->mpLeft.get());
				}
				if (node->mpRight) {
					q.push(node->mpRight.get());
				}
			}
		}

		void DepthFirstSearch() {
			std::stack<Node*> s;

			s.push(mpRoot.get());

			while (!s.empty()) {
				auto node = s.top();
				Visit(node);
				s.pop();

				if (node->mpRight) {
					s.push(node->mpRight.get());
				}
				if (node->mpLeft) {
					s.push(node->mpLeft.get());
				}
			}
		}

		void RDepthFirstSearch(Node* node) {
			if (!node) {
				return;
			}

			Visit(node);
			RDepthFirstSearch(node->mpLeft.get());
			RDepthFirstSearch(node->mpRight.get());
		}

		void PreOrder(Node* node) { // 전위 순회
			if (!node) {
				return;
			}

			Visit(node);
			PreOrder(node->mpLeft.get());
			PreOrder(node->mpRight.get());
		}

		void InOrder(Node* node) { // 중위 순회
			if (!node) {
				return;
			}

			InOrder(node->mpLeft.get());
			Visit(node);
			InOrder(node->mpRight.get());
		}

		void PostOrder(Node* node) { // 후위 순회
			if (!node) {
				return;
			}

			PostOrder(node->mpLeft.get());
			PostOrder(node->mpRight.get());
			Visit(node);
		}

		int Sum(Node* node) { // 합계
			if (!node) {
				return 0;
			}

			return node->mData + Sum(node->mpLeft.get()) + Sum(node->mpRight.get());
		}

		bool Search(int value, Node* node) { // 특정 값 탐색
			if (!node) {
				return false;
			}

			return node->mData == value || Search(value, node->mpLeft.get()) || Search(value, node->mpRight.get());
		}

		int Depth(Node* node) { // 트리의 높이
			if (!node) {
				return 0;
			}

			return 1 + std::max(Depth(node->mpLeft.get()), Depth(node->mpRight.get()));
		}
	};
}

using namespace mytree;

int main() {
	BinaryTree myTree;

	auto pRoot = myTree.GetRoot();
	pRoot->mData = 1;

	auto pNode = myTree.InsertLeft(pRoot, 2);
	myTree.InsertLeft(pNode, 4);
	myTree.InsertRight(pNode, 5);

	pNode = myTree.InsertRight(pRoot, 3);
	myTree.InsertLeft(pNode, 6);
	myTree.InsertRight(pNode, 7);

	myTree.BreadthFirstSearch();     // 1 2 3 4 5 6 7
	std::cout << std::endl;
	myTree.DepthFirstSearch();       // 1 2 4 5 3 6 7
	std::cout << std::endl;
	myTree.RDepthFirstSearch(pRoot); // 1 2 4 5 3 6 7
	std::cout << std::endl;
	myTree.PreOrder(pRoot);          // 1 2 4 5 3 6 7
	std::cout << std::endl;
	myTree.InOrder(pRoot);           // 4 2 5 1 6 3 7
	std::cout << std::endl;
	myTree.PostOrder(pRoot);         // 4 5 2 6 7 3 1
	std::cout << std::endl;

	std::cout << myTree.Sum(pRoot) << std::endl;                         // 28
	std::cout << std::boolalpha << myTree.Search(8, pRoot) << std::endl; // false
	std::cout << "depth = " << myTree.Depth(pRoot) << std::endl;         // depth = 3
}