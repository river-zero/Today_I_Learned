class Stack {
private:
	struct Element {
		int value{};
		Element* pNext{};
	};

	int mCount;
	Element* mTop;

public:
	Stack() = default;

	~Stack() {
		DeleteAll();
	}

	void Push(int value) {
		Element* pElement = new Element;
		pElement->value = value;

		pElement->pNext = mTop;
		mTop = pElement;
		mCount++;
	}

	bool Pop() {
		if (!mCount) {
			std::cout << "* Stack is Empty" << std::endl;
			return false;
		}

		Element* pPrevTop = mTop;
		mTop = mTop->pNext;
		mCount--;

		delete pPrevTop;
		return true;
	}

	void Print() const {
		Element* pElement = mTop;

		if (!mCount) {
			std::cout << "* Stack is Empty" << std::endl;
			return;
		}

		while (pElement) {
			std::cout << pElement->value << std::endl;
			pElement = pElement->pNext;
		}
	}

	void DeleteAll() {
		Element* pElement = mTop;
		Element* pNext{};

		while (pElement) {
			pNext = pElement->pNext;
			delete pElement;
			pElement = pNext;
		}

		std::cout << "* All Deleted" << std::endl;

		mCount = 0;
		mTop = nullptr;
	}
};