/************************************************************************
File:   source.cpp

Author:
		���s�Aea5878158@gmail.com
Modifier:
		�௧�N�Acheeryuchi@gmail.com
		���Y���Awindyhuang6@gmail.com
		���T�t�AJYCReports@gmail.com
		���ſ��Atbcey74123@gmail.com
Comment:
		�򥻿�J��V���ʥ\��Aw s a d ���ʸ}��W�U���k�A�ťէ��ܸ}�⯸�ߤ��a�O�r���A��T�W�i�H�W�[�g��
		ESC�O���}�e���C�P�ɧ�s�Ϫ��W����T�C

************************************************************************/

#include "main.h"
#include "Hero.h"
#include "Creature.h"
#include <vector>
#include <fstream>
Hero	 gHero(2, 2);

// Constent value
const char GWALL = 'O';
const char GNOTHING = ' ';

int GWIDTH = -1;
int GHEIGHT = -1;
const int MIN_SIZE = 4;
const int HORIZONTAL = 1;
const int VERTICAL = 2;
const double gTimeLog = 0.033;

// Distance
const int gDistance = 4;

// �Ψ��x�s�������
char** gBoard;

// �w�q���ؿ�J���O�P�����}�Cindex
enum ValidInput
{
	EW = 0,
	ES = 1,
	EA = 2,
	ED = 3,
	ESPACE = 4,
	EESC = 5,
	ESave = 6,
	ELoad = 7,
	INVALID,
};

enum Direction
{
	S = 1,
	E = 2
};

Creature gCreature;

// function declare
// ������J���A
void keyUpdate(bool key[]);
// ��l�ƪ���
void setupBoard(int rowN, int colN);
// ��X����
void draw(void);
// ��X������T
void drawInfo(void);

// �{���D�X�ʨ禡
void update(bool key[]);

void saveMap();
void loadMap();

std::vector<Trigger*> gTriggers;

int main(int argc, char** argv)
{
	srand(time(NULL));

	// �ΨӺ޲z��L��J���A���}�C
	bool gKeyState[ValidInput::INVALID];
	for (int i = 0; i < ValidInput::INVALID; i++) {
		gKeyState[i] = false;
	}

	while (true) {
		std::cout << "Enter Width: ";
		std::cin >> GWIDTH;
		std::cout << "Enter Height: ";
		std::cin >> GHEIGHT;
		system("CLS");
		if (GHEIGHT < MIN_SIZE || GWIDTH < MIN_SIZE) {
			std::cout << "Illegal, both has to be larger than " << MIN_SIZE << std::endl;
		}
		else {
			break;
		}
	}

	// Setup a clear dungeon
	setupBoard(GHEIGHT, GWIDTH);

	// Draw the bord and information
	draw();
	drawInfo();

	// Variable for game loop
	clock_t startT, endT;
	startT = clock();
	endT = clock();

	// Run the game loop
	while (!gKeyState[ValidInput::EESC]) {
		// Compute the time lap
		double timeFrame = (double)(endT - startT) / CLOCKS_PER_SEC;

		// Execute the game loop
		if (timeFrame >= gTimeLog) {
			update(gKeyState);
			startT = clock();
		}

		// Update the key
		keyUpdate(gKeyState);
		endT = clock();

		if (gKeyState[ValidInput::ESave]) {
			saveMap();
			gKeyState[ValidInput::ESave] = false;
		}
		else if (gKeyState[ValidInput::ELoad]) {
			loadMap();
			gKeyState[ValidInput::ELoad] = false;
		}
	}

	system("pause");
	return 0;
}

//******************************************************************
//
// * ������J���A
//==================================================================
void keyUpdate(bool key[])
//==================================================================
{
	for (int i = 0; i < ValidInput::INVALID; i++) {
		key[i] = false;
	}
	char input = _getch();
	switch (input) {
	case 'w':
		key[ValidInput::EW] = true;
		break;
	case 's':
		key[ValidInput::ES] = true;
		break;
	case 'a':
		key[ValidInput::EA] = true;
		break;
	case 'd':
		key[ValidInput::ED] = true;
		break;
	case ' ':
		key[ValidInput::ESPACE] = true;
		break;
	case 27:
		key[ValidInput::EESC] = true;
		break;
	case '1':
		key[ValidInput::ESave] = true;
		break;
	case '2':
		key[ValidInput::ELoad] = true;
		break;
	default:
		break;
	}
}

