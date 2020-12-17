// Author(s): Kermit Mitchell III
// Start Date: 02/19/2018 11:15 PM | Last Edited: 02/20/2018 1:55 AM
// This program allows two human players to play games of tic-tac-toe in the command line/console

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// Function Prototypes //

// This displays an error message when something invalid happens
void ErrorMessage(string msg);

// Structs and Classes //

struct State
{
private:
	// These represent the spaces on the game board, -1 for unplaced, 0 or false for 'O'; 1 or true for 'X';
	int topLeft = -1; // spot 1
	int topMiddle = -1; // spot 2
	int topRight = -1; // spot 3

	int middleLeft = -1; // spot 4
	int middleMiddle = -1; // spot 5
	int middleRight = -1; // spot 6

	int bottomLeft = -1; // spot 7
	int bottomMiddle = -1; // spot 8
	int bottomRight = -1; // spot 9

	// This determines what symbols to place on the gameboard
	char DisplaySpot(int spot)
	{
		char answer = '-';

		switch (spot)
		{
		default:
			answer = '-';
			break;
		case 0:
			answer = 'O';
			break;
		case 1:
			answer = 'X';
			break;
		}

		return answer;
	}

public:

	bool turnPlayer = 0; // 0 for 'O', 1 for 'X'; 'O' will always go first

	// Displays the current gameboard and turn player
	void DisplayState()
	{
		cout << DisplaySpot(this->topLeft) << "|" << DisplaySpot(this->topMiddle) << "|" << DisplaySpot(this->topRight) << endl;
		cout << DisplaySpot(this->middleLeft) << "|" << DisplaySpot(this->middleMiddle) << "|" << DisplaySpot(this->middleRight) << endl;
		cout << DisplaySpot(this->bottomLeft) << "|" << DisplaySpot(this->bottomMiddle) << "|" << DisplaySpot(this->bottomRight) << endl;

		if (this->turnPlayer)
		{
			cout << "Player X's turn" << endl;
		}
		else
		{
			cout << "Player O's turn" << endl;
		}
	}

	// Used to compare states
	bool operator==(const State& s)
	{
		bool result = false;

		if (this->topLeft == s.topLeft && this->topMiddle == s.topMiddle && this->topRight == s.topRight &&
			this->middleLeft == s.middleLeft && this->middleMiddle == s.middleMiddle && this->middleRight == s.middleRight &&
			this->bottomLeft == s.bottomLeft && this->bottomMiddle == s.bottomMiddle && this->bottomRight == s.bottomRight &&
			this->turnPlayer == s.turnPlayer)
		{
			result = true;
		}

		return result;
	}


	// Used to get a vector with all remaining unoccupied spots
	vector<int> ToVector()
	{
		vector<int> answer;

		if (topLeft == -1)
		{
			answer.push_back(1);
		}

		if (topMiddle == -1)
		{
			answer.push_back(2);
		}

		if (topRight == -1)
		{
			answer.push_back(3);
		}

		if (middleLeft == -1)
		{
			answer.push_back(4);
		}

		if (middleMiddle == -1)
		{
			answer.push_back(5);
		}

		if (middleRight == -1)
		{
			answer.push_back(6);
		}

		if (bottomLeft == -1)
		{
			answer.push_back(7);
		}

		if (bottomMiddle == -1)
		{
			answer.push_back(8);
		}

		if (bottomRight == -1)
		{
			answer.push_back(9);
		}

		return answer;
	}

