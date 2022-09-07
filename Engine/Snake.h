#pragma once
#include "Board.h"

class Snake
{
private:
	class Segment
	{
	private:
		Location loc;
		Color c;
	public:
		void InitHead(const Location& loc);
		void InitBody(int colorNum);
		void MoveToLoc(Location& loc,const Board& brd);
		void Draw(Board& brd);
		Location getLoc() const;
	};
private:
	static constexpr Color HeadColor=Color(91, 117, 98);
	static constexpr Color BodyColors[3] = { Color(11, 64, 26),Color(28, 92, 46),Color(61, 148, 85) };
	static constexpr int nSegmentsMax = 1200;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
	int bodyColor = 0;
	bool bCollideWithBody = false;
	Board& brd;

public:
	Snake(const Location& loc, Board& brd);
	void MoveBy(const Location& delta_loc);
	void Grow();
	void Draw();
	const Location& getNextLocation(const Location& delta_loc);
	bool checkColliding(const Location& loc);
	void checkCollidingWithItself();
	bool getCollideWithBody();
	bool checkCollidingWithBorder();
};


