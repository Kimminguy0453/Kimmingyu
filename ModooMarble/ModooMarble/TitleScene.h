#pragma once
#include "JEngine.h"
#include "GlobalDefine.h"

class TitleScene : public JEngine::Scene
{
private:
	JEngine::BitMap* m_pBack;
	std::function<bool()> clickEvent;

public:
	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();
	bool OnClick();

	TitleScene();
	~TitleScene();
};

