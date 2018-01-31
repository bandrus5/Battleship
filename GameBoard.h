#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>
#include <queue>
#include "Position.h"
#include "Ship.h"
using namespace std;

const int OCEAN_HEIGHT = 10;
const int OCEAN_WIDTH = 10;

const string BOARD_KEY_1 = "w = open sea   H = hit   0 = miss   B = ship";
const string BOARD_KEY_2 = "w = unknown   H = hit   0 = miss   S = Sunken Enemy Ship";

enum results { SUNK, HIT, MISS, INVALID_GUESS };
enum directions { UP, DOWN, RIGHT, LEFT, DEAD };

class GameBoard
{
public:
	GameBoard();
	~GameBoard();
	string DisplayBoard(string userOrOpp);
	void Reset();
	bool IsShip(Position thisPos);
	vector<Position> FindOptions(Position thisPos, int ship);
	string AddShip(Position start, Position end);
	int Guess(Position thisPos);
	int MakeAutoGuess(GameBoard &user);
	int AutoGuessNextProb(GameBoard &user);
	int AutoGuessNextLead(GameBoard &user);
	int AutoGuessRandom(GameBoard &user);
	void SinkShip(Ship sinkMe);
	bool InvalidGuess(Position thisPos);
	vector<Position> GetHits();
	void ResetLeads(GameBoard &user);
	void MakeLeads(Position lastHit);
	int GetFleetSize();
	string GetLastGuess();

private:
	char ocean[OCEAN_WIDTH][OCEAN_HEIGHT];
	vector<Ship> theFleet;
	queue<Position> autoLeads;
	queue<Position> autoProbables;
	vector<Position> allHits;
	Position lastGuess;
};


