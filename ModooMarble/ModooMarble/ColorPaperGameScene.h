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
	list<GameObject*> m_Paperlist;//list�� ����ϴ� ������ ����Ʈ�� push_front�� �����ϱ� ����(������ ���̰� ���� ���� ����)
	list<GameObject*> m_MovePaper;//list�� �ΰ� �̿��ؼ� �����̴� ���̴� ���ʿ��� �ͼ� ��������.
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

