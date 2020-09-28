#ifndef STACK_H
#define STACK_H

#include <string>   //std::string
#include <iostream> //cout
#include "Link.h"

class Stack {
public:
	Stack();
	virtual ~Stack();

	Link* push(TYPE);  //add an element given some contents
	Link* push(Link*); //add a link
	Link* peek();      //return the top of the stack
	Link* pop();       //remove the top of the stack
	void printStack(); //list the stack


private:
	Link* top;
};

#endif // STACK_H
