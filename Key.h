#ifndef KEY_H
#define KEY_H

const char keyIcon = 'K';

class Door;

class Key {
public:
	Key();
	virtual ~Key();

	int getyPos();
	void setyPos(int);

	int getxPos();
	void setxPos(int);

	Door* getDoor();
	void setDoor(Door*);

protected:

private:
	Door* door;
	int xPos;
	int yPos;
};

#endif // KEY_H
