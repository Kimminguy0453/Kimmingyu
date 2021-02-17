#pragma once
#include "JEngine.h"
#include "GlobalDefine.h"
#include "defines.h"

class GameObject
{
protected:
	JEngine::BitMap* m_pGameOB;
	float m_fGameOB_X;
	float m_fGameOB_Y;
	bool m_bMove;
	bool m_bUse;
	int m_iScore;
	bool m_bSuccess;
	JEngine::RECT rt;
public:
	GameObject();
	virtual void Input(int key) = 0;
	virtual void Update(float fETime) = 0;
	virtual void Draw() = 0;
	virtual int GetScore() = 0;
	JEngine::RECT GetRect()
	{
		return rt;
	}
	bool GetMove()
	{
		return m_bMove;
	}
	bool GetUse()
	{
		return m_bUse;
	}
	bool GetSuccess()
	{
		return  m_bSuccess;
	}
	~GameObject();
};

class PaperObject : public GameObject
{
private:
	int m_iMoveWay;
	int m_iColor;
public:
	PaperObject(int Fever);
	void Input(int key);
	void Update(float fETime);
	int GetScore();
	void Draw();
	~PaperObject();
};

class FlightObject : public GameObject
{
enum
{
	ENEMY,
	STAR,
};
private:
	float Angel;
	int m_iType;
public:
	FlightObject(int Fever,int x, int y);
	void Input(int key);
	void Update(float fETime);
	int GetScore();
	void Draw();
	void SetRect();
	~FlightObject();
};
