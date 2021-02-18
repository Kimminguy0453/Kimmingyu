#include <Windows.h>
#include "MainEngine.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "GameSelectScene.h"
#include "ColorPaperGameScene.h"
#include "FlightGameScene.h"
#include "Rank.h"
#include "RankScene.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	//엔진 객체를 생성하고 타이틀과 윈도우 사이즈를 넣어준다.
	Rank::GetInstance()->LoadRank();
	JEngine::MainEngine engine("EngineTest", 414, 649);
	JEngine::SceneManager::GetInstance()->RegistScene(new TitleScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new GameSelectScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new ColorPaperGameScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new FlightGameScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new RankScene);

	//엔진 시작
	return engine.StartEngine(hInstance);
}