/************************************************************************
File:   source.cpp

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
std::vector<char> input; // store the input instruction

// Constent value
const char GWALL = 'O';
const char GNOTHING = ' ';

const int GWIDTH = 10;
const int GHEIGHT = 10;
const double gTimeLog = 0.033;

// Distance
const int gDistance = 4;

// 用來儲存版面資料
char gBoard[GHEIGHT][GWIDTH];

// 定義六種輸入指令與對應陣列index
enum ValidInput
{
	EW = 0,
	ES = 1,
	EA = 2,
	ED = 3,
	ESPACE = 4,
	EESC = 5,
	EMOVE,
	EJUMP,
	INVALID,
};


Creature gCreature;

// function declare
// 偵測輸入狀態
void keyUpdate(bool key[]);
// 初始化版面
void setupBoard();
// 輸出版面
void draw(void);
// 輸出說明資訊
void drawInfo(void);

// 程式主驅動函式
void update(bool key[]);

Trigger gTrigger(5, 5, 10);
int globalJumpX, globalJumpY;

int main(int argc, char** argv)
{
	srand(time(NULL));

	// 用來管理鍵盤輸入狀態的陣列
	bool gKeyState[6];
	for (int i = 0; i < 6; i++) {
		gKeyState[i] = false;
	}

	// Setup a clear dungeon
	setupBoard();

	gCreature.setPos(5, 6);

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
	}

	system("pause");
	return 0;
}

//******************************************************************
//
// * 偵測輸入狀態
//==================================================================
void keyUpdate(bool key[])
{
	for (int i = 0; i < ValidInput::INVALID; i++) {
		key[i] = false;
	}

	ValidInput inputType = ValidInput::INVALID;
	int jumpX = 0, jumpY = 0;

	input.clear(); // initialize input storage

	// Read from input and store into a char vector
	char cInput;
	do
	{
		cInput = getchar();
		input.push_back(cInput);
	} while (cInput != '\n');

	// press enter and renew the input
	if (input[0] == '\n')
	{
		input.clear();
		return;
	}

	Position hPos = gHero.getPos();
	char last = '\0'; // read the last character of the input string
	int deltaX = 0, deltaY = 0; // move unit

	// if command is "Move (x,y)" or "Jump (x,y)"
	if (input.size() >= 4)
	{
		deltaX = (int)(input[6] - '0'), deltaY = (int)(input[8] - '0');
		std::string cmd; // to see if it is move or jump
		cmd.push_back(input[0]);
		cmd.push_back(input[1]);
		cmd.push_back(input[2]);
		cmd.push_back(input[3]);

		if (deltaX >= 0 && deltaX <= 9 && deltaY >= 0 && deltaY <= 9) // check if it is valid number
		{
			if (cmd == "Move")
			{
				// check if it is only one unit
				if ((abs(hPos.x - deltaX) + abs(hPos.y - deltaY)) == 1
					|| (abs(hPos.y - deltaX) == 1 && abs(hPos.y - deltaY) == 1))
				{
					deltaX -= hPos.x;
					deltaY -= hPos.y;
					gHero.move(deltaX, deltaY);
					inputType = ValidInput::EMOVE;
				}
				else
				{
					std::cout << "Invalid input\n";
				}
			}
			else if (cmd == "Jump")
			{
				inputType = ValidInput::EJUMP;
			}
			else if (cmd == "Exit")
			{
				inputType = ValidInput::EESC;
			}
		}
		else
		{
			std::cout << "Invalid input\n";
		}
	}
	// if the command isn't move or jump, then read the last character
	if (input.size() >= 2)
	{
		last = input[input.size() - 2];
	}

	switch (last)
	{
	case 'w':
		inputType = ValidInput::EW;
		break;
	case 's':
		inputType = ValidInput::ES;
		break;
	case 'a':
		inputType = ValidInput::EA;
		break;
	case 'd':
		inputType = ValidInput::ED;
		break;
	default:
		break;
	}

	if (inputType == ValidInput::EW) {
		key[ValidInput::EW] = true;
	}
	else if (inputType == ValidInput::EA) {
		key[ValidInput::EA] = true;
	}
	else if (inputType == ValidInput::ES) {
		key[ValidInput::ES] = true;
	}
	else if (inputType == ValidInput::ED) {
		key[ValidInput::ED] = true;
	}
	else if (inputType == ValidInput::EESC) {
		key[ValidInput::EESC] = true;
	}
	else if (inputType == ValidInput::EMOVE) {
		key[ValidInput::EMOVE] = true;
	}
	else if (inputType == ValidInput::EJUMP) {
		key[ValidInput::EJUMP] = true;
		jumpX = deltaX;
		jumpY = deltaY;
		globalJumpX = jumpX;
		globalJumpY = jumpY;
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

//******************************************************************
//
// * Setup the board
//==================================================================
void setupBoard()
//==================================================================
{
	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			if (i == 0 || i == GHEIGHT - 1) {
				gBoard[i][j] = GWALL;
			}
			else if (j == 0 || j == GWIDTH - 1) {
				gBoard[i][j] = GWALL;
			}
			else {
				gBoard[i][j] = GNOTHING;
			}
		}
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
	char drawBoard[GHEIGHT][GWIDTH];

	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			drawBoard[i][j] = gBoard[i][j];
		}
	}

	Position t = gTrigger.getPos();
	drawBoard[t.y][t.x] = gTrigger.getIcon();

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
	Position hPos = gHero.getPos();
	std::cout << "The hero is level " << gHero.getLevel() << "(" << gHero.getExp() << "/" << gHero.getMaxExp() << " to level up)" << std::endl;
	std::cout << "The hero has " << gHero.getHP() << " hp" << std::endl;
	std::cout << "Use wsad key to move Hero " << gHero.getIcon() << std::endl;
	std::cout << "Every time you step on a trigger T, the hero gets " << gTrigger.getExpAmount() << " EXP points" << std::endl;
	std::cout << "Hero is at (" << hPos.x << "," << hPos.y << ")\n";
	std::cout << "Type Exit to exit" << std::endl;
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
	else if (key[ValidInput::EMOVE]) {
		hasInput = true;
	}
	else if (key[ValidInput::EJUMP]) {
		gHero.jump(globalJumpX, globalJumpY);
		hasInput = true;
	}
	else {
		std::cout << "invalid input\n";
	}
	gTrigger.update(gHero);
	gCreature.update(gHero);
	draw();
	drawInfo();
}
