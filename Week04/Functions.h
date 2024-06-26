/***********************************************************************
 * File: Functions.h
 * Author: 鄭依淳
 * Create Date: 2024/03/12
 * Editor: 鄭依淳
 * Update Date: 2024/03/12
 * Description: This header file is to declare functions used in the project.
***********************************************************************/

#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <iostream>
#include <algorithm>
#include <conio.h>
#include "Position.h"

class Hero;
class Creature;

extern Hero		gHero;
extern Creature gCreature;

// Constent value
const char GWALL = 'O';
const char GNOTHING = ' ';
const int GWIDTH = 10;
const int GHEIGHT = 10;
const double gTimeLog = 0.033;

// Distance
const int gDistance = 4;

// 用來儲存版面資料
char gBoard[][GWIDTH];

// 定義六種輸入指令與對應陣列index
enum ValidInput
{
	EW = 0,
	ES = 1,
	EA = 2,
	ED = 3,
	ESPACE = 4,
	EESC = 5,
	INVALID,
};

// 偵測輸入狀態
void keyUpdate(bool key[]);
// 判斷位置是否為空
bool isPositionValid(Position& loc);
// 初始化版面
void setupBoard();
// 輸出版面
void draw(void);
// 輸出說明資訊
void drawInfo(void);
// Generate random number to decide where to move
int genRandom();

// 程式主驅動函式
void update(bool key[]);

#endif // !__FUNCTIONS_H__