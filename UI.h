#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include <conio.h>  //getch()

#define KEY_UP 72
#define KEY_DOWN 80


int checkIntInput(int, int);						//function to check that integer input is within a desired range
int selectCommand(std::string, std::string[], int);	//display a menu with options and let the user select an option
void chooseColour();								//change the colour of the console
void chooseDifficulty(Monster*);					//choose how fast the monster moves
void displayHelp();									//display infromation about the game


int checkIntInput(int minValue, int maxValue) {
	bool exit = false;
	int userInput;

	do {
		userInput = minValue - 1;
		std::cin >> userInput;
		if (std::cin.fail()) {				//input is not an integer
			std::cout << "Invalid input! Please enter an integer!" << std::endl;
			std::cin.clear();				//reset error flags
			std::cin.ignore(1000, '\n');	//ignore input stream
		}
		else if ((userInput > maxValue) || (userInput < minValue)) { //not in desired range
			std::cout << "Invalid Input! Please input an integer between " << minValue << " and " << maxValue << "." << std::endl;
		}
		else {
			exit = true;
		}
	} while (!exit);
	return userInput; //return input when coniditons are met
}

int selectCommand(std::string _text, std::string options[], int _arrSize) {
	char cursor = '0';
	int n = 0;
	bool choice = 0;

	//dynamically allocate 2D array
	std::string** menu = new std::string * [_arrSize];	//double pointer points to new array of _arrSize length
	for (int i = 0; i < arrSize; i++) {
		menu[i] = new std::string[3];					//each element in the array points to an array containing 3 strings
	}
	// assign text values into menu
	for (int i = 0; i < arrSize; i++) {
		menu[i][1] = options[i];
	}

	while (!choice) {
		std::cout << _text << std::endl;
		for (int i = 0; i < arrSize; i++) {	//reset arrows to blanks
			menu[i][0] = " ";
			menu[i][2] = " ";
		}
		//add arrows around current item
		menu[n][0] = '>';
		menu[n][2] = '<';
		for (int i = 0; i < arrSize; i++) {
			for (int j = 0; j < 3; j++) {
				std::cout << menu[i][j];
			}
			std::cout << std::endl;
		}

		cursor = _getch();
		switch (cursor) {
		case KEY_UP:
		case 'w':
			if (n == 0) {  //already at top
				n = arrSize - 1;
			}
			else {
				n--;
			}
			break;

		case KEY_DOWN:
		case 's':
			if (n == arrSize - 1) {   //already at bottom
				n = 0;
			}
			else {
				n++;
			}
			break;

		case '\r':  //enter
			choice = true;
			break;

		}
		system("CLS");
	}

	//deallocate array
	for (int i = 0; i < arrSize; i++)
		delete[] menu[i];
	delete[] menu;

	return n;
}

void chooseColour() {
	std::string colours[8] = { "Blue", "Green", "Aqua", "Red", "Purple", "Yellow", "White", "Gray" };
	int m = selectCommand("Please choose a colour.", colours, 8);

	switch (m) {
	case 0:
		system("COLOR 01");
		break;
	case 1:
		system("COLOR 02");
		break;
	case 2:
		system("COLOR 03");
		break;
	case 3:
		system("COLOR 04");
		break;
	case 4:
		system("COLOR 05");
		break;
	case 5:
		system("COLOR 06");
		break;
	case 6:
		system("COLOR 07");
		break;
	case 7:
		system("COLOR 08");
		break;
	}
}

void chooseDifficulty(Monster* monster) {
	std::string difficulty[3] = { "Easy", "Medium", "Hard" };
	int m = selectCommand("Please choose a difficulty level for the monster", difficulty, 3);

	switch (m) {
	case 0: //ez
		monster->setChaseSpeed(EASY);
		break;
	case 1: //med
		monster->setChaseSpeed(MEDIUM);
		break;
	case 2: //hard
		monster->setChaseSpeed(HARD);
		break;
	}
}

void displayHelp() {
	system("CLS");
	std::cout << "In this game you control a player who must navigate through a maze while avoid the monster." << std::endl;
	system("PAUSE");

	std::cout << "LEGEND:" << std::endl;
	std::cout << WALL << " - WALL" << std::endl;
	std::cout << PLAYERICON << " - Player" << std::endl;
	std::cout << EXITICON << " - Exit" << std::endl;
	std::cout << doorClosedIcon << " - Closed Door" << std::endl;
	std::cout << doorOpenIcon << " - Open Door" << std::endl;
	std::cout << keyIcon << " - Key" << std::endl;
	std::cout << monsterIcon << " - Monster" << std::endl;

	system("PAUSE");
	system("CLS");
}
#endif // UI_H_INCLUDED
