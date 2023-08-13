#include <iostream>

// LinkedList 선언 및 정의 - - - - - - - - - - - - - - - - - - - -
class LinkedList {
protected:
    struct Element {
        int value{};
        Element* pNext{};
    };

    int mCount;
    Element* mHead;
    Element* mTail;

public:
    LinkedList() : mCount{}, mHead{}, mTail{} {}
    virtual ~LinkedList();

    virtual void Insert(int value) = 0;
    virtual bool Remove() = 0;
    virtual void Print() const;
    void DeleteAll();
};

LinkedList::~LinkedList() {
    DeleteAll();
}

void LinkedList::Print() const {
    if (!mCount) {
        std::cout << "* Nothing to Print" << std::endl;
        return;
    }

    Element* pElement = mHead;

    while (pElement) {
        std::cout << pElement->value << " ";
        pElement = pElement->pNext;
    }

    std::cout << std::endl;
}

void LinkedList::DeleteAll() {
    Element* pElement = mHead;
    Element* pNext{};

    while (pElement) {
        pNext = pElement->pNext;
        delete pElement;
        pElement = pNext;
    }

    mCount = 0;
    mHead = nullptr;
    mTail = nullptr;
}

// Stack 선언 및 정의 - - - - - - - - - - - - - - - - - - - - - - -
class Stack : public LinkedList {
public:
    Stack() : LinkedList() {};
    ~Stack() {};
    void Insert(int value) override;
    bool Remove() override;
    void Print() const override;
};

void Stack::Insert(int value) {
    Element* pElement = new Element;
    pElement->value = value;

    pElement->pNext = mHead;
    mHead = pElement;
    mCount++;
}

bool Stack::Remove() {
    if (!mCount) {
        std::cout << "* Stack is Empty" << std::endl;
        return false;
    }

    Element* pPrevTop = mHead;
    mHead = mHead->pNext;
    mCount--;

    delete pPrevTop;
    return true;
}

void Stack::Print() const {
    if (!mCount) {
        std::cout << "* Nothing to Print" << std::endl;
        return;
    }

    Element* pElement = mHead;

    while (pElement) {
        std::cout << pElement->value << std::endl;
        pElement = pElement->pNext;
    }
}

// Queue 선언 및 정의 - - - - - - - - - - - - - - - - - - - - - - -
class Queue : public LinkedList {
public:
    Queue() : LinkedList() {};
    ~Queue() {};
    void Insert(int value) override;
    bool Remove() override;
};

void Queue::Insert(int value) {
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

bool Queue::Remove() {
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

int main() {
    std::cout << "--- stack ---" << std::endl;
    LinkedList* stack = new Stack();
    stack->Insert(4);
    stack->Insert(7);
    stack->Insert(9);
    stack->Print();
    stack->Remove();
    stack->Print();
    stack->DeleteAll();
    stack->Remove();
    stack->Print();
    delete stack;

    std::cout << "--- queue ---" << std::endl;
    LinkedList* queue = new Queue();
    queue->Insert(6);
    queue->Insert(1);
    queue->Insert(43);
    queue->Print();
    queue->Remove();
    queue->Print();
    queue->DeleteAll();
    queue->Remove();
    queue->Print();
    delete queue;
}