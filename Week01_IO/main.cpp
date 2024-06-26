/************************************************************************
File:   Source.cpp

Author:
		Áé½å¼s¡Aea5878158@gmail.com
Modifier:
		¿à¯§¦N¡Acheeryuchi@gmail.com
		³¯«T¦t¡AJYCReports@gmail.com
Comment:
		Output W,A,S,D after input, ESC to stop process.

************************************************************************/
#include <iostream>	// For print out information
#include <conio.h>	// For getch() function

// Define inputs and its index
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

// Detect state of input
void keyUpdate(bool key[]);

int main()
{
	//Initialize state of key
	bool gKeyState[ValidInput::INVALID];

	// Obtain and update the input using a loop
	/************************************************************************/
	/*Please implement your code here*/

	bool* keyState = gKeyState;

	for (int i = 0; i < ValidInput::INVALID; i++)
	{
		gKeyState[i] = false;
	}

	// keep update the state until esc 
	while (*(keyState + ValidInput::EESC) == false)
	{
		keyUpdate(keyState);
	}

	return 0;
	/************************************************************************/
}

//******************************************************************
//
// * °»´ú¿é¤Jª¬ºA
//==================================================================
void keyUpdate(bool key[])
//==================================================================
{
	for (int i = 0; i < ValidInput::INVALID; i++) {
		key[i] = false;
	}
	char input = _getch();

	// Implement a switch for output calls
	/************************************************************************/
	/*Please implement your code here*/

	switch (input)
	{
	case 'W':
		key[ValidInput::EW] = true;
		std::cout << "Key W is pressed.\n";
		break;
	case 'w':
		key[ValidInput::EW] = true;
		std::cout << "Key W is pressed.\n";
		break;
	case 'S':
		key[ValidInput::ES] = true;
		std::cout << "Key S is pressed.\n";
		break;
	case 's':
		key[ValidInput::ES] = true;
		std::cout << "Key S is pressed.\n";
		break;
	case 'A':
		key[ValidInput::EA] = true;
		std::cout << "Key A is pressed.\n";
		break;
	case 'a':
		key[ValidInput::EA] = true;
		std::cout << "Key A is pressed.\n";
		break;
	case 'D':
		key[ValidInput::ED] = true;
		std::cout << "Key D is pressed.\n";
		break;
	case 'd':
		key[ValidInput::ED] = true;
		std::cout << "Key D is pressed.\n";
		break;
	case 27:
		key[ValidInput::EESC] = true;
		std::cout << "Key ESC is pressed. End program.\n";
		break;
	default:
		key[ValidInput::INVALID] = true;
		std::cout << "Invalid input.\n";
		break;
	}



	/************************************************************************/
}
