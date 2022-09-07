#pragma once
#include "Graphics.h"
#include "Location.h"
//#include "Snake.h"
#include <assert.h>

class Board
{
public:
	Board(Graphics& gfx, int in_height, int in_width) :
		gfx(gfx)
	{
		width = in_width;
		height = in_height;
	}

	void DrawCell(const Location& loc, Color c);
	void DrawCellWithBorder(const Location& loc, Color c, int b_thickness);
	void GenerateBorder(int width, int height);
	void DrawBorder();
	int getGridX() const;
	int getGridY() const;
	const Location& getBorderStart();
	const Location& getBorderEnd();
	bool checkCollidingWithBorder(const Location& loc);

private:
	static constexpr int cellSize = 20;
	static constexpr Color BorderColor = Colors::Gray;
	int width;
	int height;
	int b_startX;
	int b_endX;
	int b_startY;
	int b_endY;
	Graphics& gfx;
	Location BorderTiles[136];
	int nBorderTiles = 0;

};
