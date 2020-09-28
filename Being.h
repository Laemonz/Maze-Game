#ifndef BEING_H
#define BEING_H

#include <string>   //std::string
#include <conio.h>  //getch

#include "maze.h"

const int invSize = 8;
class Being {
public:
	Being();
	virtual ~Being();

	std::string getName();
	void setName(std::string);

	int getHealth();
	void setHealth(int);

	int* getInventory(int);
	void setInventory(int*, int);   //set pointer
	void setInventory(int, int);    //set element

	int getyPos();
	void setyPos(int);

	int getxPos();
	void setxPos(int);

	void displayBeing();

protected:


private:
	std::string name;       //unused code
	int health;
	int inventory[invSize]; //unused code
	int yPos;
	int xPos;
};

#endif // BEING_H
