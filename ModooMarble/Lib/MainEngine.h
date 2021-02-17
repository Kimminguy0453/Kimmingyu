#pragma once
#include "GlobalDefine.h"

namespace JEngine
{
	class MainEngine
	{
	private:
		string		m_strTitle;
		int			m_winSizeX;
		int			m_winSizeY;
	public:
		int			StartEngine(HINSTANCE hInstance);
		MainEngine(string title, int cx, int cy);
		~MainEngine();
	};

}
