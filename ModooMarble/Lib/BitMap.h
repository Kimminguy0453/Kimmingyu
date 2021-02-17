#pragma once
#include <Windows.h>
#include <string>
#include "POINT.h"
using namespace std;

enum ANCHOR
{
	ANCHOR_LT,
	ANCHOR_TOP,
	ANCHOR_RT,
	ANCHOR_LEFT,
	ANCHOR_CENTER,
	ANCHOR_RIGHT,
	ANCHOR_LB,
	ANCHOR_BOTTOM,
	ANCHOR_RB,
	ANCHOR_CUSTOM
};

namespace JEngine
{
	class BitMap
	{
	private:
		HDC				m_hMemDC;
		HBITMAP			m_hBitMap;
		HBITMAP			m_hOldBitmap;
		SIZE			m_size;
		ANCHOR			m_eAnchorType;
		JEngine::POINTF	m_ptAnchor;
	public:
		void			initBack(HDC hdc, int x, int y);
		void			init(HDC hdc, string file_name);
		void			AdjustAnchorPoint(int& x, int& y);
		void			DrawBitblt(int x, int y);
		void			Draw(int x, int y);
		void			TransDraw(int x, int y, int size_x, int size_y, int Gauge = 0, int GaugeCut = 0);
		void			Draw(JEngine::POINT pt);
		void			DrawBack(HDC hdc);		
		void			SetAnchor(ANCHOR type);
		void			SetAnchorPoint(JEngine::POINTF pt);
		HDC				GetDC();

		inline int		GetWidth()
		{
			return m_size.cx;
		}

		inline int		GetHeight()
		{
			return m_size.cy;
		}

		inline SIZE GetBitSize()
		{
			return m_size;
		}

		BitMap();
		~BitMap();
	};

}
