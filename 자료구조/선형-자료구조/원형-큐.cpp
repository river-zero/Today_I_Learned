#include <iostream>

const int QUEUE_SIZE = 10;

enum Command {
	ENQUEUE = 1,
	DEQUEUE = 2,
	QUIT    = 3
};

struct Queue {
	int container[QUEUE_SIZE]{};
	int head = 0;
	int tail = 0;
};

void PrintInfo() {
	std::cout << "<QUEUE>" << std::endl
	      	  << "[1] enqueue" << std::endl
		      << "[2] dequeue" << std::endl
		      << "[3] quit" << std::endl
		      << "-----------------" << std::endl;
}

void PrintQueue(Queue& queue) {
	std::cout << "----- queue -----" << std::endl;

	if (queue.head == queue.tail) {
		std::cout << "queue is empty" << std::endl;
		return;
	}

	int i = queue.head;

	while (i != queue.tail) {
		i = (i + 1) % QUEUE_SIZE;
		std::cout << queue.container[i] << " ";
	}

	std::cout << std::endl << "-----------------" << std::endl;
}

void EnQueue(Queue& queue, int value) {
	if ((queue.tail + 1) % QUEUE_SIZE == queue.head) {
		std::cout << "* full" << std::endl;
		return;
	}

	queue.tail = (queue.tail + 1) % QUEUE_SIZE;
	queue.container[queue.tail] = value;
}

void DeQueue(Queue& queue) {
	if (queue.head == queue.tail) {
		std::cout << "* empty" << std::endl;
		return;
	}

	queue.head = (queue.head + 1) % QUEUE_SIZE;
}

int main() {
	Queue myQueue;

	PrintInfo();

	int command = 0;

	while (true) {
		PrintQueue(myQueue);

		std::cout << "> ";
		std::cin >> command;

		switch (command) {
		case ENQUEUE: {
			int value = 0;
			std::cout << "> value ? ";
			std::cin >> value;
			EnQueue(myQueue, value);
			break;
		}
		case DEQUEUE:
			DeQueue(myQueue);
			break;
		case QUIT:
			return 0;
		default:
			std::cout << "잘못된 명령입니다." << std::endl;
		}
	}
}