#include "Missile.h"

Missile::Missile(GameMap* Observer, int Unit, int Way, int x, int y)
{
	MoveWay = Way;// 움직이는 방향
	MoveSpeed = 130;//움직이는 스피드
	FrameCounter = 0;
	m_Data.pt.x = x;
	m_Data.pt.y = y;
	m_Data.rt = {x, y, x + MISSILE_WIDTH, y + MISSILE_HEIGHT };
	m_Data.Type = Unit;
	ReadMap = Observer;
	Stand = true;
}

void Missile::SetMissileRect(int x, int y)
{
	m_Data.rt.left = x;
	m_Data.rt.top = y;
	if (MoveWay == LEFT || MoveWay == RIGHT)
	{
		m_Data.rt.right = x + MISSILE_WIDTH;
		m_Data.rt.bottom = y + MISSILE_HEIGHT;
	}
	else
	{
		m_Data.rt.right = x + MISSILE_HEIGHT;
		m_Data.rt.bottom = y + MISSILE_WIDTH;
	}
}

void Missile::SetFrameCounter(double Delta)
{
	FrameCounter += Delta;
	if (FrameCounter > 1)
		FrameCounter = 1;

	if (FrameCounter == 1)
	{
		FrameCounter = 0;
		m_Data.pt.x = m_Data.rt.left;
		m_Data.pt.y = m_Data.rt.top;
	}
}

void Missile::MoveMissile()
{
	RECT tmp;
	int tmp_x;
	int tmp_y;
	if (Stand)
	{
		if (MoveWay == LEFT)
		{
			tmp_x = m_Data.pt.x - MoveSpeed * FrameCounter;
			tmp_y = m_Data.pt.y;
			tmp = { tmp_x , tmp_y, tmp_x + MISSILE_WIDTH, tmp_y + MISSILE_HEIGHT };
			if (ReadMap->CheckNotImpulse(tmp, true))
			{
				if (tmp_x < 50)
					ReleaseStand();
				else
					SetMissileRect(tmp_x, tmp_y);
			}
			else
			{
				ReleaseStand();
				ReadMap->BorkenWall(tmp, LEFT);
			}
		}
		else if (MoveWay == RIGHT)
		{
			tmp_x = m_Data.pt.x + MoveSpeed * FrameCounter;
			tmp_y = m_Data.pt.y;
			tmp = { tmp_x , tmp_y, tmp_x + MISSILE_WIDTH, tmp_y + MISSILE_HEIGHT };
			if (ReadMap->CheckNotImpulse(tmp, true))
			{
				if (tmp_x + MISSILE_WIDTH > 50 + BLOCK_WIDTH * 13)
					ReleaseStand();
				else
					SetMissileRect(tmp_x, tmp_y);
			}
			else
			{
				ReleaseStand();
				ReadMap->BorkenWall(tmp, RIGHT);
			}
		}
		else if (MoveWay == UP)
		{
			tmp_x = m_Data.pt.x;
			tmp_y = m_Data.pt.y - MoveSpeed * FrameCounter;
			tmp = { tmp_x , tmp_y, tmp_x + MISSILE_WIDTH, tmp_y + MISSILE_HEIGHT };
			if (ReadMap->CheckNotImpulse(tmp, true))
			{
				if (tmp_y < 50)
					ReleaseStand();
				else
					SetMissileRect(tmp_x, tmp_y);
			}
			else
			{
				ReleaseStand();
				ReadMap->BorkenWall(tmp, UP);
			}
		}
		else if (MoveWay == DOWN)
		{
			tmp_x = m_Data.pt.x;
			tmp_y = m_Data.pt.y + MoveSpeed * FrameCounter;
			tmp = { tmp_x , tmp_y, tmp_x + MISSILE_WIDTH, tmp_y + MISSILE_HEIGHT };
			if (ReadMap->CheckNotImpulse(tmp, true))
			{
				if (tmp_y + MISSILE_WIDTH > 50 + BLOCK_HEIGHT * 13)
					ReleaseStand();
				else
					SetMissileRect(tmp_x, tmp_y);
			}
			else
			{
				ReleaseStand();
				ReadMap->BorkenWall(tmp, DOWN);
			}
		}
	}
}

void Missile::ReleaseStand()
{
	Stand = false;
}

void Missile::DrawMissile()
{
	if(MoveWay == LEFT || MoveWay == RIGHT)
		GameImage::GetImageMaker()->DrawMissle(SetMissileImage(), m_Data.rt.left, m_Data.rt.top, MISSILE_WIDTH, MISSILE_HEIGHT);
	else 
		GameImage::GetImageMaker()->DrawMissle(SetMissileImage(), m_Data.rt.left, m_Data.rt.top, MISSILE_HEIGHT, MISSILE_WIDTH);
}

LPCTSTR Missile::SetMissileImage()
{
	if (MoveWay == LEFT)
		return TEXT("BattleCity\\missile_00.bmp");
	else if (MoveWay == RIGHT)
		return TEXT("BattleCity\\missile_01.bmp");
	else if (MoveWay == UP)
		return TEXT("BattleCity\\missile_02.bmp");
	else if (MoveWay == DOWN)
		return TEXT("BattleCity\\missile_03.bmp");
}

Missile::~Missile()
{
}