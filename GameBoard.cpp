#include "GameBoard.h"


GameBoard::GameBoard()
{
	for (int i = 0; i < OCEAN_HEIGHT; i++)
	{
		for (int j = 0; j < OCEAN_WIDTH; j++)
		{
			this->ocean[i][j] = 'w';
		}
	}
}


GameBoard::~GameBoard()
{
}

string GameBoard::DisplayBoard(string userOrOpp)
{
	stringstream output;
	if (userOrOpp == "user")
	{
		output << BOARD_KEY_1 << endl << endl;
	}
	else
	{
		output << BOARD_KEY_2 << endl << endl;
	}

	output << "  ";
	for (int i = 1; i <= OCEAN_WIDTH; i++)
	{
		output << "  " << i;
	}
	output << endl;
	for (int i = 0; i < OCEAN_HEIGHT; i++)
	{
		output << char('A' + i) << " ";
		for (int j = 0; j < OCEAN_WIDTH; j++)
		{
			//Fills the output with all the hits and misses. If we are printing the opponent's board, it replaces 'B's with 'w'
			if (userOrOpp == "user" || ocean[i][j] != 'B')
			{
				output << "  " << ocean[i][j];
			}
			else
			{
				output << "  w";
			}
		}
		output << endl;

	}
	return output.str();
}

void GameBoard::Reset()
{
	for (int i = 0; i < OCEAN_HEIGHT; i++)
	{
		for (int j = 0; j < OCEAN_WIDTH; j++)
		{
			this->ocean[i][j] = 'w';
		}
	}
	theFleet.clear();
}

bool GameBoard::IsShip(Position thisPos)
{
	int x = thisPos.GetX() - 1;
	int y = thisPos.GetY();

	if (ocean[thisPos.GetY()][thisPos.GetX() - 1] == 'B')
	{
		return true;
	}
	return false;
}

bool GameBoard::InvalidGuess(Position thisPos)
{
	int x = thisPos.GetX() - 1;
	int y = thisPos.GetY();
	char thisLocation = ocean[thisPos.GetY()][thisPos.GetX() - 1];
	if (thisLocation == '0' || thisLocation == 'S' || thisLocation == 'H')
	{
		return true;
	}
	return false;
}

string GameBoard::GetLastGuess()
{
	stringstream output;
	output << char(lastGuess.GetYAsChar()) << int(lastGuess.GetX());
	return output.str();
}

int GameBoard::Guess(Position thisPos)
{
	if (InvalidGuess(thisPos))
	{
		return INVALID_GUESS;
	}
	lastGuess = thisPos;
	if (IsShip(thisPos))
	{
		ocean[thisPos.GetY()][thisPos.GetX() - 1] = 'H';
		for (int i = 0; i < theFleet.size(); i++)
		{
			if (theFleet[i].IsOnShip(thisPos))
			{
				if (theFleet[i].Hit())
				{
					SinkShip(theFleet[i]);
					return SUNK;
				}
				else
				{
					return HIT;
				}
			}
		}
		return HIT;
	}
	ocean[thisPos.GetY()][thisPos.GetX() - 1] = '0';
	return MISS;
}

vector<Position> GameBoard::FindOptions(Position thisPos, int ship)
{
	int length = 0;
	int x = thisPos.GetX() - 1;
	int y = thisPos.GetY();
	bool addUp = true;
	bool addDown = true;
	bool addLeft = true;
	bool addRight = true;
	vector<Position> validOptions;

	switch (ship)
	{
	case 0:
		length = 4;
		break;
	case 1:
		length = 3;
		break;
	case 2:
	case 3:
		length = 2;
		break;
	case 4:
		length = 1;
		break;
	default:
		length = 0;
		break;
	}
	//Right
	for (int i = 0; i <= length; i++)
	{
		if ((x + i) > 9 || ocean[y][x + i] == 'B')
		{
			addRight = false;
		}
	}
	if (addRight)
	{
		validOptions.push_back(Position(x + length + 1, y + 'A'));
	}
	//Left
	for (int i = 0; i <= length; i++)
	{
		if ((x - i) < 0 || ocean[y][x - i] == 'B')
		{
			addLeft = false;
		}
	}
	if (addLeft)
	{
		validOptions.push_back(Position(x - length + 1, y + 'A'));
	}

	//Down
	for (int i = 0; i <= length; i++)
	{
		if ((y + i) > 9 || ocean[y + i][x] == 'B')
		{
			addDown = false;
		}
	}
	if (addDown)
	{
		validOptions.push_back(Position(x + 1, y + length + 'A'));
	}
	//Up
	for (int i = 0; i <= length; i++)
	{
		if ((y - i) < 0 || ocean[y - i][x] == 'B')
		{
			addUp = false;
		}
	}
	if (addUp)
	{
		validOptions.push_back(Position(x + 1, y - length + 'A'));
	}

		

	return validOptions;
}

