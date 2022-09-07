#include "Obstacle.h"
#include <cmath>

void Obstacle::Spawn(std::mt19937& rng, Board& brd, Snake& snake, const Location& no_loc)
{
	std::uniform_int_distribution<int> distrX(b_startX, b_endX);
	std::uniform_int_distribution<int> distrY(b_startY, b_endY);
	do
	{
		loc = { distrX(rng),distrY(rng) };
	} while (snake.checkColliding(loc) && loc==no_loc);
}

void Obstacle::setBorder(Board& brd)
{
	b_startX = brd.getBorderStart().x + 2;
	b_startY = brd.getBorderStart().y + 2;
	b_endX = brd.getBorderEnd().x - 3;
	b_endY = brd.getBorderEnd().y - 3;
}

void Obstacle::Draw(Board& brd)
{
	brd.DrawCell(loc, c);
}

const Location& Obstacle::getLoc()
{
	return loc;
}