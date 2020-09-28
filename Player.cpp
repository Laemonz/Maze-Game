#include "Player.h"
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

Player::Player() : Being()  //also call Being's constructor
{
	playerKey = nullptr;
	win = false;
}

Player::~Player() {
	delete playerKey;
}

Key* Player::getplayerKey() {
	return playerKey;
}
void Player::setplayerKey(Key* newKey) {
	playerKey = newKey;
}

bool Player::getWin() {
	return win;
}
void Player::setWin(bool _win) {
	win = _win;
}

bool Player::checkKey(int _row, int _col, Maze* maze) {
	if (maze->getGrid(_row, _col)->getmyKey() != nullptr) { //player is on a key
		playerKey = maze->getGrid(_row, _col)->getmyKey();	//add key to player
		maze->getGrid(_row, _col)->setmyKey(nullptr);       //remove key from maze
		maze->getGrid(_row, _col)->setContents(BLANK);      //update char to BLANK
		return true;
	}
	return false;
}

bool Player::validMove(int _yOld, int _xOld, int _direction, Maze* maze) {
	switch (_direction) {
	case UP: //up
		_yOld = _yOld - 1;
		break;

	case DOWN: //down
		_yOld = _yOld + 1;
		break;

	case LEFT: //left
		_xOld = _xOld - 1;
		break;

	case RIGHT: //right
		_xOld = _xOld + 1;
		break;
	}
	if (maze->getGrid(_yOld, _xOld)->getVisited() == true) {
		return false;
	}

	if (maze->getGrid(_yOld, _xOld)->getContents() == BLANK) {
		return true;
	}
	else if (maze->getGrid(_yOld, _xOld)->getContents() == EXITICON) {
		return true;
	}
	else if (maze->getGrid(_yOld, _xOld)->getContents() == keyIcon) {
		checkKey(_yOld, _xOld, maze);
		return true;
	}
	else if (maze->getGrid(_yOld, _xOld)->getContents() == doorOpenIcon) {
		return true;
	}
	else if (maze->getGrid(_yOld, _xOld)->getContents() == doorClosedIcon) {   //closed door
		if (playerKey == maze->getGrid(_yOld, _xOld)->getmyDoor()->getKey()) { //the player has the key for this door
			maze->getGrid(_yOld, _xOld)->getmyDoor()->setIsOpen(true);      //set the door to open
			maze->updateGridContents(_yOld, _xOld, doorOpenIcon);           //update the maze visually
			return true;
		}
	}

	return false;
}

bool Player::movePlayer(Maze* maze) {
	switch (_getch()) {
	case KEY_UP:
	case 'w':   //up
		if (validMove(getyPos(), getxPos(), UP, maze)) {
			maze->moveIcon(getyPos(), getxPos(), UP, PLAYERICON, BLANK);
			setyPos(getyPos() - 1);
		}
		break;

	case KEY_DOWN:
	case 's':   //down
		if (validMove(getyPos(), getxPos(), DOWN, maze)) {
			maze->moveIcon(getyPos(), getxPos(), DOWN, PLAYERICON, BLANK);
			setyPos(getyPos() + 1);
		}
		break;

	case KEY_LEFT:
	case 'a':   //left
		if (validMove(getyPos(), getxPos(), LEFT, maze)) {
			maze->moveIcon(getyPos(), getxPos(), LEFT, PLAYERICON, BLANK);
			setxPos(getxPos() - 1);
		}
		break;

	case KEY_RIGHT:
	case 'd':   //right
		if (validMove(getyPos(), getxPos(), RIGHT, maze)) {
			maze->moveIcon(getyPos(), getxPos(), RIGHT, PLAYERICON, BLANK);
			setxPos(getxPos() + 1);
		}
		break;

	default: break;
	}

	if (getxPos() == maze->getxEnd() && getyPos() == maze->getyEnd()) {  //have we reached the end?
		win = true;
		return true;
	}
	return false;
}

