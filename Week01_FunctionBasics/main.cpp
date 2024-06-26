/************************************************************************
File:   Source.cpp

Author:
		Áé½å¼s¡Aea5878158@gmail.com
Modifier:
		¿à¯§¦N¡Acheeryuchi@gmail.com
		³¯«T¦t¡AJYCReports@gmail.com
Comment:
		Use clock to count time (And output) for following input tasks

************************************************************************/

#include <ctime>
#include <iostream>

int main(int argc, char** argv)
{
	clock_t startT, endT; // Variable to store the start of the gameloop
	startT = clock();
	endT = clock();
	clock_t globalStartT = startT;

	// Start the game loop
	/************************************************************************/
	/*Please implement your code here*/

	int msgCount = 0;
	while (clock() - globalStartT < 15000)
	{
		startT = clock();
		do
		{
			endT = clock();
		} while ((endT - startT) < 1000);

		std::cout << "Total time " << msgCount << " at " << (float)endT / 1000 << "\n";
		msgCount++;
	}

	return 0;
	/************************************************************************/

}
