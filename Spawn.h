#ifndef SPAWN_H
#define SPAWN_H

#include "maze.h"

class Spawn {
public:
	Spawn();
	virtual ~Spawn();

	int getyPos();
	void setyPos(int);

	int getxPos();
	void setxPos(int);

	void spawnDoors(Maze*, Maze); //spawn doors in the maze
	void spawnKey(Maze*, Maze, Door* [3]); //spawn a key in the maze

protected:

private:
	int yPos;
	int xPos;
};

#endif // SPAWN_H
