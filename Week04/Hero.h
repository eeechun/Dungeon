/***********************************************************************
 * File: Hero.h
 * Author: ¾G¨Ì²E
 * Create Date: 2024/03/12
 * Editor: ¾G¨Ì²E
 * Update Date: 2024/03/12
 * Description: This header file is to declare hero class.
***********************************************************************/

#pragma once
#include <string>
#include "Position.h"
#include "Functions.h"

class Hero {
private:
	Position	sPos;			// Hero location
	char sIcon = 'H';	// Hero icon

public:
	// Default constructor
	Hero() {
		this->sPos.x = 0;
		this->sPos.y = 0;
		this->sIcon = 'H';
	};

	// Set position
	void setPos(Position pos) { this->sPos = pos; }
	void setPos(int x, int y) {
		this->sPos.x = x;
		this->sPos.y = y;
	}

	// Set icon
	void setIcon(char& icon) { this->sIcon = icon; }

	// Get position
	Position getPos(void) { return this->sPos; }

	// Get Icon
	char getIcon(void) { return this->sIcon; }

	// Intent: Incrementally move the hero.
	// Pre: Hero cannot move.
	// Post: The position of hero will change according to the input.
	void move(int deltaX, int deltaY) {
		Position temp = this->sPos;
		temp.x += deltaX;
		temp.y += deltaY;
		if (isPositionValid(temp) == true)
		{
			this->sPos.x += deltaX;
			this->sPos.y += deltaY;
		}
		else
		{
			std::cout << "Invalid position.\n";
		}
	}
};
