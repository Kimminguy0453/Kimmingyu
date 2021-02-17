#include <Windows.h>
#include "MainEngine.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "GameSelectScene.h"
#include "ColorPaperGameScene.h"
#include "FlightGameScene.h"


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	//���� ��ü�� �����ϰ� Ÿ��Ʋ�� ������ ����� �־��ش�.
	JEngine::MainEngine engine("EngineTest", 414, 649);
	JEngine::SceneManager::GetInstance()->RegistScene(new TitleScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new GameSelectScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new ColorPaperGameScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new FlightGameScene);

	//���� ����
	return engine.StartEngine(hInstance);
}