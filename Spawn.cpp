#include "Spawn.h"

Spawn::Spawn() {
	xPos = 1;
	yPos = 1;
}

Spawn::~Spawn() {
	//dtor
}

int Spawn::getxPos() {
	return xPos;
}
void Spawn::setxPos(int _x) {
	xPos = _x;
}

int Spawn::getyPos() {
	return yPos;
}
void Spawn::setyPos(int _y) {
	yPos = _y;
}

void Spawn::spawnDoors(Maze* realMaze, Maze mazeCopy) {
	int direction[4] = { DOWN, RIGHT, UP, LEFT };
	int currentMove;
	int nMoves;     //track how many moves we have tried
	int d = 0;        //amount of doors that have been placed
	bool exit = false;
	bool moves[4];
	bool beginInter = false;  //is the beginning an intersection
	Stack backtrack;//stack to store moves needed to backtrack
	Link* current; //used to pop the stack

	Door* doors[3];
	for (int i = 0; i < 4; i++) {
		doors[i] = new Door;
	}
	xPos = mazeCopy.getxEnd();
	yPos = mazeCopy.getyEnd();

	//set end to visited
	mazeCopy.getGrid(mazeCopy.getxEnd(), mazeCopy.getyEnd())->setVisited(true);

	while (!exit) {
		nMoves = 0;
		for (int i = 0; i < 4; i++) {
			moves[i] = false;
		}
		//find number of valid moves
		for (int i = 0; i < 4; i++) {
			switch (direction[i]) {
			case UP: //up
				if (mazeCopy.getGrid(yPos - 1, getxPos())->getVisited() == false) {
					nMoves++;
					moves[0] = true;
				}
				break;

			case DOWN: //down
				if (mazeCopy.getGrid(yPos + 1, xPos)->getVisited() == false) {
					nMoves++;
					moves[1] = true;
				}
				break;

			case LEFT: //left
				if (mazeCopy.getGrid(yPos, xPos - 1)->getVisited() == false) {
					nMoves++;
					moves[2] = true;
				}
				break;

			case RIGHT: //right
				if (mazeCopy.getGrid(yPos, xPos + 1)->getVisited() == false) {
					nMoves++;
					moves[3] = true;
				}
				break;

			}//end switch
		}
		if ((xPos == mazeCopy.getxEnd() && yPos == mazeCopy.getyEnd()) && (nMoves > 1)) { //begining is an intersection
			beginInter = true;
			xPos = xPos + 1;
			yPos = mazeCopy.getyEnd();
		}
		else if (nMoves > 1) {   //we have reached an intersection
			//place door at current pos
			doors[d]->setxPos(xPos);
			doors[d]->setyPos(yPos);
			realMaze->getGrid(yPos, xPos)->setmyDoor(doors[d]);
			realMaze->getGrid(yPos, xPos)->setContents(doorClosedIcon);
			d++;
			//now backtrack
			current = backtrack.pop();
			switch (current->getContents()) {
			case UP: //up
				yPos = yPos - 1;
				break;
			case DOWN: //down
				yPos = yPos + 1;
				break;
			case LEFT: //left
				xPos = xPos - 1;
				break;
			case RIGHT: //right
				xPos = xPos + 1;
				break;
			default:
				std::cout << "Backtrack Error!" << std::endl;
				assert(false);
			}//end switch
		}
		else if (nMoves == 1) { //we are in a hallway, keep moving
			for (int i = 0; i < 4; i++) {
				if (moves[i] == true) {
					switch (i) {
					case 0: //up
						mazeCopy.getGrid(yPos - 1, xPos)->setVisited(true);
						yPos = yPos - 1;
						break;

					case 1: //down
						mazeCopy.getGrid(yPos + 1, xPos)->setVisited(true);
						yPos = yPos + 1;
						break;

					case 2: //left
						mazeCopy.getGrid(yPos, xPos - 1)->setVisited(true);
						xPos = xPos - 1;
						break;

					case 3: //right
						mazeCopy.getGrid(yPos, xPos + 1)->setVisited(true);
						xPos = xPos + 1;
						break;
					}
					//now determine the backtrack move
					switch (i) {
					case 0: //up
						currentMove = DOWN;
						break;
					case 1: //down
						currentMove = UP;
						break;
					case 2: //left
						currentMove = RIGHT;
						break;
					case 3: //right
						currentMove = LEFT;
						break;
					default:
						break;
					}
					backtrack.push(currentMove);
					break;
				}
			}
		}
		else if (nMoves == 0) { //no valid moves, backtrack
			if (backtrack.peek() == nullptr) { //all intersections visited, we are back at the exit
				if (!beginInter) {
					spawnKey(realMaze, mazeCopy, doors);
					exit = true;
				}
				else {
					xPos = mazeCopy.getxEnd();
					yPos = yPos - 1;
					beginInter = false;
				}
			}
			else {
				current = backtrack.pop();
				switch (current->getContents()) {
				case UP: //up
					yPos = yPos - 1;
					break;

				case DOWN: //down
					yPos = yPos + 1;
					break;

				case LEFT: //left
					xPos = xPos - 1;
					break;

				case RIGHT: //right
					xPos = xPos + 1;
					break;

				default:
					std::cout << "Backtrack Error!" << std::endl;
					assert(false);
				}//end switch
				break; //exit for loop, only 1 element can be true
			}
		}
	}
	return;
}

