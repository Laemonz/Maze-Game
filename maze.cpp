#include "Maze.h"

Maze::Maze() {
	for (int i = 0; i < 4; i++) {
		moves[i] = i;
	}

	xStart = 0;
	yStart = 0;

	for (int i = 0; i < 3; i++) {
		doors[i] = new Door;
	}

	xEnd = 1;
	yEnd = 1;

	//rows and cols must be odd
	if (rows % 2 == 0) {
		std::cout << "Rows cannot be even!" << std::endl;
		assert(rows % 2 != 0);
	}
	if (cols % 2 == 0) {
		std::cout << "Cols cannot be even!" << std::endl;
		assert(cols % 2 != 0);
	}
}

Maze::~Maze() {
	//    delete grid;
	//    for(int i=0; i<3; i++){
	//        delete doors[i];
	//    }
}

int Maze::getxStart() {
	return xStart;
}
void Maze::setxStart(int _x) {
	xStart = _x;
}

int Maze::getyStart() {
	return yStart;
}
void Maze::setyStart(int _y) {
	yStart = _y;
}

int Maze::getxEnd() {
	return xEnd;
}
void Maze::setxEnd(int _x) {
	xEnd = _x;
}

int Maze::getyEnd() {
	return yEnd;
}
void Maze::setyEnd(int _y) {
	yEnd = _y;
}

Cell* Maze::getGrid(int _row, int _col) {
	return &grid[_row][_col];
}

Door* Maze::getDoor(int _i) {
	return doors[_i];
}

void Maze::sleep(int _miliseconds) {
	std::this_thread::sleep_for(std::chrono::milliseconds(_miliseconds));
}

void Maze::setCursorPosition(int _col, int _row) { //origin==top left
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();  //clear buffer
	COORD coord = { (SHORT)_col, (SHORT)_row };   //create coord
	SetConsoleCursorPosition(hConsole, coord);  //set cursor to desired position
}

void Maze::showConsoleCursor(bool show) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = show; //hide or show cursor
	SetConsoleCursorInfo(out, &cursorInfo);
}

void Maze::shuffleArray(int myArray[]) {
	int temp, rand1, rand2;
	for (int i = 0; i < 10; i++) {
		rand1 = rand() % 4;
		rand2 = rand() % 4;

		temp = myArray[rand1];
		myArray[rand1] = myArray[rand2];
		myArray[rand2] = temp;
	}
	return;
}

void Maze::generateMaze() {
	//fill maze with WALLs and reset properties
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			grid[i][j].setContents(WALL);
			grid[i][j].setVisited(true);
			grid[i][j].setmyDoor(nullptr);
			grid[i][j].setmyKey(nullptr);
		}
	}
	//set starting point
	grid[yStart][xStart].setContents(BLANK);
	grid[yStart][xStart].setVisited(false);
	printMaze();

	//call recursive function to generate maze
	buildMaze(yStart, xStart);

	return;
}

