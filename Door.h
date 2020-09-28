#ifndef DOOR_H
#define DOOR_H

#include "Key.h"

const char doorClosedIcon = char(178);
const char doorOpenIcon = char(176);

class Door {
public:
	Door();
	virtual ~Door();

	Key* getKey();
	void setKey(Key*);

	bool getIsOpen();
	void setIsOpen(bool);

	int getyPos();
	void setyPos(int);

	int getxPos();
	void setxPos(int);

protected:

private:
	Key* key;
	bool isOpen;
	int yPos;
	int xPos;
};

#endif // DOOR_H
