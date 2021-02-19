#pragma once
#include "JEngine.h"
#include "GlobalDefine.h"
#include "UIManager.h"
#include "defines.h"
#include "GameObject.h"
#include <list>

class FlightGameScene : public JEngine::Scene
{
private:
	JEngine::BitMap* m_pBack;
	JEngine::BitMap* Overview;
	JEngine::BitMap* FeverEffect;
	JEngine::BitMap* RankBack;
	vector<JEngine::BitMap*> m_pChara;
	vector<JEngine::BitMap*> m_pFeverBar;
	JEngine::BitMap* TimerBar;
	bool m_GameOver;
	bool m_Rank;
	bool m_bInvincibility;

	int m_iCombo;
	int m_iFever;
	int m_iTotalScore;
	int m_iState;


	float m_fTimerGague;
	float Flight_X;
	float Flight_Y;
	float count;
	float m_fTanCount;
	float m_Fexplosion;
	float FeverCount;
	GameObject* test;
	list <GameObject*> Objectlist;
public:
	FlightGameScene();
	~FlightGameScene();
	virtual void Init(HWND hWnd);
	void Initvector(string str, bool Character);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	string callbackScore();
	virtual void Release();
	void SetCombo();
};

