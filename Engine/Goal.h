#pragma once
#include "Obstacle.h"
#include <random>

class Goal
{
public:
	Goal();
	Goal(std::mt19937& rng, Board& brd, Snake& snake);
	void Respawn(std::mt19937& rng , Board& brd, Snake& snake, Obstacle* obstacles,int nObstacles);
	void setBorder(Board& brd);
	void Draw(Board& brd);
	const Location& getLoc();
private:
	Location loc;
	Color c = Colors::Yellow;
	int b_startX;
	int b_endX;
	int b_startY;
	int b_endY;
};