#pragma once
#include <vector>
#include "Position.h"
class Ship
{
public:
	Ship();
	Ship(Position start, Position end);
	~Ship();
	bool Hit();
	bool IsOnShip(Position position);
	int GetSize();
	vector<Position> GetShip();


private:
	int length = 0;
	int hits = 0;
	vector<Position> location;
	bool sunk = false;
};