void Maze::buildMaze(int y, int x) {
	shuffleArray(moves);    //shuffle the moves
	sleep(10);
	for (int i = 0; i < 4; i++) {
		switch (moves[i]) {
		case UP: //up
			//is 2 cells up out of bounds
			if (y - 2 <= 0) {
				continue;
			}
			else if (grid[y - 2][x].getContents() != BLANK) {
				updateGridContents(y - 2, x, BLANK);
				grid[y - 2][x].setVisited(false);
				updateGridContents(y - 1, x, BLANK);
				grid[y - 1][x].setVisited(false);
				buildMaze(y - 2, x);
			}
			break;

		case DOWN: //down
			//is 2 cells down out of bounds
			if (y + 2 >= rows) {
				continue;
			}
			else if (grid[y + 2][x].getContents() != BLANK) {
				updateGridContents(y + 2, x, BLANK);
				grid[y + 2][x].setVisited(false);
				updateGridContents(y + 1, x, BLANK);
				grid[y + 1][x].setVisited(false);
				buildMaze(y + 2, x);
			}
			break;

		case LEFT: //left
			//is 2 cells left out of bounds
			if (x - 2 <= 0) {
				continue;
			}
			else if (grid[y][x - 2].getContents() != BLANK) {
				updateGridContents(y, x - 2, BLANK);
				grid[y][x - 2].setVisited(false);
				updateGridContents(y, x - 1, BLANK);
				grid[y][x - 1].setVisited(false);
				buildMaze(y, x - 2);
			}
			break;

		case RIGHT: //right
			//is 2 cells right out of bounds
			if (x + 2 >= cols) {
				continue;
			}
			else if (grid[y][x + 2].getContents() != BLANK) {
				updateGridContents(y, x + 2, BLANK);
				grid[y][x + 2].setVisited(false);
				updateGridContents(y, x + 1, BLANK);
				grid[y][x + 1].setVisited(false);
				buildMaze(y, x + 2);
			}
			break;
		}
	}

	if (rand() % nRand == nRand - 1) {  //chance to break a WALL and make a loop
		switch (moves[rand() % 4]) {
		case UP: //up
			if (y - 2 <= 0) {
				break;
			}
			else if (grid[y - 2][x].getContents() == BLANK) {
				//updateGridContents(y-2, x, BLANK);
				updateGridContents(y - 1, x, BLANK);
				grid[y - 1][x].setVisited(false);
			}
			break;

		case DOWN: //down
			if (y + 2 >= rows) {
				break;
			}
			else if (grid[y + 2][x].getContents() == BLANK) {
				//updateGridContents(y+2, x, BLANK);
				updateGridContents(y + 1, x, BLANK);
				grid[y + 1][x].setVisited(false);
			}
			break;

		case LEFT: //left
			if (x - 2 <= 0) {
				break;
			}
			else if (grid[y][x - 2].getContents() == BLANK) {
				//updateGridContents(y, x-2, BLANK);
				updateGridContents(y, x - 1, BLANK);
				grid[y][x - 1].setVisited(false);
			}
			break;

		case RIGHT: //right
			if (x + 2 >= cols) {
				break;
			}
			else if (grid[y][x + 2].getContents() == BLANK) {
				//updateGridContents(y, x+2, BLANK);
				updateGridContents(y, x + 1, BLANK);
				grid[y][x + 1].setVisited(false);
			}
			break;
		}

	}
	return;
}

void Maze::printMaze() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cout << grid[i][j].getContents();
		}
		std::cout << std::endl;
	}
}

void Maze::updateGridContents(int _row, int _col, char _content) {
	grid[_row][_col].setContents(_content);
	setCursorPosition(_col, _row);
	std::cout << _content;
}

char Maze::checkGridContents(int y, int x, int direction) {
	switch (direction) {
	case UP:
		return grid[y - 1][x].getContents();
		break;
	case DOWN:
		return grid[y + 1][x].getContents();
		break;
	case LEFT:
		return grid[y][x - 1].getContents();
		break;
	case RIGHT:
		return grid[y][x + 1].getContents();
		break;
	default:
		return 0;
		break;
	}
}

void Maze::moveIcon(int _yOld, int _xOld, int _direction, char _icon, char _oldIcon) {
	switch (_direction) {
	case UP: //up
		updateGridContents(_yOld, _xOld, _oldIcon);
		updateGridContents(_yOld - 1, _xOld, _icon);
		break;

	case DOWN: //down
		updateGridContents(_yOld, _xOld, _oldIcon);
		updateGridContents(_yOld + 1, _xOld, _icon);
		break;

	case LEFT: //left
		updateGridContents(_yOld, _xOld, _oldIcon);
		updateGridContents(_yOld, _xOld - 1, _icon);
		break;

	case RIGHT: //right
		updateGridContents(_yOld, _xOld, _oldIcon);
		updateGridContents(_yOld, _xOld + 1, _icon);
		break;
	default:
		break;
	}
}

void Maze::resetVisited(bool _value) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (grid[i][j].getContents() != WALL) {
				grid[i][j].setVisited(false);
			}
		}
	}

}

