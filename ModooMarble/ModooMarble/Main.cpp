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
	JEngine::MainEngine engine("EngineTest", 414, 649);
	Rank::GetInstance()->LoadRank(SCENE_INDEX_PAPER);
	Rank::GetInstance()->LoadRank(SCENE_INDEX_FLIGHT);
	JEngine::SceneManager::GetInstance()->RegistScene(new TitleScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new GameSelectScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new ColorPaperGameScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new FlightGameScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new RankScene);

	//엔진 시작
	return engine.StartEngine(hInstance);
}