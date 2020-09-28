#include "Cell.h"

Cell::Cell() {
	contents = ' ';
	visited = false;
	myDoor = nullptr;
	myKey = nullptr;
}

Cell::~Cell() {
	delete myDoor;
	delete myKey;
}

char Cell::getContents() {
	return contents;
}
void Cell::setContents(char _contents) {
	contents = _contents;
}

bool Cell::getVisited() {
	return visited;
}
void Cell::setVisited(bool _visited) {
	visited = _visited;
}

Door* Cell::getmyDoor() {
	return myDoor;
}
void Cell::setmyDoor(Door* newDoor) {
	myDoor = newDoor;
}

Key* Cell::getmyKey() {
	return myKey;
}
void Cell::setmyKey(Key* newKey) {
	myKey = newKey;
}
