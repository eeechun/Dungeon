/************************************************************************
File:   main.cpp

Author:
		鍾賢廣，ea5878158@gmail.com
Modifier:
		賴祐吉，cheeryuchi@gmail.com
		黃欣云，windyhuang6@gmail.com
		陳俊宇，JYCReports@gmail.com
		邱嘉興，tbcey74123@gmail.com
		鄭依淳，b10930032@mail.ntust.edu.tw
Comment:
		基本輸入方向移動功能，w s a d 移動腳色上下左右，空白改變腳色站立之地板字元，到T上可以增加經驗
		ESC是離開畫面。同時更新圖版上的資訊。

************************************************************************/

#include "main.h"
#include "Hero.h"
#include "Creature.h"
#include <vector>
Hero	 gHero(2, 2);

// Constent value
const char GWALL = 'O';
const char GNOTHING = ' ';

int GWIDTH = -1;
int GHEIGHT = -1;
const int MIN_SIZE = 4;
const double gTimeLog = 0.033;

// Distance
const int gDistance = 4;

// 用來儲存版面資料
char** gBoard;

// 定義六種輸入指令與對應陣列index
enum ValidInput
{
	EW = 0,
	ES = 1,
	EA = 2,
	ED = 3,
	ESPACE = 4,
	EESC = 5,
	ER = 6,
	INVALID,
};


Creature gCreature;

// function declare
// 偵測輸入狀態
void keyUpdate(bool key[]);
// 初始化版面
void setupBoard(int rowN, int colN);
// 輸出版面
void draw(int height, int width);
// 輸出說明資訊
void drawInfo(void);

// 程式主驅動函式
void update(bool key[]);

// Create vector of trigger pointer for further managenent and manipulation
/*Please implement your code here*/

Trigger trigger1, trigger2;
std::vector<Trigger*> trigger;

/************************************************************************/

bool resizedRec = false;

int main(int argc, char** argv)
{
	srand(time(NULL));

	// 用來管理鍵盤輸入狀態的陣列
	bool gKeyState[6];
	for (int i = 0; i < 6; i++) {
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
	draw(GHEIGHT, GWIDTH);
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
	}

	system("pause");
	return 0;
}

//******************************************************************
//
// * 偵測輸入狀態
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
	case 'R':
		key[ValidInput::ER] = true;
		break;
	case ' ':
		key[ValidInput::ESPACE] = true;
		break;
	case 27:
		key[ValidInput::EESC] = true;
		break;
	default:
		break;
	}
}

//******************************************************************
//
// * 判斷位置是否為空
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
// * 利用 call-by-referce 將計算得到的方向回傳
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
		if (cPos.x + dir.x * count == hPos.x &&
			cPos.y + dir.y * count == hPos.y) {
			return true;
		}
		count++;
	} while (count < gDistance); // check the range in 4 units
	return false;
}

// Intent: geneerate random position
// Pre: position is not randomly initialized
// Post: position can be initialized randomly
Position randomPos()
{
	Position temp;
	do
	{
		temp.x = rand() % GWIDTH;
		temp.y = rand() % GHEIGHT;
	} while (isPositionValid(temp) == false);
	
	return temp;
}

//******************************************************************
//
// * Setup the board
//==================================================================
void setupBoard(int rowN, int colN)
//==================================================================
{
	// Allocate & init game board using 2d dynamic array
	/*Please implement your code here*/

	gBoard = new char* [rowN];

	for (int i = 0; i < rowN; i++)
	{
		gBoard[i] = new char[colN];
	}

	for (int i = 0; i < rowN; i++)
	{
		for (int j = 0; j < colN; j++)
		{
			if (i == 0 || j == 0 || i == rowN - 1 || j == colN - 1)
			{
				gBoard[i][j] = GWALL;
			}
			else
			{
				gBoard[i][j] = GNOTHING;
			}
		}
	}

	/************************************************************************/	

	// Setup for (random) position of all elements and implementation of game board using 2d dynamic array
	// Elements has to be randomly generated within canvas
	// Two triggers should also be initialized and pushed to the container here.
	/*Please implement your code here*/

	if (resizedRec == false)
	{
		gHero.setPos(randomPos());
		gCreature.setPos(randomPos());

		trigger.push_back(&trigger1);
		trigger.push_back(&trigger2);

		for (auto t : trigger)
		{
			t->setPos(randomPos());
		}
	}
	else
	{
		gHero.setPos(gHero.getPos());
		gCreature.setPos(gCreature.getPos());

		for (auto t : trigger)
		{
			t->setPos(t->getPos());
		}
	}
	
	/************************************************************************/
}

