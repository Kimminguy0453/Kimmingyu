#pragma once
#include "GlobalDefine.h"

namespace JEngine
{
	class Scene
	{
	public:
		virtual void Init(HWND hWnd) = 0;
		virtual bool Input(float fETime) = 0;
		virtual void Update(float fETime) = 0;
		virtual void Draw(HDC hdc) = 0;
		virtual void Release() = 0;

		Scene();
		virtual ~Scene();
	};
}

