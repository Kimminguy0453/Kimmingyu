#include "TitleScene.h"
#include "SceneManager.h"
#include "ResoucesManager.h"
#include "InputManager.h"
#include "defines.h"
#include "UIManager.h"


TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init(HWND hWnd)
{

	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_SPACE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);
	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("Title.bmp");
	JEngine::UIManager::GetInstance()->AddButton(180, 520, "OnSelect.bmp", std::bind(&TitleScene::OnClick, this));
}

bool TitleScene::Input(float fETime)
{
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
		return true;

	return false;
}

void TitleScene::Update(float fETime)
{

}

void TitleScene::Draw(HDC hdc)
{
	m_pBack->DrawBitblt(0, 0);
}

void TitleScene::Release()
{

}

bool TitleScene::OnClick()
{
	JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_SELECT);
	return true;
}