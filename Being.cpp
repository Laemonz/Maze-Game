#include "Being.h"

Being::Being() {
	name = "BLANK";
	health = 1;

	for (int i = 0; i < invSize; i++) {
		inventory[i] = 0;
	}
	xPos = 1;
	yPos = 1;
}

Being::~Being() {
	//dtor
}

std::string Being::getName() {
	return name;
}
void Being::setName(std::string _name) {
	name = _name;
}

int Being::getHealth() {
	return health;
}
void Being::setHealth(int _health) {
	health = _health;
}

int* Being::getInventory(int i) {
	return &inventory[i];
}
void Being::setInventory(int* element, int _inv) {
	(*element) = _inv;
}
void Being::setInventory(int i, int _inv) {
	inventory[i] = _inv;
}

int Being::getxPos() {
	return xPos;
}
void Being::setxPos(int _x) {
	xPos = _x;
}

int Being::getyPos() {
	return yPos;
}
void Being::setyPos(int _y) {
	yPos = _y;
}


void Being::displayBeing() {
	std::cout << "Name: " << name << std::endl;
	std::cout << "Health: " << health << std::endl;
	std::cout << "Inventory: ";
	for (int i = 0; i < invSize; i++) {
		std::cout << inventory[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "Position: Row " << yPos << ", Column " << xPos << std::endl;


	return;
}
