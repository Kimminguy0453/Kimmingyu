#include "FlightGameScene.h"
#include "SceneManager.h"
#include "ResoucesManager.h"
#include "InputManager.h"
#include "Rank.h"

FlightGameScene::FlightGameScene()
{
}


FlightGameScene::~FlightGameScene()
{
}

void FlightGameScene::Init(HWND hWnd)
{
	m_GameOver = false;
	m_Rank = false;

	m_iState = 0;
	m_iTotalScore = 0;
	m_iFever = 0;
	m_iCombo = 0;

	Flight_X = 224.0f;
	Flight_Y = 350.0f;
	m_fTanCount = 0.0f;
	m_Fexplosion = 0.0f;
	m_fTimerGague = 370;

	FeverCount = 0;
	count = 0;

	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_SPACE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LEFT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_RIGHT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_UP);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_DOWN);

	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("FlightGameBack.bmp"); 
	Overview = JEngine::ResoucesManager::GetInstance()->GetBitmap("TimeOver.bmp");
	TimerBar = JEngine::ResoucesManager::GetInstance()->GetBitmap("ColoredPaperTimeBar.bmp");
	FeverEffect = JEngine::ResoucesManager::GetInstance()->GetBitmap("FeverEffect3.bmp");

	Initvector("FlightGameFlight.bmp", true);
	Initvector("explosion3.bmp", true);
	Initvector("explosion2.bmp", true);
	Initvector("explosion1.bmp", true);

	Initvector("Fever1.bmp", false);
	Initvector("Fever2.bmp", false);
	Initvector("Fever3.bmp", false);

	JEngine::UIManager::GetInstance()->AddLabel(to_string(m_iTotalScore), 200, 20, DT_CENTER, std::bind(&FlightGameScene::callbackScore, this));
	JEngine::UIManager::GetInstance()->AddLabel("게임종료 : ESC", 160, 588, DT_CENTER, NULL);
}

void FlightGameScene::Initvector(string str, bool Character)
{
	if (Character)
	{
		m_pChara.push_back(JEngine::ResoucesManager::GetInstance()->GetBitmap(str));
		m_pChara.back()->SetAnchor(ANCHOR_CENTER);
	}
	else
		m_pFeverBar.push_back(JEngine::ResoucesManager::GetInstance()->GetBitmap(str));
}

bool FlightGameScene::Input(float fETime)
{
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
		JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_SELECT);
	else if (JEngine::InputManager::GetInstance()->isKeyUp(VK_SPACE) && m_GameOver)
		m_Rank = true;
	else if (JEngine::InputManager::GetInstance()->isKeyPress(VK_LEFT) && !m_GameOver && m_iState ==0)
	{
		if(Flight_X - 200 * fETime >= 35)
			Flight_X -= 200 * fETime;
	}
	else if (JEngine::InputManager::GetInstance()->isKeyPress(VK_RIGHT) && !m_GameOver && m_iState == 0)
	{
		if(Flight_X + 200 * fETime <= 413)
			Flight_X += 200 * fETime;
	}
	else if (JEngine::InputManager::GetInstance()->isKeyPress(VK_UP) && !m_GameOver && m_iState == 0)
	{
		if(Flight_Y - 200 * fETime >= 124)
			Flight_Y -= 200 * fETime;
	}
	else if (JEngine::InputManager::GetInstance()->isKeyPress(VK_DOWN) && !m_GameOver && m_iState == 0)
	{
		if (Flight_Y + 200 * fETime <= 576)
			Flight_Y += 200 * fETime;
	}
	return false;
}

void FlightGameScene::Update(float fETime)
{
	
	if (!m_GameOver)
	{
		JEngine::RECT rt;
		int score = 0;
		rt.Set(Flight_X - m_pChara[m_iState]->GetBitSize().cx / 4, Flight_Y - m_pChara[m_iState]->GetBitSize().cy/ 4, Flight_X + m_pChara[m_iState]->GetBitSize().cx / 4, Flight_Y + m_pChara[m_iState]->GetBitSize().cy / 4);
		m_fTanCount += fETime;
		if(m_iState != 0)
			m_Fexplosion += fETime;
		else
			m_Fexplosion = 0;

		if (m_fTanCount > 0.2)
		{
			Objectlist.push_back(new FlightObject(m_iFever, Flight_X, Flight_Y));
			m_fTanCount = 0;
		}
		if (m_Fexplosion > 0.5)
		{
			m_iState--;
			m_Fexplosion = 0;
		}
		if (m_iFever == 2)
		{
			FeverCount += fETime;
			if (FeverCount > 5)
			{
				m_iCombo = 0;
				m_iFever = 0;
				FeverCount = 0;
			}
		}

		for (auto iter = Objectlist.begin(); iter != Objectlist.end(); iter++)
		{
			(*iter)->Update(fETime);
			if ((*iter)->GetRect().isCollision(rt))
			{
				score = (*iter)->GetScore();
				if (m_iState == 0)
				{
					m_iTotalScore += score;
					if (score == 0)
					{
						m_iState = 3;
						m_iCombo = 0;
						m_iFever = 0;
					}
					else
						SetCombo();
				}
				

				if((*iter) != Objectlist.back())
					iter = Objectlist.erase(iter);
				else
				{
					Objectlist.pop_back();
					break;
				}
			}
			else if (!(*iter)->GetUse())
			{
				if ((*iter) == Objectlist.back())
				{
					Objectlist.pop_back();
					break;
				}
				else
					iter = Objectlist.erase(iter);
			}
		}
	}
	if (m_fTimerGague > 0)
	{
		m_fTimerGague -= 30 * fETime;
		if (m_fTimerGague <= 0)
		{
			m_fTimerGague = 0;
			m_GameOver = true;
			Rank::GetInstance()->RenewalRank(m_iTotalScore, SCENE_INDEX_FLIGHT);
			Rank::GetInstance()->SaveRank(SCENE_INDEX_FLIGHT);
		}
	}
}

void FlightGameScene::SetCombo()
{
	m_iCombo++;
	if (m_iFever != 2)
	{
		if (m_iCombo == 20)
		{
			m_iCombo = 0;
			m_iFever++;
		}
	}
}

void FlightGameScene::Draw(HDC hdc)
{
	m_pBack->DrawBitblt(0, 0);
	m_pChara[m_iState]->Draw(Flight_X, Flight_Y);
	for (auto iter = Objectlist.begin(); iter != Objectlist.end(); iter++)
	{
		if((*iter)->GetUse())
			(*iter)->Draw();
	}
	if (m_iCombo != 0)
		m_pFeverBar[m_iFever]->TransDraw(18, 52, 372, 30, m_iCombo, 20);
	TimerBar->TransDraw(20, 618, m_fTimerGague, 30);

	if (m_GameOver)
		Overview->Draw(100, 300);

	if(m_Rank)

	if (m_iFever == 2)
	{
		FeverEffect->Draw(0, 0);
	}
}

void FlightGameScene::Release()
{
	for (auto iter = Objectlist.begin(); iter != Objectlist.end(); iter++)
		delete (*iter);
	m_pChara.clear();
	Objectlist.clear(); 
	m_pFeverBar.clear();
}

string FlightGameScene::callbackScore()
{
	return to_string(m_iTotalScore);
}
