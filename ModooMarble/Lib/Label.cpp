#include "Label.h"
#include "ResoucesManager.h"

namespace JEngine
{
	Label::Label()
	{
	}


	Label::~Label()
	{
	}

	void Label::Init(string str, int x, int y, DWORD drawOption, pStringFunc callback)
	{
		m_ix = x;
		m_iy = y;
		GetTextExtentPoint32(ResoucesManager::GetInstance()->GetBackDC(), str.c_str(), str.length(), &size);
		SetPos(m_ix, m_iy, m_ix + size.cx, m_iy  + size.cy);
		m_pCallBack = callback;
		m_strPrint = str;
		m_dwDrawOption = drawOption;
	}

	void Label::Draw()
	{
		if (m_pCallBack != NULL)
		{
			m_strPrint = m_pCallBack();
			GetTextExtentPoint32(ResoucesManager::GetInstance()->GetBackDC(), m_strPrint.c_str(), m_strPrint.length(), &size);
			SetPos(m_ix, m_iy, m_ix + size.cx, m_iy + size.cy);
		}
		DrawText(ResoucesManager::GetInstance()->GetBackDC(), m_strPrint.c_str(), m_strPrint.length(),&m_rcPos.ToWinRECT(), m_dwDrawOption);
	}
}