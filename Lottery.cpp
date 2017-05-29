//Olufisayo Joseph Ayodele
//Lottery.cpp
//This is where the implements a lottery game simulation that involves the 40 images

#include <iostream>
#include <ctime>
#include "Lottery.h"
#include "graph1.h"

Lottery::Lottery()
{
	this-> no_balls = no_balls;
	this-> yourNumbers = NULL;
	this-> winningNumbers = NULL;
	this-> matches = matches;
}

Lottery::~Lottery()
{
	delete[] yourNumbers;
	delete[] winningNumbers;
}

int Lottery::getNoBalls()
{
	return no_balls;
}

bool Lottery::setNoBalls(int no_balls)
{
	if (no_balls < 3) 
	{
		this->no_balls = 3;
		return false;
	}
	else if (no_balls > 10)
	{
		this->no_balls = 10;
		return false;
	}
	else
	{
		this->no_balls = no_balls;
		return true;
	}

}

bool Lottery::addNumber(int num)
{
	if (yourNumbers == NULL)
	{
		this->yourNumbers = new int[no_balls];
		for (int i = 0; i < no_balls; i++)
		{
			this->yourNumbers[i] = NULL;
		}
	}
	if (num < 1 || num > 40)
	{
		return true;
	}
	for (int i = 0; i < no_balls; i++)
	{
		if (num == yourNumbers[i])
		{
			return true;
		}
		else if (yourNumbers[i] == NULL)
		{
			yourNumbers[i] = num;
			return false;
		}
	}
	return true;
}

void Lottery::displayYourNumbers()
{
	char card_image[7];
	selectionSort();

	for (int i = 0; i < no_balls; i++)
	{
		sprintf_s(card_image, 10, "%d.bmp", yourNumbers[i]);
 		displayBMP(card_image, (i * 60) + 40, 340);
	}
	gout << setPos(60, 360) << "Your Numbers" << endg;
}

void Lottery::processWinningNumbers()
{
	srand(time(0)); 
	bool duplicate = true; char card_image[7];

	if (winningNumbers == NULL)
		this->winningNumbers = new int[no_balls];

	for (int i = 0; i < no_balls; i++)
	{
		winningNumbers[i] = (rand() % no_balls) + 1;
		do {
			duplicate = false;
			for (int j = 0; j < i; j++)
			{
				if (winningNumbers[i] == winningNumbers[j])
				{
					winningNumbers[i] = (rand() % no_balls) + 1;
					duplicate = true;
					break;
				}
			}
		} while (duplicate);

		sprintf_s(card_image, 7, "%d.bmp", winningNumbers[i]);
		displayBMP(card_image, (i * 60) + 40, 220);
		Sleep(1000);
	}

	this->insertionSort();
	Sleep(3000);

	for (int i = 0; i < no_balls; i++)
	{
		sprintf_s(card_image, 7, "%d.bmp", winningNumbers[i]);
		displayBMP(card_image, (i * 60) + 40, 220);
		Sleep(1000);
	}
	gout << setPos(60, 220) << "Winning Numbers" << endg;
}

void Lottery::selectionSort()
{
	int i = 0; int j = 0; int temp = 0;
	int smallest = 0;  int sm_index = 0;

	for (i = 0; i < no_balls; i++)
	{
		smallest = yourNumbers[i];
		sm_index = i;

		for (j = i + 1; j < no_balls; j++)
		{
			if (yourNumbers[j] < smallest)
			{
				smallest = yourNumbers[j];
				sm_index = j;
			}
		}

		if (smallest < yourNumbers[i])
		{
			temp = yourNumbers[i];
			yourNumbers[i] = yourNumbers[sm_index];
			yourNumbers[sm_index] = temp;
		}
	}
}

void Lottery::insertionSort()
{
	int i = 0; int j = 0; int v = 0;

	for (i = 0; i < no_balls; i++)
	{
		// Look back through the previous (sorted) elts.
		// Insert this elt after first that is smaller,
		// moving the others up as you go by them.
		v = yourNumbers[i];
	}
	for (j = i - 1; j >= 0 && yourNumbers[j] > v; j--)
	{
		// yourNumbers[j] is bigger; move it up
		yourNumbers[j + 1] = yourNumbers[j];
	}

	// yourNumbers[j] <= v; put v after yourNumbers[j]
	yourNumbers[j + 1] = v;
}

int Lottery::getMatches()
{
	return matches;
}

int Lottery::binarySearch(int target)
{
	int low = 0;
	int high = no_balls - 1;
	int middle = 0;
	int index = -1;
	bool found = false;

	while ((low <= high) && (!found))
	{
		middle = (low + high) / 2;

		if (winningNumbers[middle] == target)
			found = true;
		else if (target > winningNumbers[middle])
			low = middle + 1;
		else
			high = middle - 1;
	}

	if (!found)
	{
		index = -1;
	}
	else
	{
		index = middle;
	}
	return(index);
}

int Lottery::computeWinnings()
{
	int matches = 0;
	int winnings = 0;

	for (int i = 0; i < no_balls; i++)
	{
		if (binarySearch(yourNumbers[i]) != -1)matches + 1;
	}

	winnings = pow(10.0, matches);
	return(winnings);
}