#pragma once
#include "JEngine.h"
#include "GlobalDefine.h"
#include "defines.h"
#include "GameObject.h"
#include <list>
#include "UIManager.h"
class ColorPaperGameScene : public JEngine::Scene
{
private:
	JEngine::BitMap* m_pBack;
	JEngine::BitMap* TimerBar;
	JEngine::BitMap* Overview;
	JEngine::UIObject* ScoreLabel;
	list<GameObject*> m_Paperlist;//list를 사용하는 이유는 리스트는 push_front가 가능하기 때문(마지막 종이가 제일 앞의 종이)
	list<GameObject*> m_MovePaper;//list를 두개 이용해서 움직이는 종이는 이쪽에서 와서 관리해줌.
	vector<JEngine::BitMap*> m_pFeverBar;
	JEngine::UIObject* m_pScore;
	float m_fTimerGague;

	int m_icurCombo;
	int m_iFeverCombo;
	int m_iFeverLevel;
	int m_iTotalScore;
	bool GameOver;
public:
	ColorPaperGameScene();
	~ColorPaperGameScene();
	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();
	string callbackScore();
	void SetCombo(bool success);
};

