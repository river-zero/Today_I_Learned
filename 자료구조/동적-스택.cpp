#include <iostream>

struct Element {
	int value{};
	Element* pNext{};
};

struct Stack {
	int count{};
	Element* pTop{};
};

void Push(Stack& stack, int value) {
	Element* pElement = new Element;
	pElement->value = value;

	pElement->pNext = stack.pTop;
	stack.pTop = pElement;
	stack.count++;
}

bool Pop(Stack& stack) {
	if (stack.count == 0) {
		std::cout << "* Stack is Empty" << std::endl;
		return false;
	}

	Element* pPrevTop = stack.pTop;
	stack.pTop = stack.pTop->pNext;
	stack.count--;

	delete pPrevTop;
	return true;
}

void Print(Stack& stack) {
	Element* pElement = stack.pTop;

	if (stack.count == 0) {
		std::cout << "* Stack is Empty" << std::endl;
		return;
	}

	while (pElement) {
		std::cout << pElement->value << std::endl;
		pElement = pElement->pNext;
	}
}

void DeleteAll(Stack& stack) {
	Element* pElement = stack.pTop;
	Element* pNext{};

	while (pElement) {
		pNext = pElement->pNext;
		delete pElement;
		pElement = pNext;
	}

	std::cout << "* All Deleted" << std::endl;

	stack.count = 0;
	stack.pTop = nullptr;
}

int main() {
	Stack myStack;

	DeleteAll(myStack);

	Push(myStack, 1);
	Push(myStack, 2);
	Push(myStack, 3);

	Print(myStack);

	Pop(myStack);
	Print(myStack);
	Pop(myStack);
	Print(myStack);
	Pop(myStack);
	Print(myStack);
	Pop(myStack);
	Print(myStack);
	
	DeleteAll(myStack);
}