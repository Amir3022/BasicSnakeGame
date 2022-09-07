#include "Board.h"
#include <cmath>

void Board::DrawCell(const Location& loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);
	gfx.DrawRectDim(loc.x * cellSize, loc.y * cellSize, cellSize, cellSize,c);
}

void Board::DrawCellWithBorder(const Location& loc, Color c, int b_thickness)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);
	gfx.DrawRectDimWithBorder(loc.x * cellSize, loc.y * cellSize, cellSize, cellSize, c, b_thickness);
}

void Board::GenerateBorder(int width, int height)
{
	assert(width > 0);
	assert(width <= getGridX());
	assert(height > 0);
	assert(height <= getGridY());
	b_startX = static_cast<int>(std::round((getGridX() / 2) - (width / 2)));
	b_endX = static_cast<int>(std::round((getGridX() / 2) + (width / 2)));
	b_startY = static_cast<int>(std::round((getGridY() / 2) - (height / 2)));
	b_endY = static_cast<int>(std::round((getGridY() / 2) + (height / 2)));
	for (int j = b_startY; j < b_endY; j++)
	{
		for (int i = b_startX; i < b_endX; i++)
		{
			if (j == b_startY || j == b_endY - 1)
			{
				BorderTiles[nBorderTiles] = Location{ i,j };
				nBorderTiles++;
			}
			else
			{
				if (i == b_startX || i == b_endX-1)
				{
					BorderTiles[nBorderTiles] = Location{ i,j };
					nBorderTiles++;
				}
			}
		}
	}
}

void Board::DrawBorder()
{
	for (int i = 0; i < nBorderTiles; i++)
	{
		DrawCell(BorderTiles[i], BorderColor);
	}
}


int Board::getGridX() const
{
	return width;
}

int Board::getGridY() const
{
	return height;
}

const Location& Board::getBorderStart()
{
	return Location{ b_startX,b_startY };
}

const Location& Board::getBorderEnd()
{
	return Location{ b_endX,b_endY };
}


bool Board::checkCollidingWithBorder(const Location& loc)
{
	for (int i = 0; i < nBorderTiles; i++)
	{
		if (loc == BorderTiles[i])
		{
			return true;
		}
	}
	return false;
}
