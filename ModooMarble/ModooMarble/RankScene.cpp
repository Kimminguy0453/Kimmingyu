#include "RankScene.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ResoucesManager.h"
#include "defines.h"
#include "UIManager.h"
#include "Rank.h"


RankScene::RankScene()
{
}

void RankScene::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);
	Type = Rank::GetInstance()->GetGameType();
	if (Type == SCENE_INDEX_PAPER)
	{
		m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("ColoredPaperBack.bmp");
		JEngine::UIManager::GetInstance()->AddLabel("1 등 : " + to_string(Rank::GetInstance()->GetScore(SCENE_INDEX_PAPER)), 180, 180, DT_CENTER, NULL);
		JEngine::UIManager::GetInstance()->AddLabel("2 등 : " + to_string(Rank::GetInstance()->GetScore(SCENE_INDEX_PAPER, 1)), 180, 220, DT_CENTER, NULL);
		JEngine::UIManager::GetInstance()->AddLabel("3 등 : " + to_string(Rank::GetInstance()->GetScore(SCENE_INDEX_PAPER, 2)), 180, 260, DT_CENTER, NULL);
		JEngine::UIManager::GetInstance()->AddLabel("4 등 : " + to_string(Rank::GetInstance()->GetScore(SCENE_INDEX_PAPER, 3)), 180, 300, DT_CENTER, NULL);
		JEngine::UIManager::GetInstance()->AddLabel("5 등 : " + to_string(Rank::GetInstance()->GetScore(SCENE_INDEX_PAPER, 4)), 180, 340, DT_CENTER, NULL);
	}
	else
	{
		m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("123.bmp");
		JEngine::UIManager::GetInstance()->AddLabel("1 등 : " + to_string(Rank::GetInstance()->GetScore(SCENE_INDEX_FLIGHT)), 180, 180, DT_CENTER, NULL);
		JEngine::UIManager::GetInstance()->AddLabel("2 등 : " + to_string(Rank::GetInstance()->GetScore(SCENE_INDEX_FLIGHT, 1)), 180, 220, DT_CENTER, NULL);
		JEngine::UIManager::GetInstance()->AddLabel("3 등 : " + to_string(Rank::GetInstance()->GetScore(SCENE_INDEX_FLIGHT, 2)), 180, 260, DT_CENTER, NULL);
		JEngine::UIManager::GetInstance()->AddLabel("4 등 : " + to_string(Rank::GetInstance()->GetScore(SCENE_INDEX_FLIGHT, 3)), 180, 300, DT_CENTER, NULL);
		JEngine::UIManager::GetInstance()->AddLabel("5 등 : " + to_string(Rank::GetInstance()->GetScore(SCENE_INDEX_FLIGHT, 4)), 180, 340, DT_CENTER, NULL);
	}

	JEngine::UIManager::GetInstance()->AddButton(180, 480, "OnSelect.bmp", std::bind(&RankScene::OnClick, this));
}

bool RankScene::Input(float fETime)
{
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
		JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_SELECT);

	return false;
}

void RankScene::Update(float fETime)
{

}

void RankScene::Draw(HDC hdc)
{
	m_pBack->DrawBitblt(0, 0);
	HBRUSH hWhite = (HBRUSH)GetStockObject(WHITE_BRUSH);
	HBRUSH hold = (HBRUSH)SelectObject(hdc, hWhite);


}

void RankScene::Release()
{

}

bool RankScene::OnClick()
{
	JEngine::SceneManager::GetInstance()->LoadScene(Type);
	return true;
}

RankScene::~RankScene()
{
}
