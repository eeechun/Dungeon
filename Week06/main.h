/***********************************************************************
 * File: main.h
 * Author: 鄭依淳
 * Create Date: 2024/03/15
 * Editor: 鄭依淳
 * Update Date: 2024/03/24
 * Description: This header file is to define position structure.
***********************************************************************/

#include <iostream>
#include <math.h>		// pow() and sqrt()
#include <ctime>		// for time loop function
#include <conio.h>		// _getch() <= to read input without enter "ENTER" key
#include <algorithm>	// for max and min function
#include "Position.h"
#include "Trigger.h"
// Check whether the location is a valid one i.e. not a wall
bool isPositionValid(Position& loc);
// clip algroithm
float clip(float n, float minimun, float maximum);

// Check whether two position is close enough，利用 call-by-referce 將計算得到的方向回傳
bool canSee(Position cPos, Position hPos, Position& pos2);

