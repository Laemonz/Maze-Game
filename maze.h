#ifndef MAZE_H
#define MAZE_H

#include <iostream>		//cout
#include <windows.h>	//console print functions
#include <thread>		//sleep
#include "Stack.h"		//used for recursive baccktracing
#include "Cell.h"		//2d array of cells used for maze

#include "assert.h" //bugtesting


#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3

//rows and cols must be odd
const int rows = 29;
const int cols = 35;
const int nRand = (rows + cols) / 4;  //1 in nRand chance to make a loop

const char WALL = char(219);
const char BLANK = ' ';
const char PLAYERICON = 'P';
const char EXITICON = 'E';

class Maze {
public:
	Maze();
	virtual ~Maze();

	int getxStart();
	void setxStart(int);

	int getyStart();
	void setyStart(int);

	int getxEnd();
	void setxEnd(int);

	int getyEnd();
	void setyEnd(int);

	Cell* getGrid(int, int);//get the adress of a grid element
	//use Cell.h functions to modify grid elements

	Door* getDoor(int);    //get the adress of a door element
	//use Door.h functions to modify elements

	void sleep(int);						//Have this thread sleep in miliseconds
	void setCursorPosition(int, int);		//Set cursor to specific coordinate in console
	void showConsoleCursor(bool);			//Show or hide the cursor
	void updateGridContents(int, int, char);//Set the contents of a grid element and update the screen to show it
	char checkGridContents(int, int, int);  //Check the contents or a grid given a coordinate and a direction
	void generateMaze();					//Generate the maze
	void printMaze();						//Print the maze
	void shuffleArray(int[]);				//Shuffle the moves (up, down, left, right)
	void resetVisited(bool);				//reset visited for all non WALL cells
	void spawnDoors();						//place doors at each intersection directly connected to the end of the maze
	Key* spawnKey(int _nMoves);				//spawn a key at given amount of moves away from the start
	void moveIcon(int, int, int, char, char);//Moves an icon in a direction

private:
	void buildMaze(int, int);				//Recusive function used in generation

	Cell grid[rows][cols];	//maze to be generated
	int xStart;				//col number of start point
	int yStart;				//row number of start point
	int xEnd;				//col number of end point
	int yEnd;				//row number of end point
	int moves[4];			//up,down,left,right
	Door* doors[3];			//doors to be placed
};

#endif // MAZE_H
