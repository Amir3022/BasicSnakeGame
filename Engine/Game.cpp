/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	rng(rd()),
	brd(gfx,30,40),
	snake({19,14},brd)
	//,goal(rng,brd,snake)
{
	brd.GenerateBorder(30, 20);
	goal.setBorder(brd);
	goal.Respawn(rng, brd, snake,obstacles,nObstacles);
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!bGameOver && bGameStarted)
	{
		if (wnd.kbd.KeyIsPressed(VK_UP))
		{
			delta_loc = { 0,-1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			delta_loc = { 0,1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			delta_loc = { -1,0 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			delta_loc = { 1,0 };
		}
		moveCounter++;

		if (moveCounter >= moveRate)
		{
			bool bCollideWithObstalces = false;
			for (int i = 0; i < nObstacles; i++)
			{
				if (snake.checkColliding(obstacles[i].getLoc()))
				{
					bCollideWithObstalces = true;
					break;
				}
			}
			bGameOver = snake.getCollideWithBody() || snake.checkCollidingWithBorder() || bCollideWithObstalces;
			//Location next = snake.getNextLocation(delta_loc);
			if (!bGameOver)
			{
				moveCounter = 0;
				if (bEating)
				{
					snake.Grow();
					bEating = false;
				}
				snake.MoveBy(delta_loc);
				if (snake.checkColliding(goal.getLoc()))
				{
					bEating = true;
					goal.Respawn(rng, brd, snake, obstacles, nObstacles);
					score++;
					if (score % 5 == 0)
					{
						moveRate -= 2;
						if (moveRate < 5)
						{
							moveRate = 5;
						}
						obstacles[nObstacles].setBorder(brd);
						obstacles[nObstacles].Spawn(rng, brd, snake,goal.getLoc());
						nObstacles++;
					}
				}
			}
		}
	}
	else
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			bGameStarted = true;
		}
	}
	
}

void Game::ComposeFrame()
{
	/*std::uniform_int_distribution<int> distr(0, 255);
	for (int i = 0; i < brd.getGridY(); i++)
	{
		for (int j = 0; j < brd.getGridX(); j++)
		{
			Location loc = { j,i };
			Color c(distr(rng), distr(rng), distr(rng));
			brd.DrawCell(loc, c);
		}
	}
	*/
	if (!bGameStarted)
	{
		SpriteCodex::DrawTitle(300, 200, gfx);
	}
	else
	{
		goal.Draw(brd);
		brd.DrawBorder();
		for (int i = 0; i < nObstacles; i++)
		{
			obstacles[i].Draw(brd);
		}
		snake.Draw();		
	}
	if (bGameOver)
	{
		SpriteCodex::DrawGameOver(350,280,gfx);
	}
}
