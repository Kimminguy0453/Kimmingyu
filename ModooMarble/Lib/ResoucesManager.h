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
		JEngine::BitMap*				m_pBack;//��ȭ��(���� ���۸��� ���� ȭ���� �̸��׸� ����.
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

