/***********************************************************************
 * File: Creature.h
 * Author: �G�̲E
 * Create Date: 2024/03/12
 * Editor: �G�̲E
 * Update Date: 2024/03/12
 * Description: This header file is to define creature class.
***********************************************************************/

#pragma once
#include <iostream>
#include <string>
#include "Position.h"
#include "Functions.h"

class Creature {

	// Implement Creature Class
	/*Please implement your code here*/
private:
	Position	sPos;			// Creature location
	char sIcon = 'C';	// Creature icon

public:
	// Default constructor
	Creature() {
		this->sPos.x = 0;
		this->sPos.y = 0;
		this->sIcon = 'C';
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

	// if creature can see hero, flag = 1; else = 0
	int flag = 1;

	// Intent: Update Creature's position according to Hero
	// Pre: Creature cannot move.
	// Post: Creature can move according to Hero's position
	void update(Position pos) {
		/*Please implement your code here*/
		// hero��creature���Z���t�Z
		int delX = pos.x - this->getPos().x;
		int delY = pos.y - this->getPos().y;

		// Hero�b�k�W 
		if (delX > 0 && delX <= 3 && delY > 0 && delY <= 3)
		{
			flag = 1;
			this->sPos.x += 1;
			this->sPos.y += 1;
		}
		// Hero�b�k�U
		else if (delX > 0 && delX <= 3 && delY < 0 && delY >= -3)
		{
			flag = 1;
			this->sPos.x += 1;
			this->sPos.y -= 1;
		}
		// Hero�b���U
		else if (delX < 0 && delX >= -3 && delY < 0 && delY >= -3)
		{
			flag = 1;
			this->sPos.x -= 1;
			this->sPos.y -= 1;
		}
		// Hero�b���W
		else if (delX < 0 && delX >= -3 && delY > 0 && delY <= 3)
		{
			flag = 1;
			this->sPos.x -= 1;
			this->sPos.y += 1;
		}
		// Hero�b�k
		else if (delX > 0 && delX <= 3 && delY == 0)
		{
			flag = 1;
			this->sPos.x += 1;
		}
		// Hero�b��
		else if (delX < 0 && delX >= -3 && delY == 0)
		{
			flag = 1;
			this->sPos.x -= 1;
		}
		// Hero�b�W
		else if (delY > 0 && delY <= 3 && delX == 0)
		{
			flag = 1;
			this->sPos.y += 1;
		}
		// Hero�b�U
		else if (delY < 0 && delY >= -3 && delX == 0)
		{
			flag = 1;
			this->sPos.y -= 1;
		}
		// Hero���b���u���A�h�H���W�U���k����
		else
		{
			flag = 0;
			int pos = genRandom();
			Position temp = this->getPos();
			switch (pos)
			{
			case 0:
				temp.y -= 1;
				if (isPositionValid(temp) == true)
				{
					this->sPos.y -= 1;
				}
				break;
			case 1:
				temp.y += 1;
				if (isPositionValid(temp) == true)
				{
					this->sPos.y += 1;
				}
				break;
			case 2:
				temp.x -= 1;
				if (isPositionValid(temp) == true)
				{
					this->sPos.x -= 1;
				}
				break;
			case 3:
				temp.x += 1;
				if (isPositionValid(temp) == true)
				{
					this->sPos.x += 1;
				}
				break;
			default:
				break;
			}
		}
	}
};