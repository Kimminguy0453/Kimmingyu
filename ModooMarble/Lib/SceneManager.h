#pragma once
#include "GlobalDefine.h"
#include "SingleTon.h"

namespace JEngine
{
	class Scene;
	class SceneManager : public SingleTon<SceneManager>
	{
	private:
		HWND					m_hWnd;
		vector<Scene*>			m_vecScene;
		Scene*					m_curScene;
		Scene*					m_lastScene;
		int						m_iWinCX;
		int						m_iWinCY;
	public:
		SceneManager();
		void					Init(HWND hWnd, int win_cx, int win_cy);
		void					RegistScene(Scene* Reg);
		bool					Update();
		void					Release();

		void					LoadScene(int SceneIndex);
		~SceneManager();
	};
}