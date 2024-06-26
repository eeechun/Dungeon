/************************************************************************
File:   Source.cpp

Author:
		Áé½å¼s¡Aea5878158@gmail.com
Modifier:
		¿à¯§¦N¡Acheeryuchi@gmail.com
		ÅU°ßÄ£¡Aguweiyao867@gmail.com
		³¯«T¦t¡AJYCReports@gmail.com
		ªô¹Å¿³¡Atbcey74123@gmail.com
Comment:
		Draw and print out the canvas.

************************************************************************/

#include <iostream>
#include <stdio.h>
using namespace std;

void drawBoard(); //Function to draw board
void makeBoard(); //Function to make board
void modifyBoard();	//Function to modify board

const int DUNGEN_ROW = 10, DUNGEN_COL = 20;
char dungenMap[DUNGEN_ROW][DUNGEN_COL];

int main(int argc, char** argv)
{
	makeBoard();
	drawBoard();
	modifyBoard();
	drawBoard();
}

void drawBoard()
//==================================================================
{
	// Draw out the whole board
	/************************************************************************/
	/*Please implement your code here*/

	int row, col;
	for (row = 0; row < DUNGEN_ROW; row++)
	{
		for (col = 0; col < DUNGEN_COL; col++)
		{
			std::cout << dungenMap[row][col];
		}
		std::cout << "\n";
	}
	std::cout << "\n";
	/************************************************************************/
}

void makeBoard()
//==================================================================
{
	// Enter symbol for wall and blank then create array
	/************************************************************************/
	/*Please implement your code here*/
	
	char wall, blank;
	int col, row;

	std::cout << "Enter symbol for wall: ";
	std::cin >> wall;
	std::cout << "Enter symbol for blank: ";
	std::cin >> blank;

	// top-bottom wall
	for (col = 0; col < 20; col++)
	{
		dungenMap[0][col] = wall;
		dungenMap[9][col] = wall;
	}

	// left-right wall
	for (row = 0; row < 9; row++)
	{
		dungenMap[row][0] = wall;
		dungenMap[row][19] = wall;
	}

	// blank
	for (row = 1; row < 9; row++)
	{
		for (col = 1; col < 19; col++)
		{
			dungenMap[row][col] = blank;
		}
	}

	/************************************************************************/
}

void modifyBoard()
//==================================================================
{
	// Function for modifying board given position and char to change
	/************************************************************************/
	/*Please implement your code here*/

	char c;
	int x = 0, y = 0;

	std::cout << "Enter symbol for modifying position: ";
	std::cin >> c;
	std::cout << "Enter X of modifying position: ";
	std::cin >> x;
	std::cout << "Enter Y of modifying position: ";
	std::cin >> y;

	if (x >= 20 || y >= 10 || x < 0 || y < 0)
	{
		std::cout << "Invalid input\n";
	}
	else
	{
		dungenMap[y][x] = c;
	}

	/************************************************************************/
}