string GameBoard::AddShip(Position start, Position end)
{
	int startX = start.GetX() - 1;
	int startY = start.GetY();
	int endX = end.GetX() - 1;
	int endY = end.GetY();
	int length = abs((startX - endX) + (startY - endY)) + 1;
	stringstream output;

	if (startX == endX)
	{
		if (startY > endY)
		{
			for (int i = 0; i < length; i++)
			{
				ocean[endY + i][endX] = 'B';
			}
		}
		else
		{
			for (int i = 0; i < length; i++)
			{
				ocean[startY + i][endX] = 'B';
			}
		}
	}
	else
	{
		if (startX > endX)
		{
			for (int i = 0; i < length; i++)
			{
				ocean[endY][endX + i] = 'B';
			}
		}
		else
		{
			for (int i = 0; i < length; i++)
			{
				ocean[endY][startX + i] = 'B';
			}
		}
	}
	theFleet.push_back(Ship(start, end));
	output << "Ship Added!" << endl << DisplayBoard("user");
	return output.str();
}

void GameBoard::SinkShip(Ship sinkMe)
{
	vector<Position> sunkShip = sinkMe.GetShip();
	for (int i = 0; i < sunkShip.size(); i++)
	{
		int x = sunkShip[i].GetX() - 1;
		int y = sunkShip[i].GetY();
		ocean[y][x] = 'S';
	}
}

vector<Position> GameBoard::GetHits()
{
	vector<Position> hits;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (ocean[j][i] == 'H')
			{
				hits.push_back(Position(i, j, true));
			}
		}
	}
	return hits;
}

int GameBoard::MakeAutoGuess(GameBoard &user)
{
	if (autoProbables.size() > 0)
	{
		return AutoGuessNextProb(user);
	}
	else if (autoLeads.size() > 0)
	{
		return AutoGuessNextLead(user);
	}
	else
	{
		ResetLeads(user);
		return AutoGuessRandom(user);
	}
}

int GameBoard::AutoGuessRandom(GameBoard &user)
{
	int randSector = rand() % 2;
	int randX = (rand() % 5) * 2;
	int randY = (rand() % 5) * 2;
	if (randSector)
	{
		randX++;
		randY++;
	}
	Position randomPos(randX, randY, true);
	int result = user.Guess(randomPos);
	switch (result)
	{

		case INVALID_GUESS:
			return MakeAutoGuess(user);
			break;
		case HIT:
			MakeLeads(randomPos);
			return HIT;
		case SUNK:
			return SUNK;
		case MISS:
			return MISS;
		default:
			return 0;
	}
}

