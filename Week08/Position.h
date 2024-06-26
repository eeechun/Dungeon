#pragma once
//************************************************************
// The location in the board
//************************************************************
class Position {
public:
	int x, y; // X, y Coordinate

	Position() : x(0), y(0) {}
	Position(int x, int y) : x(x), y(y) {}
	Position(const Position& ref) { *this = ref; }

	// Operator overloading

	// Intent: implement addition of two positions
	// Pre: cannot add two positions directly
	// Post: overload operator + to add two positions
	Position operator+(const Position& pos) const
	{
		return Position(this->x + pos.x, this->y + pos.y);
	}

	// Intent: add another position to the current
	// Pre: cannot move current position with +=
	// Post: overload operator += to move the current position
	Position operator+=(const Position& pos)
	{
		this->x += pos.x;
		this->y += pos.y;
		return (*this);
	}

	// Intent: implement subtraction of two positions
	// Pre: cannot subtract two positions directly
	// Post: overload operator - to subtract two positions
	Position operator-(const Position& pos) const
	{
		return Position(this->x - pos.x, this->y - pos.y);
	}

	// Intent: subtract another position to the current
	// Pre: cannot move current position with -=
	// Post: overload operator -= to move the current position
	Position operator-=(const Position& pos)
	{
		this->x -= pos.x;
		this->y -= pos.y;
		return (*this);
	}


	// Intent: multiply a constant number to the current position
	// Pre: cannot multiply a constant number to the current position
	// Post: overload operator * to multiply a constant number to the current position
	Position operator*(int num) const
	{
		return Position(this->x * num, this->y * num);
	}

	// Intent: determine if two objects are at the same position
	// Pre: cannot determine if the objects are at the same position directly
	// Post: return true if they are at the same position, otherwise false
	bool operator==(const Position& pos) const
	{
		if (this->x == pos.x && this->y == pos.y)
		{
			return true;
		}
		return false;
	}

	// Intent: determine if two objects are not at different position
	// Pre: cannot determine if the objects are not at the same position directly
	// Post: return false if they are at the same position, otherwise true
	bool operator!=(const Position& pos) const
	{
		if (this->x == pos.x && this->y == pos.y)
		{
			return false;
		}
		return true;
	}
};