void Spawn::spawnKey(Maze* realMaze, Maze mazeCopy, Door* doors[3]) {
	int direction[4];
	int currentMove;
	int i;  //track how many moves we have tried
	int n = 0;//track number of moves performed in total
	bool exit = false;
	bool success;   //has a successful move been performed
	Stack backtrack;//stack to store moves needed to backtrack
	Link* current; //used to pop the stack
	Key* key = new Key;
	for (int i = 0; i < 3; i++) {
		doors[i]->setKey(key);
	}

	xPos = mazeCopy.getxStart();
	yPos = mazeCopy.getxStart();

	//determine what order to check directions in
	if (yPos < mazeCopy.getyEnd() && xPos < mazeCopy.getxEnd()) { //end is down and right of start
		direction[0] = DOWN;
		direction[1] = RIGHT;
		direction[2] = UP;
		direction[3] = LEFT;
	}
	else if (yPos < mazeCopy.getyEnd() && xPos > mazeCopy.getxEnd()) { //end is down and left of start
		direction[0] = DOWN;
		direction[1] = LEFT;
		direction[2] = UP;
		direction[3] = RIGHT;
	}
	else if (yPos > mazeCopy.getyEnd() && xPos < mazeCopy.getxEnd()) { //end is up and right of start
		direction[0] = UP;
		direction[1] = RIGHT;
		direction[2] = DOWN;
		direction[3] = RIGHT;
	}
	else if (yPos > mazeCopy.getyEnd() && xPos > mazeCopy.getxEnd()) { //end is up and left of start
		direction[0] = UP;
		direction[1] = LEFT;
		direction[2] = DOWN;
		direction[3] = RIGHT;
	}
	else {
		std::cout << "shit" << std::endl;
	}

	//set start to visited
	mazeCopy.getGrid(getyPos(), getxPos())->setVisited(true);

	//now solve the maze
	while (!exit) {
		success = false;
		i = 0;
		while (!success) {
			switch (direction[i]) {
			case UP: //up
				i++;
				if (mazeCopy.getGrid(yPos - 1, xPos)->getVisited() == false) {
					mazeCopy.getGrid(yPos - 1, xPos)->setVisited(true);
					yPos = yPos - 1;
					success = true;
					currentMove = UP;
					n++;
				}
				break;

			case DOWN: //down
				i++;
				if (mazeCopy.getGrid(yPos + 1, xPos)->getVisited() == false) {
					mazeCopy.getGrid(yPos + 1, xPos)->setVisited(true);
					yPos = yPos + 1;
					success = true;
					currentMove = DOWN;
					n++;
				}
				break;

			case LEFT: //left
				i++;
				if (mazeCopy.getGrid(yPos, xPos - 1)->getVisited() == false) {
					mazeCopy.getGrid(yPos, xPos - 1)->setVisited(true);
					xPos = xPos - 1;
					success = true;
					currentMove = LEFT;
					n++;
				}
				break;

			case RIGHT: //right
				i++;
				if (mazeCopy.getGrid(yPos, xPos + 1)->getVisited() == false) {
					mazeCopy.getGrid(yPos, xPos + 1)->setVisited(true);
					xPos = xPos + 1;
					success = true;
					currentMove = RIGHT;
					n++;
				}
				break;

			default:
				std::cout << "Moving Stuck!" << std::endl;
				assert(false);
				break;

			}//end switch
			if (success == false && i == 4) { //no available moves
				break; //exit while loop
			}
		}//end while

		if (success) {
			//determine the backtrack move
			switch (currentMove) {
			case UP:
				currentMove = DOWN;
				break;
			case DOWN:
				currentMove = UP;
				break;
			case LEFT:
				currentMove = RIGHT;
				break;
			case RIGHT:
				currentMove = LEFT;
				break;
			default:
				break;
			}
			backtrack.push(currentMove);
		}
		else {   //perform backtrack
			if (backtrack.peek() == nullptr) { //this shouldn't really ever happen
				assert(0 != 0);
			}
			else {
				current = backtrack.pop();
				switch (current->getContents()) {
				case UP: //up
					yPos = yPos - 1;
					break;
				case DOWN: //down
					yPos = yPos + 1;
					break;
				case LEFT: //left
					xPos = xPos - 1;
					break;
				case RIGHT: //right
					xPos = xPos + 1;
					break;
				default:
					std::cout << "Backtrack Error!" << std::endl;
					assert(false);
				}//end switch
			}//end if
		}

		if (n >= rows + cols) {  //end after this many moves
			//place the key at current pos
			realMaze->getGrid(getyPos(), getxPos())->setmyKey(key);
			realMaze->getGrid(getyPos(), getxPos())->setContents(keyIcon);
			exit = true;
		}
	}

	return;
}
