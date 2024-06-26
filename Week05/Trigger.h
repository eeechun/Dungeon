/***********************************************************************
 * File: Trigger.h
 * Author: ¾G¨Ì²E
 * Create Date: 2024/03/15
 * Editor: ¾G¨Ì²E
 * Update Date: 2024/03/18
 * Description: This header file is to define trigger class.
***********************************************************************/

#pragma once
#include <string>
#include <iostream>
#include "Position.h"
#include "Hero.h"
class Hero;

//************************************************************
// Trigger Class
//************************************************************
class Trigger {
private:
	Position	sPos;			// Hero location
	char sIcon = 'T';	// Hero icon
private:
	int			sExpAmount;		// Set up the amount gain

public:
	// Default constructor
	Trigger(void) {
		this->sPos.x = 0;
		this->sPos.y = 0;
		this->sExpAmount = 0;
		this->sIcon = 'T';
	};

	// Setting constructor
	Trigger(int x, int y, int amt, char icon = 'T') {
		this->sPos.x = x;
		this->sPos.y = y;
		this->sExpAmount = amt;
		this->sIcon = icon;
	};

	// Setting constructor
	Trigger(Position& pos, int amt, char icon = 'T') {
		this->sPos = pos;
		this->sExpAmount = amt;
		this->sIcon = icon;
	};

	// Set icon
	void setIcon(char& icon) { this->sIcon = icon; }

	// Set the amount
	void SetAmount(int amt) { this->sExpAmount = amt; }

	// Get position
	Position getPos(void) { return this->sPos; }

	// Get Icon
	char getIcon(void) { return this->sIcon; }

	// Get the amount 
	int getExpAmount(void) { return this->sExpAmount; }

	// Intent: Hero gains experience after trigger
	// Pre: experience not changed
	// Post: Hero got experience according to the trigger itself
	void trigger(Hero& h) {
		h.gainEXP(sExpAmount);
	}
	
	// Intent: if Hero walk through trigger, then call trigger function
	// Pre: won't trigger even when Hero walk through trigger
	// Post: if Hero walk through trigger, then call trigger function
	void update(Hero& h) {
		if (this->sPos.x == h.getPos().x && this->sPos.y == h.getPos().y) {
			this->trigger(h);
		}
	}
};