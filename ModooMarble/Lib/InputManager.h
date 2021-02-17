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
		bool isExistKey(int key);//Ű�� ��ϵǾ��ִ��� Ȯ��
		void RegistKeyCode(int key);//Ű ���

		void Init(HWND hWnd);//������ �ڵ鰪�� �޾ƿ�.
		void Update();//Ű ���� ������Ʈ
		void Clear();//Ű ������� �ʱ�ȭ

		JEngine::POINT GetMousePoint();//�Է°����ڿ� �ִ� ���콺 ������ ��ü�� ��������.

		//Ű���� Ȯ�� �Լ���
		bool isKeyPress(int keyCode);
		bool isKeyUp(int keyCode);
		bool isKeyDown(int keyCode);
		//

		InputManager();
		~InputManager();
	};
};

