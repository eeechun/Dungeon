/***********************************************************************
 * File: Functions.h
 * Author: �G�̲E
 * Create Date: 2024/03/12
 * Editor: �G�̲E
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

// �Ψ��x�s�������
char gBoard[][GWIDTH];

// �w�q���ؿ�J���O�P�����}�Cindex
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

// ������J���A
void keyUpdate(bool key[]);
// �P�_��m�O�_����
bool isPositionValid(Position& loc);
// ��l�ƪ���
void setupBoard();
// ��X����
void draw(void);
// ��X������T
void drawInfo(void);
// Generate random number to decide where to move
int genRandom();

// �{���D�X�ʨ禡
void update(bool key[]);

#endif // !__FUNCTIONS_H__