//******************************************************************
//
// * �P�_��m�O�_����
//==================================================================
bool isPositionValid(Position& pos)
//==================================================================
{
	// Check whether it is an empty space
	if (gBoard[pos.y][pos.x] != GNOTHING)
		return false;

	return true;
}

//******************************************************************
//
// * clip algroithm
//==================================================================
float clip(float n, float minimun, float maximum)
//==================================================================
{
	return std::max(minimun, std::min(n, maximum));
}

//******************************************************************
//
// * �Q�� call-by-referce �N�p��o�쪺��V�^��
//==================================================================
bool canSee(Position cPos, Position hPos, Position& dir)
//==================================================================
{
	// the dir_x and dir_y value are call-by-refernce
	dir.x = (int)clip((float)(hPos.x - cPos.x), -1.f, 1.f); // clip the value between -1 ~ 1
	dir.y = (int)clip((float)(hPos.y - cPos.y), -1.f, 1.f);
	int count = 0;
	do {
		// spot the target position
		if (cPos + dir * count == hPos) {
			return true;
		}
		count++;
	} while (count < gDistance); // check the range in 4 units
	return false;
}

// Intent: determine which way a field with the given dimensions ought to be bisected
// Pre: the board caanot be bisected correctly
// Post: return vertical or horizontal
int orientation(int width, int height)
{
	if (width > height)
	{
		return VERTICAL;
	}
	else
	{
		return HORIZONTAL;
	}
}

// Intent: display the maze
// Pre: cannot display the maze board
// Post: set gboard as the generated maze and display
void displayMaze(char* [])
{
	// set upper edge as wall
	for (int i = 0; i < GWIDTH; i++) {
		gBoard[0][i] = GWALL;
	}

	for (int y = 0; y < GHEIGHT; y++) {
		gBoard[y][0] = GWALL; // set left edge as wall

		for (int x = 1; x < GWIDTH; x++) {
			bool bottom = y + 1 >= GHEIGHT;
			bool south = (gBoard[y][x] & S) != 0 || bottom; // check if there is a wall to the south or it is at the bottom
			bool south2 = (x + 1 < GWIDTH && (gBoard[y][x + 1] & S) != 0) || bottom; // check if there is a wall to the southeast or it is at the bottom
			bool east = (gBoard[y][x] & E) != 0 || x + 1 >= GWIDTH; // Check if there is a wall to the east or it's at the right edge

			// make the position that has a wall a wall
			if (south)
			{
				gBoard[y][x] = GWALL;
			}
			else
			{
				gBoard[y][x] = GNOTHING;
			}

			if (east)
			{
				gBoard[y][x] = GWALL;
			}
			else
			{
				if (south && south2)
				{
					gBoard[y][x] = GWALL;
				}
				else
				{
					gBoard[y][x] = GNOTHING;
				}
			}
		}
	}
	// debug: make sure the lower-right corner is empty
	gBoard[GHEIGHT - 2][GWIDTH - 2] = GNOTHING;
}

// Intent: maze generating algorithm
// Pre: cannot generate maze
// Post: randomly generate maze
void divide(char* [], int x, int y, int width, int height, int orient)
{
	if (width < 2 || height < 2)
	{
		return;
	}

	bool horizontal = (orient == HORIZONTAL);

	// wall position
	int wallX = x + (horizontal ? 0 : std::rand() % (width - 1));
	int wallY = y + (horizontal ? std::rand() % (height - 1) : 0);

	// passage position
	int passX = wallX + (horizontal? rand() % width : 0);
	int passY = wallY + (horizontal ? 0 : rand() % height);

	// wall direction
	int dirX = (horizontal ? 1 : 0);
	int	dirY = (horizontal ? 0 : 1);

	int len = (horizontal? width : height);
	int dir = (horizontal ? S : E);

	// draw the wall
	for (int i = 0; i < len; i++) {
		if (wallX != passX || wallY != passY) {
			gBoard[wallY][wallX] |= dir; // set the wall side to the current position
		}

		// add wallX, wallY according to the direction
		wallX += dirX;
		wallY += dirY;
	}

	// determine the bounds of the subfields and recursive
	int newX = x;
	int newY = y;
	int newWidth = (horizontal ? width : (wallX - x));
	int newHeight = (horizontal ? (wallY - y) : height);

	divide(gBoard, newX, newY, newWidth, newHeight, orientation(newWidth, newHeight));

	// determine the bounds of the subfields and recursive when width < 2 or height <��
	if (horizontal)
	{
		newX = x;
		newY = wallY + 1;
		newWidth = width;
		newHeight = y + height - wallY - 1;
	}
	else
	{
		newX = wallX + 1;
		newY = y;
		newWidth = x + width - wallX - 1;
		newHeight = height;
	}

	divide(gBoard, newX, newY, newWidth, newHeight, orientation(newWidth, newHeight));
}