void Player::solveMaze(Maze* maze, int _row, int _col) {
	int direction[4];
	int currentMove;
	int i;          //track how many moves we have tried
	bool exit = false;
	bool success;   //has a successful move been performed
	Stack backtrack;//stack to store moves needed to backtrack
	Link* current;	//used to pop the stack

	//determine what order to check directions in
	if (getyPos() <= _row && getxPos() <= _col) { //target is down and right of start
		direction[0] = DOWN;
		direction[1] = RIGHT;
		direction[2] = UP;
		direction[3] = LEFT;
	}
	else if (getyPos() < _row && getxPos() > _col) { //target is down and left of start
		direction[0] = DOWN;
		direction[1] = LEFT;
		direction[2] = UP;
		direction[3] = RIGHT;
	}
	else if (getyPos() > _row && getxPos() < _col) { //target is up and right of start
		direction[0] = UP;
		direction[1] = RIGHT;
		direction[2] = DOWN;
		direction[3] = RIGHT;
	}
	else if (getyPos() > _row && getxPos() > _col) { //target is up and left of start
		direction[0] = UP;
		direction[1] = LEFT;
		direction[2] = DOWN;
		direction[3] = RIGHT;
	}
	else {

	}

	//set start to visited
	maze->getGrid(getyPos(), getxPos())->setVisited(true);

	//now solve the maze
	while (!exit) {
		success = false;
		i = 0;
		while (!success) {
			switch (direction[i]) {
			case UP: //up
				i++;
				if (validMove(getyPos(), getxPos(), UP, maze)) {
					maze->getGrid(getyPos() - 1, getxPos())->setVisited(true);
					maze->moveIcon(getyPos(), getxPos(), UP, PLAYERICON, BLANK);
					setyPos(getyPos() - 1);
					success = true;
					currentMove = UP;
				}
				break;

			case DOWN: //down
				i++;
				if (validMove(getyPos(), getxPos(), DOWN, maze)) {
					maze->getGrid(getyPos() + 1, getxPos())->setVisited(true);
					maze->moveIcon(getyPos(), getxPos(), DOWN, PLAYERICON, BLANK);
					setyPos(getyPos() + 1);
					success = true;
					currentMove = DOWN;
				}
				break;

			case LEFT: //left
				i++;
				if (validMove(getyPos(), getxPos(), LEFT, maze)) {
					maze->getGrid(getyPos(), getxPos() - 1)->setVisited(true);
					maze->moveIcon(getyPos(), getxPos(), LEFT, PLAYERICON, BLANK);
					setxPos(getxPos() - 1);
					success = true;
					currentMove = LEFT;
				}
				break;

			case RIGHT: //right
				i++;
				if (validMove(getyPos(), getxPos(), RIGHT, maze)) {
					maze->getGrid(getyPos(), getxPos() + 1)->setVisited(true);
					maze->moveIcon(getyPos(), getxPos(), RIGHT, PLAYERICON, BLANK);
					setxPos(getxPos() + 1);
					success = true;
					currentMove = RIGHT;

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
		maze->sleep(50);

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
				system("CLS");
				maze->printMaze();
				std::cout << "All cells have been visited!" << std::endl;
				exit = true;
			}
			else {
				current = backtrack.pop();
				switch (current->getContents()) {
				case UP: //up
					maze->moveIcon(getyPos(), getxPos(), UP, PLAYERICON, BLANK);
					setyPos(getyPos() - 1);
					break;

				case DOWN: //down
					maze->moveIcon(getyPos(), getxPos(), DOWN, PLAYERICON, BLANK);
					setyPos(getyPos() + 1);
					break;

				case LEFT: //left
					maze->moveIcon(getyPos(), getxPos(), LEFT, PLAYERICON, BLANK);
					setxPos(getxPos() - 1);
					break;

				case RIGHT: //right
					maze->moveIcon(getyPos(), getxPos(), RIGHT, PLAYERICON, BLANK);
					setxPos(getxPos() + 1);
					break;

				default:
					std::cout << "Backtrack Error!" << std::endl;
					assert(false);
				}//end switch
			}//end if

		}

		if (getxPos() == _col && getyPos() == _row) {  //have we reached the desired location
			exit = true;
		}
	}

}
