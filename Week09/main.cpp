/************************************************************************
File:   source.cpp

Author:
		鍾賢廣，ea5878158@gmail.com
Modifier:
		賴祐吉，cheeryuchi@gmail.com
		黃欣云，windyhuang6@gmail.com
		陳俊宇，JYCReports@gmail.com
		邱嘉興，tbcey74123@gmail.com
Comment:
		基本輸入方向移動功能，w s a d 移動腳色上下左右，空白改變腳色站立之地板字元，到T上可以增加經驗
		ESC是離開畫面。同時更新圖版上的資訊。

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
	ESave = 6,
	ELoad = 7,
	INVALID,
};


Creature gCreature;

// function declare
// 偵測輸入狀態
void keyUpdate(bool key[]);
// 初始化版面
void setupBoard(int rowN, int colN);
// 輸出版面
void draw(void);
// 輸出說明資訊
void drawInfo(void);

// 程式主驅動函式
void update(bool key[]);

void saveMap();
void loadMap();

// if loaded from file, then true
bool loadFlag = false;

std::vector<Trigger*> gTriggers;

int main(int argc, char** argv)
{
	srand(time(NULL));

	// 用來管理鍵盤輸入狀態的陣列
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
	loadFlag = false;
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
		if (cPos + dir * count == hPos) {
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

	Position hPos = getValidRandomPos();
	validFlags[hPos.y][hPos.x] = false;
	gHero.setPos(hPos);

	Position cPos = getValidRandomPos();
	validFlags[cPos.y][cPos.x] = false;
	gCreature.setPos(cPos);

	// to avoid additional trigger
	if (!loadFlag)
	{
		for (int i = 0; i < 2; i++) {
			Trigger* trigger = new Trigger();
			Position tPos = getValidRandomPos();
			validFlags[tPos.y][tPos.x] = false;
			trigger->setPos(tPos);
			gTriggers.push_back(trigger);
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
	// 清除版面
	system("CLS");

	Position delta;

	// 是否有input
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
	else if (key[ValidInput::ESave]) {
		saveMap();
		hasInput = true;
	}
	else if (key[ValidInput::ELoad]) {
		loadMap();
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

// Intent: save the map status to file
// Pre: cannot save the map status
// Post: map status saved to the file
void saveMap() {
	// Save dungen to file

	std::ofstream file("dungeon.txt");
	if (!file)
	{
		std::cout << "File opening error.\n";
		return;
	}

	// save board size
	file << GWIDTH << " " << GHEIGHT << "\n";

	// save board
	for (int i = 0; i < GHEIGHT; i++)
	{
		for (int j = 0; j < GWIDTH; j++)
		{
			file << gBoard[i][j];
		}
		file << "\n";
	}

	// save hero
	file << gHero.getPos() << "\n" << gHero.getIcon() << " " << gHero.getLevel() << " " << gHero.getHP() << " " << gHero.getExp() << " " << gHero.getMaxExp() << "\n";

	// save creature position
	file << gCreature.getPos() << "\n";

	// save trigger
	file << gTriggers.size() << "\n";
	for (const auto& trigger : gTriggers)
	{
		file << trigger->getPos() << "\n";
	}

	file.close();
}

// Intent: load the map status from file
// Pre: cannot load the map status from file
// Post: map status changed to the one in the file
void loadMap() {
	// Load from file and reset the dungen

	std::ifstream file("dungeon.txt");

	if (!file)
	{
		std::cout << "Cannot open file.\n";
	}

	// clear board
	system("CLS");

	// clear trigger vector
	for (Trigger*& trigger : gTriggers) {
		delete trigger;
		trigger = nullptr;
	}

	gTriggers.clear();
	loadFlag = true;

	// load board size
	file >> GWIDTH >> GHEIGHT;
	
	// load board info.
	setupBoard(GHEIGHT, GWIDTH);

	// ignore board because it had already set up
	std::string line;

	for (int i = 0; i <= GHEIGHT; i++) {
		std::getline(file, line);
	}

	// load hero
	int heroEXP, heroHP, heroLevel, heroMaxExp;
	char heroIcon;
	Position heroPos;
	file >> heroPos;
	file >> heroIcon >> heroLevel >> heroHP >> heroEXP >> heroMaxExp;

	// set hero information
	gHero.setPos(heroPos);
	gHero.setIcon(heroIcon);
	gHero.setLevel(heroLevel);
	gHero.setHP(heroHP);
	gHero.setExp(heroEXP);
	gHero.SetMaxExp(heroMaxExp);

	// load creature
	Position creaturePos;
	file >> creaturePos;
	gCreature.setPos(creaturePos); // set creature information

	// load trigger number
	int triggerNum;
	file >> triggerNum;

	// load and set creature information
	for (int i = 0; i < triggerNum; i++)
	{
		Position triggerPos;
		file >> triggerPos;
		Trigger* trigger = new Trigger();
		trigger->setPos(triggerPos);
		gTriggers.push_back(trigger);
	}

	file.close();
}
