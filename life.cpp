#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

void life(vector<vector<bool> > &gameBoard)
{
	vector<vector<bool> > tempBoard;
	tempBoard = gameBoard;
	
	for (unsigned int i = 1; i < tempBoard.size()-1; i++)
	{
		for (unsigned int j = 1; j < tempBoard.at(i).size()-1; j++)
		{
			int neighborCount = 0;
			neighborCount = gameBoard.at(i-1).at(j-1) +
							gameBoard.at(i-1).at(j)   +
							gameBoard.at(i-1).at(j+1) + 
							gameBoard.at(i).at(j-1)   +
							gameBoard.at(i).at(j+1)   +
							gameBoard.at(i+1).at(j-1) + 
							gameBoard.at(i+1).at(j)   +
							gameBoard.at(i+1).at(j+1);
							
			if (neighborCount < 2 || neighborCount > 3)
				tempBoard.at(i).at(j) = false;
				
			if (neighborCount == 3)
				tempBoard.at(i).at(j) = true;
		}
	}
	gameBoard = tempBoard;
}

void printBoard(vector<vector<bool> > gameBoard, string cell, bool wideMode)
{
	for (unsigned int i = 0; i < gameBoard.size(); i++)
	{
		for (unsigned int j = 0; j < gameBoard.at(i).size(); j++)
		{
			if (wideMode)
			{
				if (gameBoard.at(i).at(j) == 1)
					cout << cell << " ";
				else cout << "  "; 
			}
			else
			{
				if (gameBoard.at(i).at(j) == 1)
					cout << cell;
				else cout << " "; 
			}
		}
		cout << endl;
	}
}

void seedBoard(vector<vector<bool> > &gameBoard)
{
	for (unsigned int i = 1; i < gameBoard.size()-1; i++)
	{
		for (unsigned int j = 1; j < gameBoard.at(i).size()-1; j++)
		{
			gameBoard.at(i).at(j) = rand() % 2;
		}
	}
}

void setBlinker(vector<vector<bool> > &gameBoard)
{
	gameBoard.at(7).at(7) = true;
	gameBoard.at(7).at(8) = true;
	gameBoard.at(7).at(9) = true;
}

int main ()
{
	int x, y;
	cout << "Enter number of rows and columns: ";
	cin >> x >> y;
	
	vector<vector<bool> > gameBoard(x, vector<bool>(y, 0));

	
	int generations = 0;
	double timeStep = 0.0;
	string cells;
	char wideMode = 'n';
	
	cout << "how many generations?: ";
	cin >> generations;
	cout << "enter cell character: ";
	cin >> cells;
	cout << "Enter time step in seconds: ";
	cin >> timeStep;
	cout << "widescreen rendering? (y or n): ";
	cin >> wideMode;
	cout << endl;
	
	srand(time(NULL));
	seedBoard(gameBoard);
	
	for (int i = 0; i < generations; i++)
	{
		system("clear");
		
		cout << "generation: " << i+1 << endl; 
		if (wideMode == 'y')
			printBoard(gameBoard, cells, true);
		else 
			printBoard(gameBoard, cells, false);

		
		life(gameBoard);
		usleep(timeStep * 1000000);
	
	}
}
