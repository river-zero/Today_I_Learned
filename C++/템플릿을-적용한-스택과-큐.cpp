#include <iostream>

// LinkedList 선언 및 정의 - - - - - - - - - - - - - - - - - - - -
template <typename T>
class LinkedList {
protected:
    struct Element {
        T value{};
        Element* pNext{};
    };

    int mCount;
    Element* mHead;
    Element* mTail;

public:
    LinkedList() : mCount{}, mHead{}, mTail{} {};
    virtual ~LinkedList() { DeleteAll(); }

    virtual void Insert(const T& value) = 0;
    virtual bool Remove() = 0;
    virtual void Print() const;
    void DeleteAll();
};

template <typename T>
void LinkedList<T>::Print() const {
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

template <typename T>
void LinkedList<T>::DeleteAll() {
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
template <typename T>
class Stack : public LinkedList<T> {
public:
    Stack() : LinkedList<T>() {}
    ~Stack() {}
    void Insert(const T& value) override;
    bool Remove() override;
    void Print() const override;
};

template <typename T>
void Stack<T>::Insert(const T& value) {
    typename LinkedList<T>::Element* pElement = new typename LinkedList<T>::Element;
    pElement->value = value;

    pElement->pNext = this->mHead;
    this->mHead = pElement;
    this->mCount++;
}

template <typename T>
bool Stack<T>::Remove() {
    if (!this->mCount) {
        std::cout << "* Stack is Empty" << std::endl;
        return false;
    }

    typename LinkedList<T>::Element* pPrevTop = this->mHead;
    this->mHead = this->mHead->pNext;
    this->mCount--;

    delete pPrevTop;
    return true;
}

template <typename T>
void Stack<T>::Print() const {
    if (!this->mCount) {
        std::cout << "* Nothing to Print" << std::endl;
        return;
    }

    typename LinkedList<T>::Element* pElement = this->mHead;

    while (pElement) {
        std::cout << pElement->value << std::endl;
        pElement = pElement->pNext;
    }
}

// Queue 선언 및 정의 - - - - - - - - - - - - - - - - - - - - - - -
template <typename T>
class Queue : public LinkedList<T> {
public:
    Queue() : LinkedList<T>() {}
    ~Queue() {}
    void Insert(const T& value) override;
    bool Remove() override;
};

template <typename T>
void Queue<T>::Insert(const T& value) {
    typename LinkedList<T>::Element* pElement = new typename LinkedList<T>::Element;
    pElement->value = value;

    if (!this->mCount) {
        this->mHead = pElement;
    } else {
        this->mTail->pNext = pElement;
    }

    this->mTail = pElement;
    this->mCount++;
}

template <typename T>
bool Queue<T>::Remove() {
    if (!this->mCount) {
        std::cout << "* Queue is Empty" << std::endl;
        return false;
    }

    typename LinkedList<T>::Element* pHead = this->mHead;
    this->mHead = this->mHead->pNext;
    this->mCount--;

    delete pHead;
    return true;
}

int main() {
    std::cout << "--- stack ---" << std::endl;
    LinkedList<int>* stack = new Stack<int>();
    stack->Insert(4);
    stack->Insert(7);
    stack->Insert(9);
    stack->Print();
    stack->DeleteAll();
    stack->Insert(12);
    stack->Print();
    stack->Remove();
    stack->Print();
    delete stack;

    std::cout << "--- queue ---" << std::endl;
    LinkedList<std::string>* queue = new Queue<std::string>();
    queue->Insert("aa");
    queue->Insert("gh");
    queue->Insert("gd");
    queue->Print();
    queue->Remove();
    queue->Print();
    queue->DeleteAll();
    queue->Insert("dg");
    queue->Print();
    delete queue;
}