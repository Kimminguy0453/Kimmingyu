#pragma once
#include "JEngine.h"
#include "GlobalDefine.h"

class RankScene : public JEngine::Scene
{
private:
	JEngine::BitMap* m_pBack;
	int Type;
	std::function<bool()> clickEvent;
public:
	RankScene();
	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();
	bool OnClick();
	~RankScene();
};