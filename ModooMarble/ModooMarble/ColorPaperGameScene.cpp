#include "ColorPaperGameScene.h"
#include "SceneManager.h"
#include "ResoucesManager.h"
#include "InputManager.h"
#include "Rank.h"

ColorPaperGameScene::ColorPaperGameScene()
{
}

ColorPaperGameScene::~ColorPaperGameScene()
{
}

void ColorPaperGameScene::Init(HWND hWnd)
{
	m_iTotalScore = 0;
	m_fTimerGague = 370.f;
	GameOver = false;
	SetCombo(false);//fever 게이지와 콤보수를 초기화.
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LEFT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_RIGHT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_UP);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_DOWN);
	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("ColoredPaperBack.bmp");
	m_pFeverBar.push_back(JEngine::ResoucesManager::GetInstance()->GetBitmap("Fever1.bmp"));
	m_pFeverBar.push_back(JEngine::ResoucesManager::GetInstance()->GetBitmap("Fever2.bmp"));
	m_pFeverBar.push_back(JEngine::ResoucesManager::GetInstance()->GetBitmap("Fever3.bmp"));
	TimerBar = JEngine::ResoucesManager::GetInstance()->GetBitmap("ColoredPaperTimeBar.bmp");
	Overview = JEngine::ResoucesManager::GetInstance()->GetBitmap("TimeOver.bmp"); 
	JEngine::UIManager::GetInstance()->AddLabel(to_string(m_iTotalScore), 200, 20, DT_CENTER, std::bind(&ColorPaperGameScene::callbackScore, this));
	JEngine::UIManager::GetInstance()->AddLabel("게임종료 : ESC", 160, 588, DT_CENTER, NULL);
}

bool ColorPaperGameScene::Input(float fETime)
{
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
		JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_SELECT);
	else if (JEngine::InputManager::GetInstance()->isKeyUp(VK_LEFT) && !GameOver)
	{
		m_Paperlist.back()->Input(VK_LEFT);
		m_MovePaper.push_back(m_Paperlist.back());
		m_Paperlist.pop_back();
	}
	else if (JEngine::InputManager::GetInstance()->isKeyUp(VK_RIGHT) && !GameOver)
	{
		m_Paperlist.back()->Input(VK_RIGHT);
		m_MovePaper.push_back(m_Paperlist.back());
		m_Paperlist.pop_back();
	}
	else if (JEngine::InputManager::GetInstance()->isKeyUp(VK_UP) && !GameOver)
	{
			m_Paperlist.back()->Input(VK_UP);
			m_MovePaper.push_back(m_Paperlist.back());
			m_Paperlist.pop_back();
	}
	else if (JEngine::InputManager::GetInstance()->isKeyUp(VK_DOWN) && !GameOver)
	{
		m_Paperlist.back()->Input(VK_DOWN);
		m_MovePaper.push_back(m_Paperlist.back());
		m_Paperlist.pop_back();
	}
	return false;
}

void ColorPaperGameScene::Update(float fETime)
{
	if (!GameOver)
	{
		if (m_Paperlist.size() < 5)
			m_Paperlist.push_front(new PaperObject(m_iFeverLevel));
		if (m_MovePaper.size() != 0)
		{
			for (auto iter = m_MovePaper.begin(); iter != m_MovePaper.end(); iter++)
			{
				if ((*iter)->GetMove())
					(*iter)->Update(fETime);
			}
			if (!m_MovePaper.front()->GetUse())
			{
				if (m_MovePaper.front()->GetSuccess())
				{
					m_iTotalScore += m_MovePaper.front()->GetScore();
					SetCombo(true);
				}
				else
					SetCombo(false);
				delete m_MovePaper.front();
				m_MovePaper.pop_front();
			}
		}

		if (m_fTimerGague > 0)
		{
			m_fTimerGague -= 10 * fETime;
			if (m_fTimerGague <= 0)
			{
				m_fTimerGague = 0;
				GameOver = true;
				Rank::GetInstance()->RenewalRank(m_iTotalScore, SCENE_INDEX_PAPER);
				Rank::GetInstance()->SaveRank(SCENE_INDEX_PAPER);
			}
		}
	}
}

void ColorPaperGameScene::SetCombo(bool success)
{
	if (success)
	{
		m_icurCombo++;
		if (m_iFeverLevel != 2)
		{
			if (m_iFeverCombo == 20)
			{
				m_iFeverCombo = 0;
				m_iFeverLevel++;
			}
			m_iFeverCombo++;
		}
		else if(m_iFeverCombo <= 20)	
			m_iFeverCombo++;
	}
	else
	{
		m_iFeverCombo = 0;
		m_iFeverLevel = 0;
		m_icurCombo = 0;
	}
}

void ColorPaperGameScene::Draw(HDC hdc)
{
	HFONT hFont, OldFont;

	m_pBack->DrawBitblt(0, 0);
	m_Paperlist.back()->Draw();
	if (m_MovePaper.size() != 0)
	{
		for (auto iter = m_MovePaper.begin(); iter != m_MovePaper.end(); iter++)
			(*iter)->Draw();
	}
	if(m_iFeverCombo != 0)
		m_pFeverBar[m_iFeverLevel]->TransDraw(18, 52, 372, 30, m_iFeverCombo, 20);

	TimerBar->TransDraw(20, 618, m_fTimerGague, 30);

	if (GameOver)
	{
		Overview->Draw(100, 300);
	}
}

void ColorPaperGameScene::Release()
{
	for (auto iter = m_Paperlist.begin(); iter != m_Paperlist.end(); iter++)
		delete (*iter);
	for (auto iter = m_MovePaper.begin(); iter != m_MovePaper.end(); iter++)
		delete (*iter);;
	m_Paperlist.clear();
	m_MovePaper.clear();
	m_pFeverBar.clear();
}

string ColorPaperGameScene::callbackScore()
{
	return to_string(m_iTotalScore);
}
