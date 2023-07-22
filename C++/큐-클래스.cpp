class Queue {
private:
	struct Element {
		int value{};
		Element* pNext{};
	};

	int mCount;
	Element* mHead;
	Element* mTail;

public:
	Queue() = default;

	~Queue() {
		DeleteAll();
	}

	void EnQueue(int value) {
		Element* pElement = new Element;
		pElement->value = value;

		if (!mCount) {
			mHead = pElement;
		} else {
			mTail->pNext = pElement;
		}

		mTail = pElement;
		mCount++;
	}
	
	bool DeQueue() {
		if (!mCount) {
			std::cout << "* Queue is Empty" << std::endl;
			return false;
		}

		Element* pHead = mHead;
	    mHead = mHead->pNext;
		mCount--;

		delete pHead;
		return true;
	}

	void Print() {
		if (!mCount) {
			std::cout << "* Queue is Empty" << std::endl;
			return;
		}

		Element* pElement = mHead;

		while (pElement) {
			std::cout << pElement->value << " ";
			pElement = pElement->pNext;
		}

		std::cout << std::endl;
	}

	void DeleteAll() {
		Element* pElement = mHead;
		Element* pNext{};

		while (pElement) {
			pNext = pElement->pNext;
			delete pElement;
			pElement = pNext;
		}

		std::cout << "* All Deleted" << std::endl;

		mCount = 0;
		mHead = nullptr;
		mTail = nullptr;
	}
};