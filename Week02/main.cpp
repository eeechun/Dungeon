/************************************************************************
File:   Source.cpp

Author:
		ªô¹Å¿³¡Atbcey74123@gmail.com
Comment:
		Output character position after W,A,S,D input.
		Output invalid if destination out of boundary.
		ESC to stop process.

************************************************************************/
#include <iostream>	// For print out information
#include <conio.h>	// For getch() function

bool tryMove(int deltaX, int deltaY);
bool checkValidDst(int x, int y);

int posX = 0, posY = 0; // global param to keep the character position
const int DUNGEN_SIZE = 5; // For each dimension, -DUNGEN_SIZE < pos < DUNGEN_SIZE

int main() {
	// Obtain and update the input using a loop
	while (true) {
		char input = _getch();

		/************************************************************************/
		/*Please implement your code here*/

		int deltaX = 0, deltaY = 0;
		switch (input)
		{
		case 'W':
			deltaY = 1;
			break;
		case 'w':
			deltaY = 1;
			break;
		case 'S':
			deltaY = -1;
			break;
		case 's':
			deltaY = -1;
			break;
		case 'A':
			deltaX = -1;
			break;
		case 'a':
			deltaX = -1;
			break;
		case 'D':
			deltaX = 1;
			break;
		case 'd':
			deltaX = 1;
			break;
		default:
			break;
		}

		if (tryMove(deltaX, deltaY) == true)
		{
			posX += deltaX;
			posY += deltaY;
		}
		else
		{
			std::cout << "Failed to move\n";
		}
		std::cout << "Character position: (" << posX << "," << posY << ")\n";

		/************************************************************************/
	}
}

//******************************************************************
//
// * Move character with input delta, return true if successful otherwise false
//==================================================================
bool tryMove(int deltaX, int deltaY) {
	/************************************************************************/
	/*Please implement your code here*/

	int tempX = posX + deltaX;
	int tempY = posY + deltaY;
	if (checkValidDst(tempX, tempY) == true)
	{
		return true;
	}
	else
	{
		return false;
	}

	/************************************************************************/
}
//******************************************************************
//
// * Check if given position is a valid destination, return true if valid otherwise false
//==================================================================
bool checkValidDst(int x, int y) {
	/************************************************************************/
	/*Please implement your code here*/

	if (x >= DUNGEN_SIZE || x <= -DUNGEN_SIZE || y >= DUNGEN_SIZE || y <= -DUNGEN_SIZE)
	{
		return false;
	}
	else
	{
		return true;
	}

	/************************************************************************/
}
