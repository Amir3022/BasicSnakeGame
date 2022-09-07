#pragma once
#include "Snake.h"
#include <random>

class Obstacle
{
public:
	Obstacle()
	{

	}
	void Spawn(std::mt19937& rng, Board& brd, Snake& snake,const Location& no_loc);
	void setBorder(Board& brd);
	void Draw(Board& brd);
	const Location& getLoc();
private:
	Location loc;
	Color c = Colors::Red;
	int b_startX;
	int b_endX;
	int b_startY;
	int b_endY;
};