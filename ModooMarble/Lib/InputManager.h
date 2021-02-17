#pragma once
#include "GlobalDefine.h"
#include "POINT.h"
#include "SingleTon.h"

namespace JEngine
{
	class InputManager : public SingleTon<InputManager>
	{
		struct KEY_INFO
		{
		public:
			int				keyCode;
			bool			KeyPrecce;
			bool			keyUp;
			bool			KeyDown;
		};

	private:
		HWND							m_hWnd;
		JEngine::POINT					m_ptMouse;
		std::vector<InputManager::KEY_INFO>	m_vecKeyCode;

	public:
		bool isExistKey(int key);//키가 등록되어있는지 확인
		void RegistKeyCode(int key);//키 등록

		void Init(HWND hWnd);//윈도우 핸들값을 받아옴.
		void Update();//키 상태 업데이트
		void Clear();//키 등록정보 초기화

		JEngine::POINT GetMousePoint();//입력관리자에 있는 마우스 포인터 객체를 리턴해줌.

		//키상태 확인 함수들
		bool isKeyPress(int keyCode);
		bool isKeyUp(int keyCode);
		bool isKeyDown(int keyCode);
		//

		InputManager();
		~InputManager();
	};
};