	// Used to know if a goal state or unfavorable state has been met
	bool CheckDefeat(bool enemy)
	{
		bool answer = false; // assume the state is safe; that the enemy is not defeated
		char enemyChar = '?';
		// If the enemy is Player X
		if (enemy)
		{
			enemyChar = 'X';
			// Check for all X's in a row

			/*3 in a Row*/
			if (this->topLeft == 0 && this->topMiddle == 0 && this->topRight == 0)
			{
				answer = true;
			}
			else if (this->middleLeft == 0 && this->middleMiddle == 0 && this->middleRight == 0)
			{
				answer = true;
			}
			else if (this->bottomLeft == 0 && this->bottomMiddle == 0 && this->bottomRight == 0)
			{
				answer = true;
			}
			/*3 in a Column*/
			else if (this->topLeft == 0 && this->middleLeft == 0 && this->bottomLeft == 0)
			{
				answer = true;
			}
			else if (this->topMiddle == 0 && this->middleMiddle == 0 && this->bottomMiddle == 0)
			{
				answer = true;
			}
			else if (this->topRight == 0 && this->middleRight == 0 && this->bottomRight == 0)
			{
				answer = true;
			}
			/*3 in a Diaganol*/
			else if (this->topLeft == 0 && this->middleMiddle == 0 && this->bottomRight == 0)
			{
				answer = true;
			}
			else if (this->topRight == 0 && this->middleMiddle == 0 && this->bottomLeft == 0)
			{
				answer = true;
			}
		}
		else // If the enemy is Player O
		{
			enemyChar = 'O';
			// Check for all O's in a row

			/*3 in a Row*/
			if (this->topLeft == 1 && this->topMiddle == 1 && this->topRight == 1)
			{
				answer = true;
			}
			else if (this->middleLeft == 1 && this->middleMiddle == 1 && this->middleRight == 1)
			{
				answer = true;
			}
			else if (this->bottomLeft == 1 && this->bottomMiddle == 1 && this->bottomRight == 1)
			{
				answer = true;
			}
			/*3 in a Column*/
			else if (this->topLeft == 1 && this->middleLeft == 1 && this->bottomLeft == 1)
			{
				answer = true;
			}
			else if (this->topMiddle == 1 && this->middleMiddle == 1 && this->bottomMiddle == 1)
			{
				answer = true;
			}
			else if (this->topRight == 1 && this->middleRight == 1 && this->bottomRight == 1)
			{
				answer = true;
			}
			/*3 in a Diaganol*/
			else if (this->topLeft == 1 && this->middleMiddle == 1 && this->bottomRight == 1)
			{
				answer = true;
			}
			else if (this->topRight == 1 && this->middleMiddle == 1 && this->bottomLeft == 1)
			{
				answer = true;
			}
		}

		if (answer)
		{
			cout << "This state is a DEFEAT for Player " << enemyChar << endl;
		}
		else
		{
			cout << "This state is currently safe for Player " << enemyChar << endl;
		}

		return answer;
	}

	// This attempts to place a symbol onto the gameboard
	bool PickSpot(char row, char column)
	{
		bool success = true;
		// rows: 0, 1, 2 | columns: 0, 1, 2
		/*Top Row*/
		if (row == '0' && column == '0')
		{
			if (this->topLeft != -1)
			{
				ErrorMessage("This spot is already occupied.");
				success = false;
			}
			else
			{
				if (this->turnPlayer)
				{
					this->topLeft = 1;
				}
				else
				{
					this->topLeft = 0;
				}
			}
		}
		else if (row == '0' && column == '1')
		{
			if (this->topMiddle != -1)
			{
				ErrorMessage("This spot is already occupied.");
				success = false;
			}
			else
			{
				if (this->turnPlayer)
				{
					this->topMiddle = 1;
				}
				else
				{
					this->topMiddle = 0;
				}
			}
		}
		else if (row == '0' && column == '2')
		{
			if (this->topRight != -1)
			{
				ErrorMessage("This spot is already occupied.");
				success = false;
			}
			else
			{
				if (this->turnPlayer)
				{
					this->topRight = 1;
				}
				else
				{
					this->topRight = 0;
				}
			}
		}
		/*Middle Row*/
		else if (row == '1' && column == '0')
		{
			if (this->middleLeft != -1)
			{
				ErrorMessage("This spot is already occupied.");
				success = false;
			}
			else
			{
				if (this->turnPlayer)
				{
					this->middleLeft = 1;
				}
				else
				{
					this->middleLeft = 0;
				}
			}
		}
		else if (row == '1' && column == '1')
		{
			if (this->middleMiddle != -1)
			{
				ErrorMessage("This spot is already occupied.");
				success = false;
			}
			else
			{
				if (this->turnPlayer)
				{
					this->middleMiddle = 1;
				}
				else
				{
					this->middleMiddle = 0;
				}
			}
		}
		else if (row == '1' && column == '2')
		{
			if (this->middleRight != -1)
			{
				ErrorMessage("This spot is already occupied.");
				success = false;
			}
			else
			{
				if (this->turnPlayer)
				{
					this->middleRight = 1;
				}
				else
				{
					this->middleRight = 0;
				}
			}
		}
		/*Bottom Row*/
		else if (row == '2' && column == '0')
		{
			if (this->bottomLeft != -1)
			{
				ErrorMessage("This spot is already occupied.");
				success = false;
			}
			else
			{
				if (this->turnPlayer)
				{
					this->bottomLeft = 1;
				}
				else
				{
					this->bottomLeft = 0;
				}
			}
		}
		else if (row == '2' && column == '1')
		{
			if (this->bottomMiddle != -1)
			{
				ErrorMessage("This spot is already occupied.");
				success = false;
			}
			else
			{
				if (this->turnPlayer)
				{
					this->bottomMiddle = 1;
				}
				else
				{
					this->bottomMiddle = 0;
				}
			}
		}
		else if (row == '2' && column == '2')
		{
			if (this->bottomRight != -1)
			{
				ErrorMessage("This spot is already occupied.");
				success = false;
			}
			else
			{
				if (this->turnPlayer)
				{
					this->bottomRight = 1;
				}
				else
				{
					this->bottomRight = 0;
				}
			}
		}
		else
		{
			ErrorMessage("Invalid row and column options.");
			success = false;
		}

		return success;
	}

};