//******************************************************************
//
// * Setup the board
//==================================================================
void setupBoard(int rowN, int colN)
//==================================================================
{
	// Allocate & init game board using 2d dynamic array

	gBoard = new char* [rowN];
	for (int i = 0; i < rowN; i++) {
		gBoard[i] = new char[colN];
		for (int j = 0; j < colN; j++) {
			if (i == 0 || i == rowN - 1 || j == 0 || j == colN - 1)
				gBoard[i][j] = GWALL;
			else
				gBoard[i][j] = GNOTHING;
		}
	}

	// initialize the board to 0, in order to compare direction later
	for (int i = 0; i < GHEIGHT; i++)
	{
		for (int j = 0; j < GWIDTH; j++)
		{
			gBoard[i][j] = 0;
		}
	}

	srand(99); // set random seed
	divide(gBoard, 0, 0, GWIDTH, GHEIGHT, orientation(GWIDTH, GHEIGHT));
	displayMaze(gBoard);

	// Setup for (random) position of all elements and implementation of game board using 2d dynamic array
	// Elements has to be randomly generated within canvas

	std::vector<std::vector<bool>> validFlags(GHEIGHT);
	for (int i = 0; i < GHEIGHT; i++) {
		validFlags[i].resize(GWIDTH);
		for (int j = 0; j < GWIDTH; j++) {
			validFlags[i][j] = gBoard[i][j] == GWALL ? false : true;
		}
	}

	auto getRandomPos = [&rowN, &colN]() {
		return Position((int)(rand() % colN), (int)(rand() % rowN));
	};

	auto getValidRandomPos = [&validFlags, &getRandomPos]() {
		while (true) {
			Position pos = getRandomPos();
			if (validFlags[pos.y][pos.x]) {
				return pos;
			}
		}
	};

	Position hPos(1,1);
	validFlags[hPos.y][hPos.x] = false;
	gHero.setPos(hPos);

	Position cPos = getValidRandomPos();
	validFlags[cPos.y][cPos.x] = false;
	gCreature.setPos(cPos);

	for (int i = 0; i < 2; i++) {
		Trigger* trigger = new Trigger();
		Position tPos = getValidRandomPos();
		validFlags[tPos.y][tPos.x] = false;
		trigger->setPos(tPos);
		gTriggers.push_back(trigger);
	}
}

//******************************************************************
//
// * Draw the board
//==================================================================
void draw()
//==================================================================
{
	// Add the hero into the board
	// Setup and implementation of drawing board using 2d vector

	std::vector<std::vector<char>> drawBoard(GHEIGHT);

	for (int i = 0; i < GHEIGHT; i++) {
		drawBoard[i].resize(GWIDTH);
		for (int j = 0; j < GWIDTH; j++) {
			drawBoard[i][j] = gBoard[i][j];
		}
	}

	// Draw two triggers using for loop on drawBoard

	for (int i = 0; i < gTriggers.size(); i++) {
		Position t = gTriggers[i]->getPos();
		drawBoard[t.y][t.x] = gTriggers[i]->getIcon();
	}

	Position c = gCreature.getPos();
	drawBoard[c.y][c.x] = gCreature.getIcon();

	// Update the hero information
	Position h = gHero.getPos();
	drawBoard[h.y][h.x] = gHero.getIcon();

	// Draw the board
	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			std::cout << drawBoard[i][j]; //  output
		}
		std::cout << "\n";
	}
}

