#ifndef CELL_H
#define CELL_H

#include "Door.h"

class Cell {
public:
	Cell();
	virtual ~Cell();

	char getContents();
	void setContents(char);

	bool getVisited();
	void setVisited(bool);

	Door* getmyDoor();
	void setmyDoor(Door*);

	Key* getmyKey();
	void setmyKey(Key*);

protected:

private:
	char contents;  //contents to be displayed in the grid
	bool visited;   //has the cell been visited yet, used in depth first searches
	Door* myDoor;   //is this cell a door
	Key* myKey;     //is this cell a key
};

#endif // CELL_H