int GameBoard::AutoGuessNextLead(GameBoard &user)
{

	int result = user.Guess(autoLeads.front());
	if (result == INVALID_GUESS)
	{
		autoLeads.pop();
		return MakeAutoGuess(user);
	}
	else if (result == MISS)
	{
		autoLeads.pop();
		return MISS;
	}
	else if (result == SUNK)
	{
		autoLeads.pop();
		ResetLeads(user);
		return SUNK;
	}
	else if (result == HIT)
	{
		int direction = autoLeads.front().GetDirection();
		
		if (direction == DEAD)
		{
			autoLeads.pop();
		}
		else if (direction == UP)
		{
			Position next = autoLeads.front();
			Position previous = autoLeads.front();
			if (next.MoveUp())
			{
				next.SetDistance(abs(next.GetY() - 4.5));
				autoProbables.push(next);
			}
			if (previous.MoveDown() && previous.MoveDown())
			{
				previous.SetDistance(abs(previous.GetY() - 4.5));
				autoProbables.push(previous);
			}
		}
		else if (direction == DOWN)
		{
			Position next = autoLeads.front();
			Position previous = autoLeads.front();
			if (next.MoveDown())
			{
				next.SetDistance(abs(next.GetY() - 4.5));
				autoProbables.push(next);
			}
			if (previous.MoveUp() && previous.MoveUp())
			{
				previous.SetDistance(abs(previous.GetY() - 4.5));
				autoProbables.push(previous);
			}
		}
		else if (direction == LEFT)
		{
			Position next = autoLeads.front();
			Position previous = autoLeads.front();
			if (next.MoveLeft())
			{
				next.SetDistance(abs(next.GetX() - 4.5));
				autoProbables.push(next);
			}
			if (previous.MoveRight() && previous.MoveRight())
			{
				previous.SetDistance(abs(previous.GetX() - 4.5));
				autoProbables.push(previous);
			}
		}
		else if (direction == RIGHT)
		{
			Position next = autoLeads.front();
			Position previous = autoLeads.front();
			if (next.MoveRight())
			{
				next.SetDistance(abs(next.GetX() - 4.5));
				autoProbables.push(next);
			}
			if (previous.MoveLeft() && previous.MoveLeft())
			{
				previous.SetDistance(abs(previous.GetX() - 4.5));
				autoProbables.push(previous);
			}
		}
		autoLeads.pop();
		return HIT;
	}
	else
	{
		autoLeads.pop();
	}
}

int GameBoard::AutoGuessNextProb(GameBoard &user)
{
	int result = user.Guess(autoProbables.front());
	if (result == INVALID_GUESS)
	{
		autoProbables.pop();
		return MakeAutoGuess(user);
	}
	else if (result == MISS)
	{
		autoProbables.pop();
		return MISS;
	}
	else if (result == HIT)
	{
		int direction = autoProbables.front().GetDirection();
		ResetLeads(user);
		switch (direction)
		{
		case DEAD:
			autoProbables.pop();
			break;
		case UP:
			if (!autoProbables.front().MoveUp())
			{
				autoProbables.pop();
			}
			break;
		case DOWN:
			if (!autoProbables.front().MoveDown())
			{
				autoProbables.pop();
			}
			break;
		case RIGHT:
			if (!autoProbables.front().MoveRight())
			{
				autoProbables.pop();
			}
			break;
		case LEFT:
			if (!autoProbables.front().MoveLeft())
			{
				autoProbables.pop();
			}
			break;
		}
		return HIT;
	}
	else if (result == SUNK)
	{
		while (!autoProbables.empty())
		{
			autoProbables.pop();
		}
		while (!autoLeads.empty())
		{
			autoLeads.pop();
		}
		allHits.clear();
		allHits = user.GetHits();
		ResetLeads(user);
		return SUNK;
	}

}

void GameBoard::ResetLeads(GameBoard &user)
{
	while (!autoLeads.empty())
	{
		autoLeads.pop();
	}

	vector<Position> unsunkHits = user.GetHits();
	for (int i = 0; i < unsunkHits.size(); i++)
	{
		MakeLeads(unsunkHits[i]);
	}
}

void GameBoard::MakeLeads(Position lastHit)
{
	Position leftGuess = lastHit;
	Position rightGuess = lastHit;
	Position upGuess = lastHit;
	Position downGuess = lastHit;
	if (leftGuess.MoveLeft())
	{
		int distanceFromCenter = abs(leftGuess.GetX() - 4.5);
		leftGuess.SetDistance(distanceFromCenter);
		leftGuess.SetDirection(LEFT);
		autoLeads.push(leftGuess);
	}
	if (upGuess.MoveUp())
	{
		int distanceFromCenter = abs(upGuess.GetY() - 4.5);
		upGuess.SetDistance(distanceFromCenter);
		upGuess.SetDirection(UP);
		autoLeads.push(upGuess);
	}
	if (rightGuess.MoveRight())
	{
		int distanceFromCenter = abs(rightGuess.GetX() - 4.5);
		rightGuess.SetDistance(distanceFromCenter);
		rightGuess.SetDirection(RIGHT);
		autoLeads.push(rightGuess);
	}
	if (downGuess.MoveDown())
	{
		int distanceFromCenter = abs(downGuess.GetY() - 4.5);
		downGuess.SetDistance(distanceFromCenter);
		downGuess.SetDirection(DOWN);
		autoLeads.push(downGuess);
	}
}

int GameBoard::GetFleetSize()
{
	return theFleet.size();
}