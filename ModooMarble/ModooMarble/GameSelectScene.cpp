#include "GameSelectScene.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ResoucesManager.h"
#include "defines.h"
#include "UIManager.h"


GameSelectScene::GameSelectScene()
{
}


GameSelectScene::~GameSelectScene()
{
}


void GameSelectScene::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);
	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("GameSelect.bmp");
	JEngine::UIManager::GetInstance()->AddButton(320, 166, "OnSelect.bmp", std::bind(&GameSelectScene::PaperGameClick, this));
	JEngine::UIManager::GetInstance()->AddButton(320, 249, "OnSelect.bmp", std::bind(&GameSelectScene::FilghtGameClick, this));
}

bool GameSelectScene::Input(float fETime)
{
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
		JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_TITLE);

	return false;
}

void GameSelectScene::Update(float fETime)
{

}

void GameSelectScene::Draw(HDC hdc)
{
	m_pBack->DrawBitblt(0, 0);
}

void GameSelectScene::Release()
{

}

bool GameSelectScene::PaperGameClick()
{
	JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_PAPER);
	return true;
}
bool GameSelectScene::FilghtGameClick()
{
	JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_FLIGHT);
	return true;
}
