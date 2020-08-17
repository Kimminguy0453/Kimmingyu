#pragma once
#include "GameMap.h"

class Missile
{
private:
	int MoveWay;// �����̴� ����
	int MoveSpeed;//�����̴� ���ǵ�
	double FrameCounter;// �����ϋ� ������ ���� ����� ���� ī����
	bool Stand;
	LPCTSTR ImageID;
	BlockData m_Data;//�׷��� ������ǥ, źȯ�� ����, �߻��� ����Ÿ��
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

