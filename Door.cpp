#include "Door.h"

Door::Door() {
	key = nullptr;
	isOpen = false;
}

Door::~Door() {
	delete key;
}

Key* Door::getKey() {
	return key;
}
void Door::setKey(Key* newKey) {
	key = newKey;
}

bool Door::getIsOpen() {
	return isOpen;
}
void Door::setIsOpen(bool _b) {
	isOpen = _b;
}

int Door::getxPos() {
	return xPos;
}
void Door::setxPos(int _x) {
	xPos = _x;
}

int Door::getyPos() {
	return yPos;
}
void Door::setyPos(int _y) {
	yPos = _y;
}