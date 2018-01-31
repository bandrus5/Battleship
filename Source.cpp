#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "GameBoard.h"
#include "Position.h"

using namespace std;

const int NUMBER_OF_SHIPS = 5;


//Works
void Greet(string &userName)
{
	cout << "BATTLESHIP" << endl << endl;
	cout << "Created by Berkeley Andrus" << endl;
	cout << "Press Enter to Continue." << endl;
	cin.get();

	cout << "Welcome to Battleship, Admiral. What is your name? ";
	getline(cin, userName);
	cout << endl;
	cout << "Thanks, " << userName << ". I am your onboard computer system, and I will assist you through this war." << endl;


} //Works

//Works
bool IsNotValid(string &userInput)
{
	if (userInput[0] >= 'a' && userInput[0] <= 'j')
	{
		userInput[0] += 'A' - 'a';
	}

	if (userInput.length() > 3 || userInput.length() < 2)
	{
		return true;
	}
	if (userInput[0] < 'A' || userInput[0] > 'J')
	{
		
		return true;
		
	}

	if (userInput.length() == 3 && userInput[1] == '1' && userInput[2] == '0')
	{
		return false;
	}
	if (userInput.length() == 2 && isdigit(userInput[1]) && userInput[1] != '0')
	{
		return false;
	}
	return true;
} //

//Works
void AddUserShips(GameBoard &user)
{
	string userInput;
	string junk;
	int endOption = 0;
	vector<Position> endOptions;

	cout << "Our first task is to assemble our fleet! You have five ships to place on the 10 by 10 grid shown below." << endl;
	cout << user.DisplayBoard("user") << endl << endl;
	cout << "Press Enter to Continue." << endl;
	cin.get();
	cout << "For each ship, enter a letter (A-J) followed by a number (1-10). This will tell me where you want to start ";
	cout << "each ship." << endl << "I will then give you the options of where the other end should be based on the ship's";
	cout << " size and the available spots." << endl;
	cout << "If you want to start over, just type 'R' and we'll delete all the ships and start again." << endl;

	for (int i = 0; i < NUMBER_OF_SHIPS; i++)
	{
		cout << endl << "Enter the first end of your ship: ";
		getline(cin, userInput);

		//If "R", delete all ships and restart.
		if (userInput == "R" || userInput == "r")
		{
			user.Reset();
			cout << endl << "All ships have been removed. See, look! This is the ocean right now:" << endl;
			cout << user.DisplayBoard("user");
			i = -1;
			continue;
		}
		//If not Letter:Number, ask for another one.
		if (IsNotValid(userInput))
		{
			cout << endl << "Sorry, I didn't understand that. Please try again." << endl;
			i--;
			continue;
		}

		//If space is taken, ask for another one.
		Position newestPos = Position(userInput);
		if (user.IsShip(newestPos))
		{
			cout << "You already have a ship there!" << endl;
			i--;
			continue;
		}
		//Check which other ends are available.
		endOptions = user.FindOptions(newestPos, i);
		if (endOptions.size() == 0)
		{
			cout << "I'm sorry. If you start your ship there, it won't have anywhere to go!" << endl;
			i--;
			continue;
		}
		cout << "Okay, your ship can go from " << newestPos.ToString() << " to the following locations:" << endl;
		for (int i = 0; i < endOptions.size(); i++)
		{
			cout << i + 1 << ": " << endOptions[i].ToString() << endl;
		}
		cout << "Please select one (1-" << endOptions.size() << "):";
		cin >> endOption;
		while (cin.fail() || endOption < 1 || endOption > endOptions.size())
		{
			cin.clear();
			cin.ignore(UINT16_MAX, '\n');
			cout << "Hold up, that wasn't an option. Try again: " << endl;
			cin >> endOption;
		}
		cout << user.AddShip(newestPos, endOptions[endOption - 1]);
		cin.get();
	}
}

//Works
void AddOpponentShips(GameBoard &opponent)
{
	cout << "Alright, it looks like your opponent is assembling for war." << endl;
	cout << "This may take as long as .04 seconds, so please be patient." << endl;
	cout << "Press Enter to Continue." << endl;
	cin.get();
	char randomY;
	int randomX;
	int endOption = 0;
	vector<Position> endOptions;

	for (int i = 0; i < NUMBER_OF_SHIPS; i++)
	{

		randomY = rand() % 9 + 'A';
		randomX = rand() % 9 + 1;
		

		//If space is taken, ask for another one.
		Position newestPos = Position(randomX, randomY);
		if (opponent.IsShip(newestPos))
		{
			i--;
			continue;
		}
		//Check which other ends are available.
		endOptions = opponent.FindOptions(newestPos, i);
		if (endOptions.size() == 0)
		{
			i--;
			continue;
		}

		endOption = rand() % endOptions.size();
		opponent.AddShip(newestPos, endOptions[endOption]);
	}
	//cout << "Opponent's ships: " << endl;
	//cout << opponent.DisplayBoard("user");

}


