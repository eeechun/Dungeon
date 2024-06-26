#pragma once
#include <iostream>
#include <fstream>
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
	Position operator+(const Position& rhs) const {
		return Position(x + rhs.x, y + rhs.y);
	}
	Position& operator+=(const Position& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	Position operator-(const Position& rhs) const {
		return Position(x - rhs.x, y - rhs.y);
	}
	Position& operator-=(const Position& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	Position operator*(int scale) const {
		return Position(x * scale, y * scale);
	}
	bool operator==(const Position& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator!=(const Position& rhs) const {
		return !(*this == rhs);
	}

	/*Please implement your code here*/

	friend std::istream& operator>>(std::istream& is, Position& pos) {
		char comma;
		return is >> pos.x >> comma >> pos.y;
	}

	friend std::ostream& operator<<(std::ostream& os, const Position& pos) {
		return os << pos.x << ", " << pos.y;
	}

	/************************************************************************/
};
