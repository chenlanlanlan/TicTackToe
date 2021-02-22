#include <iostream>
#include <string>
#include <stdexcept>
#include <set>
#include <stdlib.h>

#define GRID_SIZE 3

using namespace std;

class Game
{
private:
	char grid[GRID_SIZE][GRID_SIZE];
	//win condition: 3 in a row / col / diagonal
	set<string> winConditions
	{
		"012", "345", "678", //row
		"036", "147", "258", //col
		"048", "246"		 // diagonal
	};
	void initializeGrid()
	{
		char c = ' ';
		for (int x = 0; x < GRID_SIZE; x++)
		{
			for (int y = 0; y < GRID_SIZE; y++)
			{
				grid[x][y] = c;
			}
		}
	}

public:
	Game()
	{
		initializeGrid();
		showGrid();
		while (true)
		{
			getInput();
			showGrid();
			checkWins();

			computerTurn();
			showGrid();
			checkWins();
		}
	}
	void checkWins()
	{

		set<char> xSet;
		set<char> oSet;

		for (int row = 0; row < GRID_SIZE; row++)
		{
			for (int col = 0; col < GRID_SIZE; col++)
			{
				if (grid[row][col] == 'X')
				{
					xSet.insert(to_string(row * GRID_SIZE + col).c_str()[0]);
				}
				else if (grid[row][col] == 'O')
				{
					oSet.insert(to_string(row * GRID_SIZE + col).c_str()[0]);
				}
			}
		}

		for (string str : winConditions)
		{
			int xCount = 0;
			int oCount = 0;
			for (char c : str)
			{
				if (xSet.find(c) != xSet.end())
				{
					xCount++;
				}
				if (oSet.find(c) != oSet.end())
				{
					oCount++;
				}
			}
			if (xCount == 3)
			{
				showGrid();
				cout << " ****** X wins ******* " << endl;
				exit(0);
				break;
			}
			if(oCount == 3)
			{
				showGrid();
				cout << " ****** O wins ******* " << endl;
				exit(0);
				break;
			}
		}
	}

	void computerTurn()
	{
		cout<<"Computer's turn" << endl;
		set<char> xSet;
		for (int row = 0; row < GRID_SIZE; row++)
		{
			for (int col = 0; col < GRID_SIZE; col++)
			{
				if (grid[row][col] == 'X')
				{
					cout<<"X position: "<<row * GRID_SIZE + col<<endl;
					xSet.insert(to_string(row * GRID_SIZE + col).c_str()[0]);
				}
			}
		}

		set<string> xPossibleWins;
		
		for (string str : winConditions)
		{
			for(char c : str)
			{
				if (xSet.find(c) != xSet.end())
				{
					xPossibleWins.insert(str);
				}
			}
		}
		
		set<int> possibleMoves;

		for(string str : xPossibleWins)
		{
			for(char c :str)
			{
				int pos = c - '0';
				possibleMoves.insert(pos);
			}
		}
		for(int pos : possibleMoves)
		{
			int row = pos / 3;
			int col = pos % 3;
			if(grid[row][col] == 'X' || grid[row][col] == 'O')
			{
				continue;
			}
			else
			{
				cout<<"Computer choose: " << pos << endl;
				grid[row][col] = 'O';
				break;
			}
		}
	}

	void getInput()
	{
		string input;
		while (true)
		{
			cout << "Input your desired position: " << endl;
			getline(cin, input);
			// input validation
			if (input != "")
			{
				int pos;
				try
				{
					pos = stoi(input);
				}
				catch (const std::invalid_argument &ia)
				{
					cout << "Please enter a number!" << endl;
					continue;
				}
				if (stoi(input) > 9 || stoi(input) < 1)
				{
					cout << "The desired position cannot be less than 1 or greater than 9!" << endl;
				}
				else
				{
					pos = stoi(input) - 1;
					int row = pos / 3;
					int col = pos % 3;
					char currGrid = grid[row][col];
					if (currGrid == 'X' || currGrid == 'O')
					{
						cout << "This position has been taken, please input another position " << endl;
					}
					else
					{
						grid[row][col] = 'X';
						break;
					}
				}
			}
			else
			{
				cout << "The desired position cannot be empty!" << endl;
			}
		}
	}

	void showGrid()
	{
		cout << "-------------" << endl;
		for (int x = 0; x < GRID_SIZE; x++)
		{
			cout <<"|";
			for (int y = 0; y < GRID_SIZE; y++)
			{
				cout << " " << grid[x][y] << " |";
			}
			cout << endl
				 << "-------------" << endl;
		}
	}
};

int main()
{
	Game game;
	return 0;
}