// This shows the scoreboard
void DisplayScore(int h, int a, int d);

// This changes the state of the game by trying to place a symbol onto the game board, and returning the new resulting state
State AttemptDecision(State current, int optionNum);

// Global variables //
bool player1ID = 0; // this is used to keep track of which symbol is tied to player 1; 0 or false for 'O'; 1 or true for 'X';
int player1Wins = 0;
int player2Wins = 0;
int draws = 0;
int decisionNum = 0; // used to keep track of the player's decisions

int main()
{
	// Declare the variables

	// This is the starting state
	State starting;

	int turnCounter = 0;
	char userInput = ' '; // for user input use

	do
	{
		// reset these variables every new match
		turnCounter = 0; 
		bool isGameFinished = false; // only true when a game has completed
		State current = starting; // the current state of the game

		// Ask for intial user input
		do
		{
			DisplayScore(player1Wins, player2Wins, draws);
			cout << "Welcome to Kermit Mitchell III's Tic-Tac-Toe! \nPlayer1, would you like to go first? (Y/N): " << endl;
			userInput = ' ';
			cin >> userInput;
			if (userInput == 'Y')
			{
				player1ID = 0;
				cout << "OK. Player 1 will be 'O' and Player 2 will be 'X'" << endl;
				system("pause");
			}
			else if (userInput == 'N')
			{
				player1ID = 1;
				cout << "OK. Player 1 will be 'X' and Player 2 will be 'O'" << endl;
				system("pause");
			}
			else
			{
				system("CLS");
				ErrorMessage("Invalid input. Please try again.");
				cin.ignore(1000, '\n'); cin.clear(); 
			}
		} while (userInput != 'Y' && userInput != 'N'); // repeat until a valid confirm option is entered



		while (!isGameFinished)
		{
			// Create the temp state for manipulation
			State temp = current;

			// To detect draws
			turnCounter++;
			if (turnCounter > 9 || current.ToVector().empty()) // Clearly a draw if at least 9 turns have passed, or there are no more unoccupied spots to pick from!
			{
				current.DisplayState();
				cout << "It's a draw..." << endl;
				draws++;
				break;
			}

			
			
				// Display the board and prompt the player to pick a spot
				do
				{
					current.DisplayState();
					cout << "Pick an unoccupied spot to mark: " << endl;

					char row = ' ';
					char column = ' ';
					userInput = ' ';

					do
					{
						row = userInput = column = ' ';
						cin.ignore(1000, '\n'); cin.clear();
						cout << "Enter row (0/1/2) then a comma (,) and then Enter column (0/1/2): " << endl;
						cin >> row;
						cin >> userInput; // to capture the comma (,)
						cin >> column;
						if (userInput != ',') 
						{
							ErrorMessage("Invalid syntax. Please remember the comma inbetween row and column choices.");
						}
						if ((row != '0' && row != '1' && row != '2') || (column != '0' && column != '1' && column != '2'))
						{
							ErrorMessage("Invalid row and column options. Please try again.");
						}
					} while (userInput != ',' || (row != '0' && row != '1' && row != '2') || (column != '0' && column != '1' && column != '2'));

					// Confirm the player's choice
					do
					{
						cin.ignore(1000, '\n'); cin.clear(); userInput = ' ';
						cout << "Are you sure you want this spot: " << row << "," << column << " (Y/N): " << endl;
						cin >> userInput;
						if (userInput != 'Y' && userInput != 'N')
						{
							ErrorMessage("Invalid option. Please try again.");
						}
					} while (userInput != 'Y' && userInput != 'N'); // repeat until a valid confirm option is entered

					if (userInput == 'Y')
					{
						// Determine corresponding option num, i

						if (row == '0' && column == '0')
						{
							decisionNum = 1;
						}
						else if (row == '0' && column == '1')
						{
							decisionNum = 2;
						}
						else if (row == '0' && column == '2')
						{
							decisionNum = 3;
						}
						/*Middle Row*/
						else if (row == '1' && column == '0')
						{
							decisionNum = 4;
						}
						else if (row == '1' && column == '1')
						{
							decisionNum = 5;
						}
						else if (row == '1' && column == '2')
						{
							decisionNum = 6;
						}
						/*Bottom Row*/
						else if (row == '2' && column == '0')
						{
							decisionNum = 7;
						}
						else if (row == '2' && column == '1')
						{
							decisionNum = 8;
						}
						else if (row == '2' && column == '2')
						{
							decisionNum = 9;
						}

						// Attempt the player's decision
						temp = AttemptDecision(temp, decisionNum);
						if (temp == current)
						{
							cout << "Please pick a different spot." << endl;
						}
					}

				} while (temp == current); // repeat until a game changing decision is made

				// Update the state of the game
				current = temp;

				// Determine if a victory condition has been met
				if (current.CheckDefeat(current.turnPlayer))
				{
					isGameFinished = true;
					cout << "GAME OVER!" << endl;
					if (current.turnPlayer == player1ID)
					{
						cout << "Player2 is victorious!" << endl;
						player2Wins++;
					}
					else
					{
						cout << "Player1 is victorious!" << endl;
						player1Wins++;
					}
					current.DisplayState();
					
				}

			// Go on to the next turn
		}

		// At this point, a game has concluded:
		DisplayScore(player1Wins, player2Wins, draws);
		do
		{
			cin.ignore(1000, '\n'); cin.clear(); userInput = ' ';
			cout << "Would you like to play again? (Y/N): " << endl;
			cin >> userInput;
			if (userInput != 'Y' && userInput != 'N')
			{
				ErrorMessage("Invalid input. Please try again.");
			}

		} while (userInput != 'Y' && userInput != 'N'); // repeat until a valid confirm option is entered
		system("CLS");

	} while (userInput == 'Y');

	// Display the results

	cout << "Thanks for playing Kermit Mitchell III's Tic-Tac-Toe!\nNow exiting..." << endl;

	// End the program
	system("pause");
	return 0;
}

