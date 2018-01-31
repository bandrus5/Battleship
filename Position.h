#pragma once
#include <string>
#include <sstream>
#include <utility>
using namespace std;

class Position
{
public:
	Position();
	Position(int xCoor, char yCoor);
	Position(int xCoor, int yCoor, bool basic);
	Position(string coors);
	~Position();
	string ToString();
	int GetX();
	int GetY();
	char GetYAsChar();
	bool MoveUp();
	bool MoveDown();
	bool MoveRight();
	bool MoveLeft();
	void SetDirection(int direction);
	int GetDirection() const;
	void SetDistance(double distance);
	double GetDistance();
	//bool operator< (const Position &p);
	//bool operator== (const Position &p);

private:
	int xCoor = 1;
	char yCoor = 'A';
	int direction = 0;
	double distanceFromCenter = 0;
};

