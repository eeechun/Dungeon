/***********************************************************************
 * File: Hero.h
 * Author: ¾G¨Ì²E
 * Create Date: 2024/03/15
 * Editor: ¾G¨Ì²E
 * Update Date: 2024/03/15
 * Description: This header file is to define hero class.
***********************************************************************/

#pragma once
#include <string>
#include "Position.h"
#include "main.h"
//************************************************************
// Hero Class, only has requirement part for example
//************************************************************

class Hero {

private:
	Position	sPos;			// Hero location
	char sIcon = 'H';	// Hero icon
	int			hp;
	int			sLevel = 1;     // Level
	int			sMaxExp;		// Level update experience
	int			sCurrentExp;	// current exp hero has

public:
	// Default constructor
	Hero() {
		this->sPos.x = 0;
		this->sPos.y = 0;
		this->sLevel = 1;
		this->sCurrentExp = 0;
		this->sMaxExp = 10;
		this->sIcon = 'H';
		this->hp = 100;
	};
	// Setting constructor
	Hero(int x, int y, int level = 1, int maxExp = 10, int currentExp = 0, char icon = 'H', int hp = 100) {
		this->sPos.x = x;
		this->sPos.y = y;
		this->sLevel = level;
		this->sCurrentExp = currentExp;
		this->sMaxExp = maxExp;
		this->sIcon = icon;
		this->hp = hp;
	};

	// Setting constructor
	Hero(Position& pos, int level = 1, int maxExp = 10, int currentExp = 0, char icon = 'H', int hp = 100) {
		this->sPos = pos;
		this->sLevel = level;
		this->sCurrentExp = currentExp;
		this->sMaxExp = maxExp;
		this->sIcon = icon;
		this->hp = hp;
	};

	// Set position
	void setPos(Position pos) { this->sPos = pos; }
	void setPos(int x, int y) {
		this->sPos.x = x;
		this->sPos.y = y;
	}

	// Set icon
	void setIcon(char& icon) { this->sIcon = icon; }

	// Set level
	void setLevel(int level) { this->sLevel = level; }

	// Set exp
	void setExp(int exp) { this->sCurrentExp = exp; }

	// Set MaxExp
	void SetMaxExp(int maxexp) { this->sMaxExp = maxexp; }

	// Get position
	Position getPos(void) { return this->sPos; }

	// Get Icon
	char getIcon(void) { return this->sIcon; }

	// Get level
	int getLevel(void) { return this->sLevel; }

	// Get Exp
	int getExp(void) { return this->sCurrentExp; }

	// Get Max
	int getMaxExp(void) { return this->sMaxExp; }

	int getHP() const { return this->hp; }

	// Incrementally move the elements 
	void move(int x, int y) {
		// Compute the next position
		Position next;
		next.x = this->sPos.x + x;
		next.y = this->sPos.y + y;

		if (isPositionValid(next))
			this->sPos = next;
		else {
			std::cout << "Invalid location\n";
		}
	}

	// Intent: calculate gain of EXP
	// Pre: EXP and level won't change
	// Post: Level up when EXP catches the maximum of the current level.
	void gainEXP(int points) {
		// Implement Gain of EXP
		int number = points;
		while (number > 0) {
			// if level up
			if (sCurrentExp + number >= sMaxExp) {
				number -= (sMaxExp - sCurrentExp);
				sCurrentExp = 0;
				sMaxExp = (int)((float)sMaxExp * 1.2f);
				sLevel++;
			}
			else {
				sCurrentExp += number;
				number = 0;
			}
		}
	}
	
	// Intent: implement damage to Hero when walked through Creature
	// Pre: nothing happened when Hero walked through Creature
	// Post: lost 1 health
	void damage(int points) {
		// Implement Damage done to Hero
		this->hp -= points;
		if (this->hp <= 0)
		{
			std::cout << "Hero is out of health.\n";
		}
	}
};
