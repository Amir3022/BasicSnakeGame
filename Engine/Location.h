#pragma once
struct Location
{
	static Location Add(const Location& val1,const Location& val2)
	{
		return { val1.x + val2.x,val1.y + val2.y };
	}
	bool operator == (const Location& val) const
	{
		return (x == val.x && y == val.y);
	}
	int x;
	int y;

};