#pragma once
#include "Missile.h"
#include <time.h>


class Character
{
protected:
	BlockData m_Data;//ĳ���� ��ġ������ ���Ǵ� ����.
	GameMap* ReadMap;
	LPCTSTR m_Image;
	double MissileCount;
	double FrameCounter;
	bool UseUnit;
	int MoveSpeed;
	int WayImage;
	int MoveWay;
	bool Shoot;
	int m_Life;
	bool DeathFlag;
public:
	//�ڽ�Ŭ�������� �ٽ� ����
	virtual void InitData(int x, int y, int Type) = 0;
	virtual bool MoveCharacter() = 0;
	virtual void ImageID() = 0;
	virtual bool DamageCheck(Missile* CheckMissile) = 0;
	virtual void SetFrame(double Delta) = 0;
	virtual void DeathProcess() = 0;
	virtual void MoveChange(bool Change) = 0;

	//�ڽ�Ŭ���� ����
	void ReleaseFrame();
	void DeathImage(int Number);
	void InitMap(GameMap* ReadMap);
	void DrawCharacter();
	void SetDataPoint();
	void SetWayImage(int Way);
	void SetRect(int x, int y);
	Missile* MakeMissile();//ĳ���Ϳ��� �̻����� ����� ������ ĳ���� Ŭ�������� ���(�̻����� ����� ���ſ� ���ؼ��� BattlecityŬ�������� ����.
	
	inline int GetLife()
	{
		return m_Life;
	}
	inline bool GetDeath()
	{
		return DeathFlag;
	}
	inline POINT GetPoint()
	{
		return m_Data.pt;
	}
	inline bool GetUseUnit()
	{
		return UseUnit;
	}
	inline bool UseShoot()
	{
		return Shoot;
	}
	inline int GetMoveWay()
	{
		return MoveWay;
	}
	inline int GetMoveSpeed()
	{
		return MoveSpeed;
	}
};

class Player : public Character
{
private:
	POINT BackPoint;
	int Back_Up_MoveWay;
private:
	void SetFrame(double Delta);
	bool MoveCharacter();
	void InitData(int x, int y, int Type);
	void ImageID();
	bool DamageCheck(Missile* CheckMissile);
	void DeathProcess();
	void MoveChange(bool Change);
};

class Enemy : public Character
{
private:
	int ShootCounter;
	int Cur_Distractor;
	int Pre_Distractor;
	int Hit_Direction;
	bool NotImpulseFlag;
	bool MoveFlag;
	bool DamageFlag;
	bool Counterattack;
	double MoveChangeCounter;
	double DamageCounter;
private:
	void SetFrame(double Delta);
	bool MoveCharacter();
	void InitData(int x, int y, int Type);
	void ImageID();
	bool DamageCheck(Missile* CheckMissile);
	void DeathProcess();
	void MoveChange(bool Change);
	int Movepossible(bool NotImpulse);
	RECT MakeRect(int x, int y);
	bool CheckImpluseCommand(POINT pt, int Move);
};
