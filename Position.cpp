#include "Position.h"



Position::Position()
{
}

Position::Position(int xCoor, char yCoor)
{
	this->xCoor = xCoor;
	this->yCoor = yCoor;
	if (yCoor < 11)
	{
		this->yCoor += 'A';
	}
}

Position::Position(int xCoor, int yCoor, bool basic)
{
	this->xCoor = xCoor + 1;
	this->yCoor = yCoor + 'A';
}

Position::Position(string coors)
{
	if (coors.length() == 3)
	{
		xCoor = 10;
	}
	else
	{
		xCoor = coors[1] - '0';
	}
	this->yCoor = coors[0];
}

Position::~Position()
{
}

string Position::ToString()
{
	stringstream output;
	output << char(yCoor) << xCoor;
	return output.str();
}

int Position::GetX()
{
	return xCoor;
}

int Position::GetY()
{
	return yCoor - 'A';
}

char Position::GetYAsChar()
{
	return yCoor;
}


bool Position::MoveUp()
{
	if (yCoor > 'A')
	{
		yCoor--;
		return true;
	}
	return false;
}

bool Position::MoveDown()
{
	if (yCoor < 'J')
	{
		yCoor++;
		return true;
	}
	return false;
}

bool Position::MoveRight()
{
	if (xCoor < 10)
	{
		xCoor++;
		return true;
	}
	return false;
}

bool Position::MoveLeft()
{
	if (xCoor > 1)
	{
		xCoor--;
		return true;
	}
	return false;
}

void Position::SetDirection(int direction)
{
	this->direction = direction;
}

int Position::GetDirection() const
{
	return direction;
}

void Position::SetDistance(double distance)
{
	this->distanceFromCenter = distance;
}

double Position::GetDistance()
{
	return distanceFromCenter;
}
/*
bool Position::operator< (const Position &p)
{
	if (distanceFromCenter > p.distanceFromCenter)
	{
		return true;
	}
	return false;
}


bool Position::operator== (const Position &p)
{
	if (distanceFromCenter == p.distanceFromCenter)
	{
		return true;
	}
	return false;
}
*/