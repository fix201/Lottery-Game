//Olufisayo Joseph Ayodele
//Lottery.cpp
//This is the main file that implements a lottery game simulation that involves the 40 images

#include <iostream>
#include <ctime>
#include "Lottery.h"
#include "graph1.h"

using namespace std;

int main()
{
	//Variable Declaration/Initialization
	int no_balls = 0; int target = 0;
	int yourNumber = 0; 
	bool res = false;
	char repeat;
	Lottery lottery;

	//Display Graphics
	displayGraphics();

	do {
		//Prompts the user for the number of lottery balls 
		cout << "How many lottery balls do you want to play: "; cin >> no_balls;
		res = lottery.setNoBalls(no_balls);

		if (!res)
			cout << "Incorrect input\nPlease enter again: \n";

		//Prompts the user for lottery numbers
		for (int i = 0; i < lottery.getNoBalls(); i++)
		{
			do {
				cout << "Enter lottery # " << i + 1 << " (between 1 and 40): ";
				cin >> yourNumber;

				res = lottery.addNumber(yourNumber);
			} while (res);
		}

		lottery.selectionSort();
		lottery.displayYourNumbers();		
		lottery.processWinningNumbers();		
		lottery.computeWinnings();

		gout << setPos(80, 100) << "Number of Ball Played: " << lottery.getNoBalls() << endg;
		gout << setPos(80, 120) << "Number of Matches: " << lottery.getMatches() << endg;
		gout << setPos(80, 140) << "Your Payout: $" << lottery.computeWinnings() << endg;

		cout << "Repeat the program? (y/n): "; cin >> repeat;

	} while (repeat == 'y' || repeat == 'Y');
	return 0;
}
