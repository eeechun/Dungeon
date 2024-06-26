/***********************************************************************
 * File: Creature.h
 * Author: 鄭依淳
 * Create Date: 2024/03/12
 * Editor: 鄭依淳
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
		// hero跟creature的距離差距
		int delX = pos.x - this->getPos().x;
		int delY = pos.y - this->getPos().y;

		// Hero在右上 
		if (delX > 0 && delX <= 3 && delY > 0 && delY <= 3)
		{
			flag = 1;
			this->sPos.x += 1;
			this->sPos.y += 1;
		}
		// Hero在右下
		else if (delX > 0 && delX <= 3 && delY < 0 && delY >= -3)
		{
			flag = 1;
			this->sPos.x += 1;
			this->sPos.y -= 1;
		}
		// Hero在左下
		else if (delX < 0 && delX >= -3 && delY < 0 && delY >= -3)
		{
			flag = 1;
			this->sPos.x -= 1;
			this->sPos.y -= 1;
		}
		// Hero在左上
		else if (delX < 0 && delX >= -3 && delY > 0 && delY <= 3)
		{
			flag = 1;
			this->sPos.x -= 1;
			this->sPos.y += 1;
		}
		// Hero在右
		else if (delX > 0 && delX <= 3 && delY == 0)
		{
			flag = 1;
			this->sPos.x += 1;
		}
		// Hero在左
		else if (delX < 0 && delX >= -3 && delY == 0)
		{
			flag = 1;
			this->sPos.x -= 1;
		}
		// Hero在上
		else if (delY > 0 && delY <= 3 && delX == 0)
		{
			flag = 1;
			this->sPos.y += 1;
		}
		// Hero在下
		else if (delY < 0 && delY >= -3 && delX == 0)
		{
			flag = 1;
			this->sPos.y -= 1;
		}
		// Hero不在視線內，則隨機上下左右移動
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