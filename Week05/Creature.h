/***********************************************************************
 * File: Creature.h
 * Author: ¾G¨Ì²E
 * Create Date: 2024/03/15
 * Editor: ¾G¨Ì²E
 * Update Date: 2024/03/18
 * Description: This header file is to define creature class.
***********************************************************************/

#include <string>
#include "Position.h"
#include "Hero.h"
#include "main.h"

class Creature {//creature class 
private:
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
	void update(Hero& hero) {
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

		if (hPos.x == sPos.x && hPos.y == sPos.y) {
			hero.damage(power);
		}
	}
};