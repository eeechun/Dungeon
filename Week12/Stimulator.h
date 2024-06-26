#pragma once
#include "Hero.h"
#include "Position.h"

class Stimulator
{
protected:
	char s_icon;
	Position s_pos;

public:
	/* constructors and copy constructor */
	Stimulator()
	{
		s_icon = '$';
	}
	Stimulator(int x, int y)
	{
		s_icon = '$';
		s_pos.x = x;
		s_pos.y = y;
	}
	Stimulator(const Stimulator& stim)
	{
		*this = stim;
	}

	/* function */
	virtual void update(Hero& hero)
	{
		if (hero.getPos() == s_pos)
		{
			hero.gain(500);
		}
	}

	// Set position
	void setPos(const Position& pos) { this->s_pos = pos; }
	void setPos(int x, int y) {
		this->s_pos.x = x;
		this->s_pos.y = y;
	}

	// Get position
	Position getPos() const { return this->s_pos; }

	// Get Icon
	char getIcon() const { return this->s_icon; }
};

class healthStimulator : public Stimulator
{
public:
	/* consrtuctors and copy constructor */
	healthStimulator()
	{
		s_icon = '*';
	}

	/* function */
	void update(Hero& hero)
	{
		if (hero.getPos() == s_pos)
		{
			hero.fulfillHealth(5);
		}
	}
};