void ErrorMessage(string msg)
{
	cout << "Error! " << msg << endl;
}

void DisplayScore(int h, int a, int d)
{
	cout << "SCORE: " << "Player1: " << h << " | Player2: " << a << " | Draws: " << d << endl;
}


State AttemptDecision(State current, int optionNum)
{
	State newState = current;

	// Check the optionNum

	switch (optionNum)
	{
	default:
		cout << "Invalid option. Options range from 1-9." << endl;
		break;
	case 1:
		cout << "Option 1: Top Left" << endl;
		if (newState.PickSpot('0', '0'))
		{
			newState.turnPlayer = !newState.turnPlayer; // Switch the turn player to handle control over
		}
		break;
	case 2:
		cout << "Option 2: Top Middle" << endl;
		if (newState.PickSpot('0', '1'))
		{
			newState.turnPlayer = !newState.turnPlayer;
		}
		break;
	case 3:
		cout << "Option 3: Top Right" << endl;
		if (newState.PickSpot('0', '2'))
		{
			newState.turnPlayer = !newState.turnPlayer;
		}
		break;
	case 4:
		cout << "Option 4: Middle Left" << endl;
		if (newState.PickSpot('1', '0'))
		{
			newState.turnPlayer = !newState.turnPlayer;
		}
		break;
	case 5:
		cout << "Option 5: Middle Middle" << endl;
		if (newState.PickSpot('1', '1'))
		{
			newState.turnPlayer = !newState.turnPlayer;
		}
		break;
	case 6:
		cout << "Option 6: Middle Right" << endl;
		if (newState.PickSpot('1', '2'))
		{
			newState.turnPlayer = !newState.turnPlayer;
		}
		break;
	case 7:
		cout << "Option 7: Bottom Left" << endl;
		if (newState.PickSpot('2', '0'))
		{
			newState.turnPlayer = !newState.turnPlayer;
		}
		break;
	case 8:
		cout << "Option 8: Bottom Middle" << endl;
		if (newState.PickSpot('2', '1'))
		{
			newState.turnPlayer = !newState.turnPlayer;
		}
		break;
	case 9:
		cout << "Option 9: Bottom Right" << endl;
		if (newState.PickSpot('2', '2'))
		{
			newState.turnPlayer = !newState.turnPlayer;
		}
		break;
	}

	return newState;
}

