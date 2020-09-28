#include "Monster.h"

Monster::Monster() : Being()  //also call Being's constructor
{
	setxPos(2);
	setyPos(2);
	chaseSpeed = MEDIUM;
}

Monster::~Monster() {
	//dtor
}

int Monster::getChaseSpeed() {
	return chaseSpeed;
}
void Monster::setChaseSpeed(int _ms) {
	chaseSpeed = _ms;
}

void Monster::placeMonster(Maze* maze, int y, int x) {
		//we must place the monster on a BLANK to start
		if (maze->getGrid(y, x)->getContents() == BLANK) {
			setxPos(y);
			setyPos(x);
		}
		else if (maze->checkGridContents(y, x, UP) == BLANK) {
			setxPos(y - 1);
			setyPos(x);
		}
		else if (maze->checkGridContents(y, x, DOWN) == BLANK) {
			setxPos(y + 1);
			setyPos(x);
		}
		else if (maze->checkGridContents(y, x, LEFT) == BLANK) {
			setxPos(y);
			setyPos(x - 1);
		}
		else if (maze->checkGridContents(y, x, RIGHT) == BLANK) {
			setxPos(y);
			setyPos(x + 1);
		}

}


void Monster::chasePlayerSpooky(Maze* maze, Player* player) {
	int direction, h, v;
	bool fast = false;      //move the monster faster if it is far from the player
	char oldCell;           //what to update the old cell's contents to
	char nextCell = BLANK;  //what the next cell's contents are
							//monster will start on a BLANK cell

	while (player->getHealth() > 0 && player->getWin() == false) {

		//determine where to move
		h = std::fabs(getxPos() - player->getxPos());
		v = std::fabs(getyPos() - player->getyPos());
		if (h > v) { //horiz distance is bigger
			if (getxPos() < player->getxPos()) { //player is to the right
				direction = RIGHT;
			}
			else { //player is to the left
				direction = LEFT;
			}
			if (h >= FAST) { //monster is far away
				fast = true;
			}
		}
		else { //vert distance is smaller or equal

			if (getyPos() < player->getyPos()) { //player is below
				direction = DOWN;
			}
			else {   //player is above
				direction = UP;
			}
			if (v >= FAST) { //monster is far away
				fast = true;
			}
		}

		//move the monster
		oldCell = nextCell;
		nextCell = maze->checkGridContents(getyPos(), getxPos(), direction);    //determine what the the next cell's contents are
		maze->moveIcon(getyPos(), getxPos(), direction, monsterIcon, oldCell);  //determine what the next cell's contents will be
		switch (direction) {
		case UP:
			setyPos(getyPos() - 1);
			break;
		case DOWN:
			setyPos(getyPos() + 1);
			break;
		case LEFT:
			setxPos(getxPos() - 1);
			break;
		case RIGHT:
			setxPos(getxPos() + 1);
			break;
		default:
			break;
		}

		//now check if we have caught the player
		if (player->getxPos() == getxPos() && player->getyPos() == getyPos()) {
			player->setHealth(0);
		}
		if (fast) {
			std::this_thread::sleep_for(std::chrono::milliseconds(chaseSpeed / 2));
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(chaseSpeed));
		}

	}

}
