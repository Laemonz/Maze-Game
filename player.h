#ifndef PLAYER_H
#define PLAYER_H

#include "Being.h"

class Player : public Being {
public:
	Player();
	virtual ~Player();

	Key* getplayerKey();
	void setplayerKey(Key*);

	bool getWin();
	void setWin(bool);

	bool checkKey(int, int, Maze*);         //Gives a key to the player if there is a key at given cell
	bool movePlayer(Maze*);                 //Move the player using arrows or wasd
	void solveMaze(Maze*, int, int);        //Let the computer solve the maze

	bool validMove(int, int, int, Maze*);   //Valid move if only if visited==false and
											//contents == (BLANK or exit or openDoor)
											//Also open doors if player has a key


protected:

private:
	Key* playerKey; //stores the key that the player must get
	bool win;       //has the player won yet?
};

#endif // PLAYER_H
