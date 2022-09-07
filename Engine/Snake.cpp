#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location& loc,Board& brd):
	brd(brd)
{
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location& delta_loc)
{
	for (int i = nSegments - 1; i > 0; i--)
	{
		segments[i].MoveToLoc(segments[i - 1].getLoc(),brd);
	}
	segments[0].MoveToLoc(Location::Add(segments[0].getLoc(), delta_loc),brd);
	checkCollidingWithItself();
}

void Snake::Grow()
{
	if (nSegments < nSegmentsMax)
	{
		segments[nSegments].InitBody(bodyColor);
		nSegments++;
		bodyColor++;
		if (bodyColor > 2)
		{
			bodyColor = 0;
		}
	}
}

void Snake::Draw()
{
	for (int i = nSegments-1; i >= 0; i--)
	{
		segments[i].Draw(brd);
	}
}

const Location& Snake::getNextLocation(const Location& delta_loc)
{
	return Location::Add(segments[0].getLoc(), delta_loc);
}

bool Snake::checkColliding(const Location& loc)
{
	for (int i = 0; i < nSegments; i++)
	{
		if (loc == segments[i].getLoc())
		{
			return true;
		}
	}
	return false;
}

void Snake::checkCollidingWithItself()
{
	for (int i = 1; i < nSegments; i++)
	{
		if (segments[0].getLoc() == segments[i].getLoc())
		{
			bCollideWithBody = true;
		}
	}
}

bool Snake::getCollideWithBody()
{
	return bCollideWithBody;
}

bool Snake::checkCollidingWithBorder()
{
	return brd.checkCollidingWithBorder(segments[0].getLoc());
}

void Snake::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snake::HeadColor;
}

void Snake::Segment::InitBody(int colorNum)
{
	c = Snake::BodyColors[colorNum];
}

void Snake::Segment::MoveToLoc(Location& in_loc, const Board& brd)
{
	if (in_loc.x < 0)
	{
		in_loc.x = brd.getGridX() - 1;
	}
	if (in_loc.x >= brd.getGridX())
	{
		in_loc.x = 0;
	}
	if (in_loc.y < 0)
	{
		in_loc.y = brd.getGridY() - 1;
	}
	if (in_loc.y >= brd.getGridY())
	{
		in_loc.y = 0;
	}
	loc = in_loc;
}

void Snake::Segment::Draw(Board& brd)
{
	//brd.DrawCell(loc, c);
	brd.DrawCellWithBorder(loc, c, 2);
}

Location Snake::Segment::getLoc() const
{
	return loc;
}