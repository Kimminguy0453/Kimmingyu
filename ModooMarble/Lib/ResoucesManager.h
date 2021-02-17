#pragma once
#include <Windows.h>
#include <vector>
#include <map>
#include "SingleTon.h"
#include "BitMap.h"
using namespace std;

namespace JEngine
{
	class ResoucesManager : public SingleTon<ResoucesManager>
	{
	private:
		JEngine::BitMap*				m_pBack;//도화지(더블 버퍼링을 위해 화면을 미리그릴 공간.
		map<string, JEngine::BitMap*>	m_mapBitmap;
		JEngine::BitMap*				initBitmap(std::string strFileName);
	public:
		void							initBack(HDC hdc, int cx, int cy);
		HDC								GetBackDC();
		void							DrawBack(HDC hdc);
		JEngine::BitMap*				GetBitmap(std::string strFileName);

		ResoucesManager();
		~ResoucesManager();
	};
}

