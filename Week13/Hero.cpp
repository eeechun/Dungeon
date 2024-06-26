#include "Hero.h"

void Hero::move(Position delta) {
	// Compute the next position
	Position next = this->sPos + delta;

    try 
    {
        // if the next position is invalid, throw invalid argument
        if (!isPositionValid(next)) 
        {
            throw std::invalid_argument("Invalid location");
        }
        
        // if valid, update the position
        this->sPos = next;
    }
    catch (const std::invalid_argument& e) 
    {
        std::cerr << "Exception caught: " << e.what() << "\n";
    }
}