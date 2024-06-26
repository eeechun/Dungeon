#pragma once
#include <string>
#include "Position.h"
#include "Hero.h"
#include "main.h"
//************************************************************
// Creature Class, only has requirement part for example
//************************************************************

class Creature {//creature class 
protected:
	Position	sPos;			// Creature position
	char sIcon = 'C';			// Creature icon
	int power;
public:
	// Default constructor
	Creature(void) {
		this->sPos.x = 1;
		this->sPos.y = 1;
		this->sIcon = 'C';
		this->power = 5;
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

public:
	virtual void update(Hero& hero) {
		Position hPos = hero.getPos();

		Position dir;
		if (canSee(this->sPos, hPos, dir)) {
			std::cout << "Creature has find the Hero in the ( " << dir.x << ", " << dir.y << " ) direction\n";
			this->sIcon = '!';
		}
		else {
			std::cout << "Creature didn't find the Hero\n";
			this->sIcon = 'C';
		}

		if (!(hPos != sPos)) {
			hero.damage(power);
		}
	}
};

// Hero's level decreased by 1 when it was attacked by Creature1 (icon : X)
class LevelCreature :public Creature
{
public:
	LevelCreature()
	{
		sIcon = 'X';
		power = 10;
	}

	void update(Hero& hero) override {
		Position hPos = hero.getPos();

		Position dir;
		if (canSee(sPos, hPos, dir)) {
			std::cout << "Enemy 2 has found the Hero in the (" << dir.x << ", " << dir.y << ") direction\n";
			sIcon = '!';
		}
		else {
			std::cout << "Enemy 2 didn't find the Hero\n";
			sIcon = 'X';
		}

		if (hPos == sPos) {
			hero.levelDown(1);
		}
	}
};

// Hero's money minus 100 when it was attacked by Creature2 (icon : x)
class MoneyCreature :public Creature
{
public:
	MoneyCreature()
	{
		sIcon = 'x';
		power = 10;
	}

	void update(Hero& hero) override {
		Position hPos = hero.getPos();

		Position dir;
		if (canSee(sPos, hPos, dir)) {
			std::cout << "Enemy 1 has found the Hero in the (" << dir.x << ", " << dir.y << ") direction\n";
			sIcon = '!';
		}
		else {
			std::cout << "Enemy 1 didn't find the Hero\n";
			sIcon = 'x';
		}

		if (hPos == sPos) {
			hero.cost(100);
		}
	}
};