void HumanTurn(GameBoard &user, GameBoard&opponent, string userName, int &userFleet, int &opponentFleet)
{
	string userGuess;
	int result = 0;

	cout << "Here's the enemy waters: " << endl;
	cout << opponent.DisplayBoard("opp");
	cout << "Where would you like to fire, " << userName << "? (Enter the letter first): ";
	getline(cin, userGuess);

	while (IsNotValid(userGuess))
	{
		cout << endl << "Sorry, I didn't understand that. Please try again." << endl;
		cout << endl << "Where would you like to fire? ";
		getline(cin, userGuess);
	}
	result = opponent.Guess(Position(userGuess));
	switch (result)
	{
	case INVALID_GUESS:
		cout << endl << "Looks like you've already fired there, Admiral. Try again." << endl;
		return HumanTurn(user, opponent, userName, userFleet, opponentFleet);
	case MISS:
		cout << endl << endl << userName << " guessed " << userGuess << " and missed! Better luck next time." << endl;
		cout << "Here's what we've gathered so far:" << endl;
		cout << opponent.DisplayBoard("opp");
		break;
	case HIT:
		cout << endl << endl << userName << " guessed " << userGuess << " and hit something! Nice work!" << endl;
		cout << "Here's what we've gathered so far:" << endl;
		cout << opponent.DisplayBoard("opp");
		break;
	case SUNK:
		cout << endl << endl << "YOU'VE SUNK THE OPPONENT'S BATTLESHIP! Or, well, one of its ships. I never learned ";
		cout << "the names of all of them..." << endl;
		opponentFleet--;
		if (opponentFleet == 0)
		{
			return;
		}
		cout << "Here's what we've gathered so far:" << endl;
		cout << opponent.DisplayBoard("opp");
		break;
	default:
		cout << "Error. BIIIIG Error." << endl;
		break;
	}
}

void AutoTurn(GameBoard &user, GameBoard&opponent, string userName, int &userFleet, int &opponentFleet)
{
	int result = opponent.MakeAutoGuess(user);
	switch (result)
	{
	case HIT:
		cout << "Your opponent has struck you, Admiral! It got a hit at " << user.GetLastGuess() << "." << endl;
		cout << "Here's your board: " << endl;
		cout << user.DisplayBoard("user");
		cout << "Your turn is next. Let's get back at those scoundrels!" << endl;
		return;
	case MISS:
		cout << "HA! Your opponent missed you by a mile. Or an inch. I don't really understand numbers." << endl;
		cout << "It shot at " << user.GetLastGuess() << " but you're safe." << endl;
		cout << "Here's your board: " << endl;
		cout << user.DisplayBoard("user");
		cout << "Your turn is next. Let's show these guys who's boss." << endl;
		return;
	case SUNK:
		cout << "Bad news, Admiral. It looks like you've lost a ship. You were struck at " << user.GetLastGuess() << "." << endl;
		userFleet--;
		if (userFleet)
		{
			cout << "But you're not done yet! Here's the remainder of your fleet." << endl << user.DisplayBoard("user");
			cout << "Let's hit them where it hurts!" << endl;
		}
		return;
	default:
		cout << "Um, something went wrong. I don't know what happened." << endl;
		return;
	}
}

void Play(GameBoard &user, GameBoard&opponent, string userName)
{
	int userFleet = 5;
	int opponentFleet = 5;
	string userGuess;
	string opponentGuess;


	cout << "Well, since you are the human one, I guess you can go first." << endl;

	while (userFleet && opponentFleet)
	{
		HumanTurn(user, opponent, userName, userFleet, opponentFleet);
		cout << "Press enter to let the robot guess." << endl;
		cin.get();
		AutoTurn(user, opponent, userName, userFleet, opponentFleet);
		cout << "Press enter to continue." << endl;
		cin.get();
	}

	cout << "Well, that's the game!" << endl;
	if (userFleet)
	{
		cout << "Congratulations, Admiral " << userName << "! You won! Here were both boards: " << endl;
		cout << user.DisplayBoard("user") << opponent.DisplayBoard("user");
	}
	else
	{
		cout << "I'm sorry, Admiral. You have lost the game." << endl;
		cout << user.DisplayBoard("user") << opponent.DisplayBoard("user");
	}
	return;
	
}


int main()
{
	srand(time(NULL));
	string userName;
	GameBoard user = GameBoard();
	GameBoard opponent = GameBoard();

	Greet(userName);
	
	AddUserShips(user);

	AddOpponentShips(opponent);

	Play(user, opponent, userName);
	
	cout << "Press enter to continue.";
	cin.get();
	return 0;
}


/*
1. Populate opponent's GameBoard




*/