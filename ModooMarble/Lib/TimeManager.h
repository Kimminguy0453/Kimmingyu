#pragma once
#include "SingleTon.h"
#include <Windows.h>

namespace JEngine
{
	/**
	* @brief ���ӿ� ���Ǵ� �ð��� FPS�� ����ϴ� Ŭ����
	* @details scene�� Input Update ������ ���ڷ� �Ѿ�� �귯���ð��� �����ϴ� Ŭ���� FPS���� ��ɵ� ������ �ֽ��ϴ�.
	* @author JBC classicaa@naver.com
	* @date 2016-10-14
	* @version 0.0.1
	*/

	class TimeManager : public SingleTon<TimeManager>
	{
	private:
		bool				m_bUseFPS;
		int					m_nFPS;
		DWORD				m_dwLastTime;
		DWORD				m_dwCurTime;
		float				m_fElapseTime;
	public:
		void				init(bool useFPS, int FPS);
		bool				Update();
		inline float		GetElipseTime()
		{
			return m_fElapseTime;
		}
		TimeManager();
		~TimeManager();
	};
}

