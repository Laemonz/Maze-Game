#include <time.h>   //time(NULL)
#include <thread>   //multithreading and sleep
#include "player.h" 
#include "Monster.h"
#include "UI.h"

using namespace std;

struct objects;
void moveMonster(objects*);

//Use multiple threads to allow player and monster to move independently 
struct objects {
	Maze* maze;
	Player* player;
	Monster* monster;
};

void moveMonster(objects* myStruct) {
	while (myStruct->player->getHealth() > 0 && myStruct->player->getWin() == false) {
		myStruct->monster->chasePlayerSpooky(myStruct->maze, myStruct->player);
	}
}

void movePlayer(objects* myStruct) {
	while (myStruct->player->getHealth() > 0 && myStruct->player->getWin() == false) {
		myStruct->player->movePlayer(myStruct->maze);
	}
}


int main() {
	srand(time(NULL));

	Maze* maze = new Maze;
	Player* player = new Player;
	Key* key;
	Monster* monster = new Monster;

	struct objects* myStruct = new objects;
	myStruct->maze = maze;
	myStruct->player = player;
	myStruct->monster = monster;

	int n;

	bool autosolve;
	bool exit = false;
	bool quit = false;


	string solveMethod[2] = { "Manual","Autosolve (No Monster)" };
	string welcome[3] = { "Start Game", "Change Colour", "Help" };
	string yesNo[2] = { "Yes","No" };


	cout << "Welcome to the Maze Game!" << endl;
	system("PAUSE");
	system("CLS");
	while (!quit) {
		maze->showConsoleCursor(false);
		while (!exit) {
			n = selectCommand("Please choose an option.", welcome, 3);
			switch (n) {
			case 0: //start
				exit = true;
				break;

			case 1: //Change Colour
				chooseColour();
				break;

			case 2: //Help
				displayHelp();
				break;
			}
		}
		exit = false; //reset var

		autosolve = selectCommand("Please would you like to manually solve the maze or let the computer solve it? (Y/N)", solveMethod, 2);
		if (!autosolve) {
			chooseDifficulty(monster);
		}


		//SETUP MAZE-------------------------------------------------------------------------------------------------
		maze->setyStart(rows - 2);    //starting coords must both be odd numbers
		maze->setxStart(cols - 2);    //and not equal to rows or cols

		player->setyPos(maze->getyStart());
		player->setxPos(maze->getxStart());
		player->setWin(false);
		player->setHealth(1);

		maze->generateMaze();
		maze->getGrid(maze->getyStart(), maze->getxStart())->setContents(PLAYERICON);  //set start to PLAYERICON
		maze->setxEnd(1);
		maze->setyEnd(1);
		maze->updateGridContents(1, 1, EXITICON); //set exit to EXITICON

		maze->spawnDoors();
		key = maze->spawnKey((rows + cols));
		maze->resetVisited(false);

		monster->placeMonster(maze, rows / 2, cols / 2);

		//reprint the maze because the printing method sometimes leaves annoying blue lines from printing the characters
		system("CLS");
		maze->printMaze();
		//Maze Setup Complete----------------------------------------------------------------------------------------


		if (autosolve) {
			player->solveMaze(maze, key->getyPos(), key->getxPos());    //find the key
			maze->resetVisited(false);
			player->solveMaze(maze, maze->getyEnd(), maze->getxEnd());
			system("CLS");
			maze->printMaze();
			std::cout << "Exit Reached!" << std::endl;
		}
		else {
			std::thread mThread(moveMonster, myStruct); //create new thread for monster movement
			mThread.detach();                           //detach from main
			std::thread pThread(movePlayer, myStruct);  //create new thread for player movement
			pThread.join();                             //sync with main
			if (player->getHealth() <= 0) {
				system("CLS");
				maze->printMaze();
				std::cout << "You were killed by the monster!" << std::endl;
				maze->sleep(1500);
				system("PAUSE");
			}
			else {   //win
				maze->printMaze();
				std::cout << "You reached the exit!" << std::endl;
				maze->sleep(1500);
				system("PAUSE");
			}

		}
		exit = false;
		system("CLS");
		maze->printMaze();
		quit = selectCommand("Would you like to play again?", yesNo, 2);
		maze->resetVisited(false);

	}

	return 0;
}
