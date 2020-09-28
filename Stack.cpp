#include "Stack.h"

Stack::Stack() {
	top = nullptr;
}

Stack::~Stack() {
	while (top != nullptr) {
		delete pop();
	}
}

Link* Stack::peek() {
	return top;
}

Link* Stack::pop() {
	Link* temp;
	temp = top;
	top = top->getBelow();
	return temp;
}

Link* Stack::push(TYPE myContents) {
	Link* myLink = new Link;
	myLink->setContents(myContents);

	// if stack is empty
	if (top == nullptr) {
		top = myLink;
		return myLink;
	}
	else {
		myLink->setBelow(top);
		top = myLink;
		return myLink;
	}
}

Link* Stack::push(Link* newLink) {
	// if stack is empty
	if (top == nullptr) {
		top = newLink;
		return newLink;
	}
	else {
		newLink->setBelow(top);
		top = newLink;
		return newLink;
	}
}

void Stack::printStack() {
	if (top == nullptr) {
		std::cout << "Stack is empty." << std::endl;
	}
	else {
		Link* current = top;
		while (current != nullptr) {
			std::cout << current->getContents() << "  ";
			current = current->getBelow();
		}
	}
	return;
}
