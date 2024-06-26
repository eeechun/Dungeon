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
	int			money;

public:
	// Default constructor
	Hero() {
		this->sPos.x = 0;
		this->sPos.y = 0;
		this->sLevel = 1;
		this->sCurrentExp = 0;
		this->sMaxExp = 15;
		this->sIcon = 'H';
		this->hp = 100;
		this->money = 0;
	};
	// Setting constructor
	Hero(int x, int y, int level = 1, int maxExp = 15, int currentExp = 0, char icon = 'H', int hp = 100, int money = 1000) {
		this->sPos.x = x;
		this->sPos.y = y;
		this->sLevel = level;
		this->sCurrentExp = currentExp;
		this->sMaxExp = maxExp;
		this->sIcon = icon;
		this->hp = hp;
		this->money = money;
	};

	// Setting constructor
	Hero(Position& pos, int level = 1, int maxExp = 15, int currentExp = 0, char icon = 'H', int hp = 100, int money = 1000) {
		this->sPos = pos;
		this->sLevel = level;
		this->sCurrentExp = currentExp;
		this->sMaxExp = maxExp;
		this->sIcon = icon;
		this->hp = hp;
		this->money = money;
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

	// Set money
	void SetMoney(int money) { this->sMaxExp = money; }

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

	// Get money
	int getMoney(void) { return this->money; }

	int getHP() const { return this->hp; }
	void setHP(int hp) { this->hp = hp; }

	// Incrementally move the elements 
	void move(Position delta);

	// Calculate Gain of EXP
	void gainEXP(int points) {
		int number = points;
		while (number > 0) {
			if (sCurrentExp + number >= sMaxExp) {//level up
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
	void damage(int points) {
		hp = hp - points;
		if (hp < 0)
			hp = 0;
	}

	void levelDown(int level) {
		sLevel = sLevel - level;
		// if Hero is already in level 1, make current Exp to 0 instead of level down
		if (sLevel < 1)
		{
			sLevel = 1;
			sCurrentExp = 0;
		}
	}

	void levelUp(int level) {
		sLevel = sLevel + level;
	}

	void fulfillHealth(int health) {
		this->hp = this->hp + health;
		if (this->hp >= 100)
		{
			this->hp = 100;
		}
	}

	void cost(int value) {
		this->money = this->money - value;
		if (this->money < 0)
		{
			this->money = 0;
			this->damage(5);
		}
	}

	void gain(int value) {
		this->money = this->money + value;
	}
};
