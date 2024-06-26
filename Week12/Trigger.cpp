#include "Trigger.h"

void Trigger::update(Hero& hero)
{
	Position hPos = hero.getPos();

	if (hPos == this->_pos)
	{
		hero.gainEXP(_exp);
	}
}

void LevelTrigger::update(Hero& hero)
{
	Position hPos = hero.getPos();

	if (hPos == _pos)
	{
		hero.levelUp(1);
	}
}