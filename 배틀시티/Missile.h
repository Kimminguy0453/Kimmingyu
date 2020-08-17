#pragma once
#include "GameMap.h"

class Missile
{
private:
	int MoveWay;// 움직이는 방향
	int MoveSpeed;//움직이는 스피드
	double FrameCounter;// 움직일떄 프레임 단위 계산을 위한 카운터
	bool Stand;
	LPCTSTR ImageID;
	BlockData m_Data;//그려질 시작좌표, 탄환의 영역, 발사한 유닛타입
	GameMap* ReadMap;
public:
	Missile(GameMap* Observer, int Unit, int Way, int x, int y);
	inline RECT GetMissileRect()
	{
		return  m_Data.rt;
	}
	inline int GetStartUnit()
	{
		return  m_Data.Type;
	}
	inline bool GetStand()
	{
		return Stand;
	}
	inline int GetMoveWay()
	{
		return MoveWay;
	}
	void ReleaseStand();
	void SetFrameCounter(double Delta);
	void MoveMissile();
	void DrawMissile();
	void SetMissileRect(int x, int y);
	LPCTSTR SetMissileImage();
	
	~Missile();
};