void Maze::spawnDoors() {
	int direction[4] = { DOWN, RIGHT, UP, LEFT };
	int currentMove;
	int nMoves;     //track how many moves we have tried
	int d = 0;        //amount of doors that have been placed
	int xPos = xEnd;
	int yPos = yEnd;
	bool exit = false;
	bool moves[4];
	bool beginInter = false;  //is the beginning an intersection
	Stack backtrack;//stack to store moves needed to backtrack
	Link* current; //used to pop the stack

	//set end to visited
	grid[xPos][yPos].setVisited(true);

	while (!exit) {
		nMoves = 0;
		for (int i = 0; i < 4; i++) {
			moves[i] = false;
		}
		//find number of valid moves
		for (int i = 0; i < 4; i++) {
			switch (direction[i]) {
			case UP: //up
				if (grid[yPos - 1][xPos].getVisited() == false) {
					nMoves++;
					moves[0] = true;
				}
				break;

			case DOWN: //down
				if (grid[yPos + 1][xPos].getVisited() == false) {
					nMoves++;
					moves[1] = true;
				}
				break;

			case LEFT: //left
				if (grid[yPos][xPos - 1].getVisited() == false) {
					nMoves++;
					moves[2] = true;
				}
				break;

			case RIGHT: //right
				if (grid[yPos][xPos + 1].getVisited() == false) {
					nMoves++;
					moves[3] = true;
				}
				break;

			}//end switch
		}
		if ((xPos == xEnd && yPos == yEnd) && (nMoves > 1)) { //begining is an intersection
			beginInter = true;
			xPos = xPos + 1;    //deal with the right hallway first
			yPos = yEnd;
			grid[xPos][yPos].setVisited(true);
		}
		else if (nMoves > 1) {   //we have reached an intersection
			//place door at current pos
			grid[yPos][xPos].setmyDoor(doors[d]);
			updateGridContents(yPos, xPos, doorClosedIcon);
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
			}
		}
		else if (nMoves == 1) { //we are in a hallway, keep moving
			for (int i = 0; i < 4; i++) {
				if (moves[i] == true) {
					switch (i) {
					case 0: //up
						grid[yPos - 1][xPos].setVisited(true);
						yPos = yPos - 1;
						break;

					case 1: //down
						grid[yPos + 1][xPos].setVisited(true);
						yPos = yPos + 1;
						break;

					case 2: //left
						grid[yPos][xPos - 1].setVisited(true);
						xPos = xPos - 1;
						break;

					case 3: //right
						grid[yPos][xPos + 1].setVisited(true);
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
					exit = true;
				}
				else {
					xPos = xEnd;
					yPos = yPos + 1;
					grid[xPos][yPos].setVisited(true);
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

Key* Maze::spawnKey(int _nMoves) {
	int direction[4];
	int currentMove;
	int i;  //track how many moves we have tried
	int n = 0;//track number of moves performed in total
	int xPos = xStart;
	int yPos = yStart;

	bool exit = false;
	bool success;   //has a successful move been performed
	Stack backtrack;//stack to store moves needed to backtrack
	Link* current; //used to pop the stack
	Key* key = new Key;
	for (int i = 0; i < 3; i++) {
		doors[i]->setKey(key);
	}

	//determine what order to check directions in
	if (yPos < yEnd && xPos < xEnd) { //end is down and right of start
		direction[0] = DOWN;
		direction[1] = RIGHT;
		direction[2] = UP;
		direction[3] = LEFT;
	}
	else if (yPos < yEnd && xPos > xEnd) { //end is down and left of start
		direction[0] = DOWN;
		direction[1] = LEFT;
		direction[2] = UP;
		direction[3] = RIGHT;
	}
	else if (yPos > yEnd && xPos < xEnd) { //end is up and right of start
		direction[0] = UP;
		direction[1] = RIGHT;
		direction[2] = DOWN;
		direction[3] = RIGHT;
	}
	else if (yPos > yEnd && xPos > xEnd) { //end is up and left of start
		direction[0] = UP;
		direction[1] = LEFT;
		direction[2] = DOWN;
		direction[3] = RIGHT;
	}
	else {

	}

	//set start to visited
	grid[yPos][xPos].setVisited(true);

	//now solve the maze
	while (!exit) {
		success = false;
		i = 0;
		while (!success) {
			switch (direction[i]) {
			case UP: //up
				i++;
				if (grid[yPos - 1][xPos].getVisited() == false) {
					grid[yPos - 1][xPos].setVisited(true);
					yPos = yPos - 1;
					success = true;
					currentMove = UP;
					n++;
				}
				break;

			case DOWN: //down
				i++;
				if (grid[yPos + 1][xPos].getVisited() == false) {
					grid[yPos + 1][xPos].setVisited(true);
					yPos = yPos + 1;
					success = true;
					currentMove = DOWN;
					n++;
				}
				break;

			case LEFT: //left
				i++;
				if (grid[yPos][xPos - 1].getVisited() == false) {
					grid[yPos][xPos - 1].setVisited(true);
					xPos = xPos - 1;
					success = true;
					currentMove = LEFT;
					n++;
				}
				break;

			case RIGHT: //right
				i++;
				if (grid[yPos][xPos + 1].getVisited() == false) {
					grid[yPos][xPos + 1].setVisited(true);
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

		if (n == _nMoves) {  //end after this many moves
			//place the key at current pos
			key->setxPos(xPos);
			key->setyPos(yPos);
			grid[yPos][xPos].setmyKey(key);
			grid[yPos][xPos].setContents(keyIcon);
			exit = true;

		}
	}

	return key;
}
