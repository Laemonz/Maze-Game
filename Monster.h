#ifndef MONSTER_H
#define MONSTER_H

#include "Being.h"
#include "player.h"

#include <cmath> // std::abs

const char monsterIcon = 'M';
const int EASY = 1500;
const int MEDIUM = 1000;
const int HARD = 400;
const int FAST = 10;  //threshold distance between player and monster where monster moves faster


class Monster : public Being {
public:
	Monster();
	virtual ~Monster();

	int getChaseSpeed();
	void setChaseSpeed(int);

	void placeMonster(Maze*, int, int);     //spawn the monster on a BLANK near or on a set of coordinates
	void chasePlayerSpooky(Maze*, Player*);  //Move the monster and go allow it to through walls

protected:

private:
	int chaseSpeed; //how fast the monster moves in ms
};

#endif // MONSTER_H
