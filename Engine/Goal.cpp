#include "Goal.h"

Goal::Goal()
{

}

Goal::Goal(std::mt19937& rng, Board& brd, Snake& snake)
{
	//Respawn(rng, brd, snake);
}

void Goal::Respawn(std::mt19937& rng, Board& brd, Snake& snake, Obstacle* obstacles, int nObstacles)
{
	std::uniform_int_distribution<int> distrX(b_startX,  b_endX);
	std::uniform_int_distribution<int> distrY(b_startY, b_endY);
	bool bCollide ;
	do
	{
		loc = { distrX(rng),distrY(rng) };
		bCollide = false;
		for (int i = 0; i < nObstacles; i++)
		{
			if (loc == obstacles[i].getLoc())
			{
				bCollide = true;
				break;
			}
		}
	} while (snake.checkColliding(loc) && bCollide);
}

void Goal::setBorder(Board& brd)
{
	b_startX = brd.getBorderStart().x+2;
	b_startY = brd.getBorderStart().y+2;
	b_endX = brd.getBorderEnd().x-3;
	b_endY = brd.getBorderEnd().y-3;
}

void Goal::Draw(Board& brd)
{
	brd.DrawCell(loc, c);
}

const Location& Goal::getLoc()
{
	return loc;
}
