#include "Key.h"
#include "Door.h"

Key::Key() {
	xPos = 0;
	yPos = 0;
	door = nullptr;
}

Key::~Key() {
	delete door;
}

int Key::getxPos() {
	return xPos;
}
void Key::setxPos(int _x) {
	xPos = _x;
}

int Key::getyPos() {
	return yPos;
}
void Key::setyPos(int _y) {
	yPos = _y;
}

Door* Key::getDoor() {
	return door;
}
void Key::setDoor(Door* newDoor) {
	door = newDoor;
}
