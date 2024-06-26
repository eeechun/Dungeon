/***********************************************************************
 * File: Functions.cpp
 * Author: 鄭依淳
 * Create Date: 2024/03/12
 * Editor: 鄭依淳
 * Update Date: 2024/03/12
 * Description: This header file is to define functions used in the project.
***********************************************************************/

#include <iostream>
#include "Functions.h"
#include "Creature.h"
#include "Hero.h"
#include "Position.h"

// Intent: generate random number to decide where to move
// Pre: object not moved
// Post: 0 for up, 1 for down, 2 for left, 3 for right
int genRandom()
{
	return rand() % 4;
}

// Intent: Set up the original baord.
// Pre: Game board not set.
// Post: Game board set with given size.
void setupBoard()
{
	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			if (i == 0 || i == GHEIGHT - 1) {
				gBoard[i][j] = GWALL;
			}
			else if (j == 0 || j == GWIDTH - 1) {
				gBoard[i][j] = GWALL;
			}
			else {
				gBoard[i][j] = GNOTHING;
			}
		}
	}
}

// Intent: Determine if the position is empty for obect to move to.
// Pre: Object may move outside the board.
// Post: Check if the position is empty before moving.
bool isPositionValid(Position& pos)
{
	// Check whether it is an empty space
	if (gBoard[pos.y][pos.x] != GNOTHING)
		return false;

	if (pos.x == gHero.getPos().x && pos.y == gHero.getPos().y)
		return false;

	if (pos.x == gCreature.getPos().x && pos.y == gCreature.getPos().y)
		return false;

	return true;
}

// Intent: Draw the board.
// Pre: Nothing showed on the screen.
// Post: Game board and objects showed.
void draw()
{
	// Add the hero into the board
	char drawBoard[GHEIGHT][GWIDTH];

	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			drawBoard[i][j] = gBoard[i][j];
		}
	}

	// Update the hero information
	Position h = gHero.getPos();
	drawBoard[h.y][h.x] = gHero.getIcon();

	Position c = gCreature.getPos();
	drawBoard[c.y][c.x] = gCreature.getIcon();

	// Draw the board
	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			std::cout << drawBoard[i][j]; //  output
		}
		std::cout << "\n";
	}
}

//Intent: Detect input key.
// Pre: No changes while entering the key.
// Post: Move object according to the input key.
void keyUpdate(bool key[])
{
	for (int i = 0; i < ValidInput::INVALID; i++) {
		key[i] = false;
	}
	char input = _getch();
	switch (input) {
	case 'w':
		key[ValidInput::EW] = true;
		break;
	case 's':
		key[ValidInput::ES] = true;
		break;
	case 'a':
		key[ValidInput::EA] = true;
		break;
	case 'd':
		key[ValidInput::ED] = true;
		break;
	case ' ':
		key[ValidInput::ESPACE] = true;
		break;
	case 27:
		key[ValidInput::EESC] = true;
		break;
	default:
		break;
	}
}

//******************************************************************
//
// * clip algroithm
//==================================================================
float clip(float n, float minimun, float maximum)
//==================================================================
{
	return std::max(minimun, std::min(n, maximum));
}

// Intent: Print outputs and information.
// Pre: No outputs and information.
// Post: Print outputs and information.
void drawInfo(void)
{
	// Print Outputs
	/*Please implement your code here*/

	std::cout << "Hero position: (" << gHero.getPos().x << ", " << gHero.getPos().y << ")\n";
	std::cout << "Creature position: (" << gCreature.getPos().x << ", " << gCreature.getPos().y << ")\n";
	if (gCreature.flag == 1)
	{
		std::cout << "Creature has find the Hero in the ( " << gHero.getPos().x - gCreature.getPos().x << ", " << gHero.getPos().y - gCreature.getPos().y << " ) direction\n";
	}
	else
	{
		std::cout << "Creature didn't find the Hero\n";
	}

	/************************************************************************/

	std::cout << "Use wsad key to move Hero " << gHero.getIcon() << std::endl;
	std::cout << "Press ESC key to exit" << std::endl;
}

// Intent: Update the board.
// Pre: Board not updated after actions.
// Post: Board will update after any actions.
void update(bool key[])
{
	// 清除版面
	system("CLS");

	// 是否有input
	bool hasInput = false;
	if (key[ValidInput::EW]) {
		gHero.move(0, -1);
		hasInput = true;
	}
	else if (key[ValidInput::ES]) {
		gHero.move(0, 1);
		hasInput = true;
	}
	else if (key[ValidInput::EA]) {
		gHero.move(-1, 0);
		hasInput = true;
	}
	else if (key[ValidInput::ED]) {
		gHero.move(1, 0);
		hasInput = true;
	}
	else {
		std::cout << "invalid input\n";
	}
	//Calculate and Initiate Move
	gCreature.update(gHero.getPos());
	draw();
	drawInfo();
}