//******************************************************************
//
// * Draw the board
//==================================================================
void draw(int height, int width)
//==================================================================
{
	// Add the hero into the board
	// Setup and implementation of drawing board using 2d vector
	/*Please implement your code here*/

	std::vector<std::vector<char>> drawBoard(height, std::vector<char>(width));

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			drawBoard[i][j] = gBoard[i][j];
		}
	}

	/************************************************************************/

	// Draw two triggers using for loop on drawBoard
	/*Please implement your code here*/

	for (auto t : trigger)
	{
		Position p = t->getPos();
		drawBoard[p.y][p.x] = t->getIcon();
	}

	/************************************************************************/

	Position c = gCreature.getPos();
	drawBoard[c.y][c.x] = gCreature.getIcon();

	// Update the hero information
	Position h = gHero.getPos();
	drawBoard[h.y][h.x] = gHero.getIcon();

	// Draw the board
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
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
	std::cout << "Press ESC key to exit" << std::endl;
}

bool checkValid(int reHeight, int reWidth)
{
	Position tPos1 = trigger1.getPos();
	Position tPos2 = trigger2.getPos();
	Position heroPos = gHero.getPos();
	Position creaturePos = gCreature.getPos();

	if (tPos1.x >= reWidth - 1 || tPos1.y >= reHeight - 1)
	{
		std::cerr << "Trigger 1 out of range.\n";
		return false;
	}
	if (tPos2.x >= reWidth - 1 || tPos2.y >= reHeight - 1)
	{
		std::cerr << "Trigger 2 out of range.\n";
		return false;
	}
	if (heroPos.x >= reWidth - 1 || heroPos.y >= reHeight - 1)
	{
		std::cerr << "Hero out of range.\n";
		return false;
	}
	if (creaturePos.x >= reWidth - 1 || creaturePos.y >= reHeight - 1)
	{
		std::cerr << "Creature out of range.\n";
		return false;
	}
	return true;
}

Position inputSize()
{
	int reWidth = 0, reHeight = 0;

	std::cout << "Resize the board width: ";
	std::cin >> reWidth;
	std::cout << "Resize the board height: ";
	std::cin >> reHeight;

	if (checkValid(reHeight, reWidth) == true)
	{
		Position temp;
		temp.x = reWidth;
		temp.y = reHeight;
		system("CLS");
		return temp;
	}
	else
	{
		inputSize();
	}
}

void resizeBoard()
{
	Position reSized = inputSize();
	GHEIGHT = reSized.y;
	GWIDTH = reSized.x;
	resizedRec = true;
	setupBoard(GHEIGHT, GWIDTH);
}

//******************************************************************
//
// * Update the board state
//==================================================================
void update(bool key[])
//==================================================================
{
	// 清除版面
	system("CLS");

	// 是否有input
	bool hasInput = false;
	if (key[ValidInput::EW]) {
		gHero.move(0, -1);
		hasInput = true;
	}
	else if (key[ValidInput::ES]) {
		gHero.move(0, 1);
		hasInput = true;
	}
	else if (key[ValidInput::EA]) {
		gHero.move(-1, 0);
		hasInput = true;
	}
	else if (key[ValidInput::ED]) {
		gHero.move(1, 0);
		hasInput = true;
	}
	else if (key[ValidInput::ER]) {
		resizeBoard();
		hasInput = true;
	}
	else {
		std::cout << "invalid input\n";
	}

	// Manipulate update of two triggers using while loop
	/*Please implement your code here*/

	std::vector<Trigger*>::iterator it = trigger.begin();
	while (it!=trigger.end())
	{
		(*it)->update(gHero);
		it++;
	}

	/************************************************************************/

	gCreature.update(gHero);
	draw(GHEIGHT, GWIDTH);
	drawInfo();
}
