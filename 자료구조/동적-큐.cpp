#include <iostream>

struct Element {
	int value{};
	Element* pNext{};
};

struct Queue {
	int count{};
	Element* pHead{};
	Element* pTail{};
};

void EnQueue(Queue& queue, int value) {
	Element* pElement = new Element;
	pElement->value = value;

	if (queue.count == 0) {
		queue.pHead = pElement;
	}
	else {
		queue.pTail->pNext = pElement;
	}

	queue.pTail = pElement;
	queue.count++;
}

bool DeQueue(Queue& queue) {
	if (queue.count == 0) {
		std::cout << "* Queue is Empty" << std::endl;
		return false;
	}

	Element* pHead = queue.pHead;
	queue.pHead = queue.pHead->pNext;
	queue.count--;

	delete pHead;
	return true;
}

void Print(Queue& queue) {
	if (queue.count == 0) {
		std::cout << "* Queue is Empty" << std::endl;
		return;
	}

	Element* pElement = queue.pHead;

	while (pElement) {
		std::cout << pElement->value << " ";
		pElement = pElement->pNext;
	}

	std::cout << std::endl;
}

void DeleteAll(Queue& queue) {
	Element* pElement = queue.pHead;
	Element* pNext{};

	while (pElement) {
		pNext = pElement->pNext;
		delete pElement;
		pElement = pNext;
	}

	std::cout << "* All Deleted" << std::endl;

	queue.count = 0;
	queue.pHead = nullptr;
	queue.pTail = nullptr;
}

int main() {
	Queue myQueue;

	DeleteAll(myQueue);

	EnQueue(myQueue, 1);
	EnQueue(myQueue, 2);
	EnQueue(myQueue, 3);

	Print(myQueue);

	DeQueue(myQueue);
	Print(myQueue);
	DeQueue(myQueue);
	Print(myQueue);
	DeQueue(myQueue);
	Print(myQueue);
	DeQueue(myQueue);
	Print(myQueue);

	DeleteAll(myQueue);
}