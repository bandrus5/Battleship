#include "Ship.h"



Ship::Ship()
{
}

Ship::Ship(Position start, Position end)
{
	int startX = start.GetX();
	char startY = start.GetYAsChar();
	int endX = end.GetX();
	char endY = end.GetYAsChar();

	if (startX == endX)
	{
		if (startY < endY)
		{
			while (startY <= endY)
			{
				location.push_back(Position(startX, startY));
				startY++;
			}
		}
		else
		{
			while (endY <= startY)
			{
				location.push_back(Position(endX, endY));
				endY++;
			}
		}
	}
	else
	{
		if (startX < endX)
		{
			while (startX <= endX)
			{
				location.push_back(Position(startX, startY));
				startX++;
			}
		}
		else
		{
			while (endX <= startX)
			{
				location.push_back(Position(endX, endY));
				endX++;
			}
		}
	}
	length = location.size();
}

Ship::~Ship()
{
}


bool Ship::Hit()
{
	hits++;
	if (hits == length)
	{
		sunk = true;
	}
	return sunk;
}

bool Ship::IsOnShip(Position position)
{
	int x = position.GetX();
	int y = position.GetY();
	for (int i = 0; i < location.size(); i++)
	{
		if (location[i].GetX() == x && location[i].GetY() == y)
		{
			return true;
		}
	}
	return false;
}

int Ship::GetSize()
{
	return location.size();
}

vector<Position> Ship::GetShip()
{
	return location;
}