//******************************************************************
//
// * Output information
//==================================================================
void drawInfo(void)
//==================================================================
{
	std::cout << "The hero is level " << gHero.getLevel() << "(" << gHero.getExp() << "/" << gHero.getMaxExp() << " to level up)" << std::endl;
	std::cout << "The hero has " << gHero.getHP() << " hp" << std::endl;
	std::cout << "Use wsad key to move Hero " << gHero.getIcon() << std::endl;
	std::cout << "Every time you step on a trigger T, the hero gets 10 exp." << std::endl;
	std::cout << "(ESC) Exit (1) Save (2) Load" << std::endl;
}

//******************************************************************
//
// * Update the board state
//==================================================================
void update(bool key[])
//==================================================================
{
	// �M������
	system("CLS");

	Position delta;

	// �O�_��input
	bool hasInput = false;
	if (key[ValidInput::EW]) {
		delta -= Position(0, 1);
		hasInput = true;
	}
	else if (key[ValidInput::ES]) {
		delta += Position(0, 1);
		hasInput = true;
	}
	else if (key[ValidInput::EA]) {
		delta = delta - Position(1, 0);
		hasInput = true;
	}
	else if (key[ValidInput::ED]) {
		delta = delta + Position(1, 0);
		hasInput = true;
	}
	else {
		bool allInvalid = true;
		for (int i = 0; i < ValidInput::INVALID; i++) {
			if (key[i]) {
				allInvalid = false;
				break;
			}
		}
		if (allInvalid)
			std::cout << "invalid input\n";
	}
	if (hasInput) {
		gHero.move(delta);
	}

	// Manipulate update of two triggers using while loop

	for (int i = 0; i < gTriggers.size(); i++) {
		gTriggers[i]->update(gHero);
	}

	gCreature.update(gHero);
	draw();
	drawInfo();
}

//******************************************************************
//
// * Save the map status
//==================================================================
void saveMap() {
	// Save dungen to file
	system("CLS");
	std::cout << "Input file name for saving or Exit to leave saving." << std::endl;
	std::cout << "Input: ";
	std::string input;
	std::cin >> input;
	if (input.compare("Exit") == 0)
		return;

	std::ofstream oStream(input + ".txt");
	oStream << GWIDTH << " " << GHEIGHT << std::endl;

	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			oStream << gBoard[i][j];
		}
		oStream << std::endl;
	}
	oStream << std::endl;

	oStream << gHero.getPos() << " " << gHero.getHP() << " " << gHero.getLevel() << " " << gHero.getExp() << " " << gHero.getMaxExp() << std::endl;
	oStream << gCreature.getPos() << std::endl;
	oStream << gTriggers.size() << std::endl;
	for (int i = 0; i < gTriggers.size(); i++) {
		oStream << gTriggers[i]->getPos() << std::endl;
	}

	oStream.close();
}

//******************************************************************
//
// * Load the map status
//==================================================================
void loadMap() {
	// Load from file and reset the dungen
	system("CLS");
	std::cout << "Input file name for loading or Exit to leave loading." << std::endl;
	std::cout << "Input: ";
	std::string input;
	std::cin >> input;
	if (input.compare("Exit") == 0)
		return;

	std::ifstream iStream(input + ".txt");
	if (!iStream.is_open())
		return;

	// reset dungen
	for (int i = 0; i < GHEIGHT; i++) {
		delete[] gBoard[i];
	}
	delete[] gBoard;

	for (int i = 0; i < gTriggers.size(); i++)
		delete gTriggers[i];
	gTriggers.clear();

	iStream >> GWIDTH >> GHEIGHT;

	char _c;
	iStream.get(_c);

	gBoard = new char* [GHEIGHT];
	for (int i = 0; i < GHEIGHT; i++) {
		gBoard[i] = new char[GWIDTH];
		for (int j = 0; j < GWIDTH; j++) {
			iStream.get(gBoard[i][j]);
		}
		iStream.get(_c);
	}

	Position pos;
	int hp, level, exp, maxExp;
	iStream >> pos >> hp >> level >> exp >> maxExp;

	gHero.setPos(pos);
	gHero.setHP(hp);
	gHero.setLevel(level);
	gHero.setExp(exp);
	gHero.SetMaxExp(maxExp);

	iStream >> pos;
	gCreature.setPos(pos);

	int triggerN;
	iStream >> triggerN;
	for (int i = 0; i < triggerN; i++) {
		iStream >> pos;
		Trigger* trigger = new Trigger();
		trigger->setPos(pos);
		gTriggers.push_back(trigger);
	}

	iStream.close();
}