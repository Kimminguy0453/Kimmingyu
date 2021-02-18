#include "GameObject.h"
#include "ResoucesManager.h"


GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

PaperObject::PaperObject(int Fever)
{
	m_fGameOB_X = 155.0f;
	m_fGameOB_Y = 298.0f;
	m_iColor = rand() % 4;
	if(m_iColor == BLUE)
		m_pGameOB = JEngine::ResoucesManager::GetInstance()->GetBitmap("ColoredPaperBlue.bmp");
	else if (m_iColor == YELLOW)
		m_pGameOB = JEngine::ResoucesManager::GetInstance()->GetBitmap("ColoredPaperYellow.bmp");
	else if (m_iColor == RED)
		m_pGameOB = JEngine::ResoucesManager::GetInstance()->GetBitmap("ColoredPaperRed.bmp");
	else if (m_iColor == GREEN)
		m_pGameOB = JEngine::ResoucesManager::GetInstance()->GetBitmap("ColoredPaperGreen.bmp");
	m_bMove = false;
	m_bUse = true;
	if (Fever == FEVER1)
		m_iScore = 100;
	else if (Fever == FEVER1)
		m_iScore = 1400;
	else if (Fever == FEVER2)
		m_iScore = 3000;
}

void PaperObject::Input(int key)
{
	if (!m_bMove)
	{
		m_iMoveWay = key;
		m_bMove = true;
	}
}

void PaperObject::Update(float fETime)
{
	if (m_bMove == true)
	{
		if (m_iMoveWay == VK_LEFT)
		{
			if(m_fGameOB_X - 300 * fETime >= 15)
				m_fGameOB_X -= 300 * fETime;
			else
			{
				m_bMove = false;
				m_bUse = false;
				if (m_iColor == BLUE)
					m_bSuccess = true;
				else
					m_bSuccess = false;
			}
		}
		else if(m_iMoveWay == VK_RIGHT)
		{
			if(m_fGameOB_X + 300 * fETime <= 290)
				m_fGameOB_X += 300 * fETime;
			else
			{
				m_bMove = false;
				m_bUse = false;
				if (m_iColor == RED)
					m_bSuccess = true;
				else
					m_bSuccess = false;
			}
		}
		else if (m_iMoveWay == VK_DOWN)
		{
			if (m_fGameOB_Y + 300 * fETime <= 442)
				m_fGameOB_Y += 300 * fETime;
			else
			{
				m_bMove = false;
				m_bUse = false;
				if (m_iColor == YELLOW)
					m_bSuccess = true;
				else
					m_bSuccess = false;
			}
		}
		else if (m_iMoveWay == VK_UP)
		{
			if (m_fGameOB_Y - 300 * fETime >= 148)
				m_fGameOB_Y -= 300 * fETime;
			else
			{
				m_bMove = false;
				m_bUse = false;
				if (m_iColor == GREEN)
					m_bSuccess = true;
				else
					m_bSuccess = false;
			}
		}
	}
}

void PaperObject::Draw()
{
	m_pGameOB->Draw((int)m_fGameOB_X, (int)m_fGameOB_Y);
}


int PaperObject::GetScore()
{
	if (m_bSuccess)
		return m_iScore;
	else
		return 0;
}

PaperObject::~PaperObject()
{

}

FlightObject::FlightObject(int Fever, int x, int y)
{
	int Start = rand() %  4;
	m_bUse = true;
	m_iType = rand() % 2;
	if (m_iType == ENEMY)
	{
		m_iScore = 0;
		m_pGameOB = JEngine::ResoucesManager::GetInstance()->GetBitmap("FlightGameBullet.bmp");
	}
	else if (m_iType == STAR)
	{
		if (Fever == FEVER1)
		{
			m_iScore = 100;
			m_pGameOB = JEngine::ResoucesManager::GetInstance()->GetBitmap("FlightGameStar1.bmp");
		}
		else if (Fever == FEVER2)
		{
			m_iScore = 1400;
			m_pGameOB = JEngine::ResoucesManager::GetInstance()->GetBitmap("FlightGameStar2.bmp");
		}
		else if (Fever == FEVER3)
		{
			m_iScore = 3000;
			m_pGameOB = JEngine::ResoucesManager::GetInstance()->GetBitmap("FlightGameStar3.bmp");
		}
	}
	if (Start == 1)
	{
		m_fGameOB_X = 0;
		m_fGameOB_Y = rand() % (609 - m_pGameOB->GetBitSize().cy + 1);
	}
	else if (Start == 2)
	{
		m_fGameOB_X = 448 - m_pGameOB->GetBitSize().cx;
		m_fGameOB_Y = rand() % (609 - m_pGameOB->GetBitSize().cy + 1);
	}
	else if (Start == 3)
	{
		m_fGameOB_Y = 91;
		m_fGameOB_X = rand() % (448 - m_pGameOB->GetBitSize().cx + 1);
	}
	else if (Start == 4)
	{
		m_fGameOB_Y = 609;
		m_fGameOB_X = rand() % (448 - m_pGameOB->GetBitSize().cx + 1);
	}
	Angel = atan2f((m_fGameOB_Y + m_pGameOB->GetBitSize().cy * 0.5) - y, (m_fGameOB_X + m_pGameOB->GetBitSize().cx * 0.5) - x);//두점사이의 각도를 구하기 위해 사용. 각도 = tan-(높이 / 밑변)
	SetRect();
}

void FlightObject::Input(int key)
{
}

void FlightObject::Update(float fETime)
{
	if ((m_fGameOB_X >= 0 && m_fGameOB_X + m_pGameOB->GetBitSize().cx <= 448) && (m_fGameOB_Y >= 91 && m_fGameOB_Y + m_pGameOB->GetBitSize().cy <= 609))
	{
		m_fGameOB_X -= cos(Angel) * (200 * fETime);
		m_fGameOB_Y -= sin(Angel) * (200 * fETime);
	}
	else
		m_bUse = false;
	SetRect();
}

int FlightObject::GetScore()
{
	return m_iScore;
}

void FlightObject::Draw()
{
	m_pGameOB->Draw(m_fGameOB_X, m_fGameOB_Y);
}

void FlightObject::SetRect()
{
	rt.Set(m_fGameOB_X - m_pGameOB->GetBitSize().cx / 2, m_fGameOB_Y - m_pGameOB->GetBitSize().cy / 2, m_fGameOB_X + m_pGameOB->GetBitSize().cx / 2, m_fGameOB_Y + m_pGameOB->GetBitSize().cy / 2);
}

FlightObject::~FlightObject()
{
}