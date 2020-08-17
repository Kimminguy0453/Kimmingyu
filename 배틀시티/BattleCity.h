#pragma once
#include "Character.h"
#include <list>
#define SAVE 100
#define LOAD 101

struct GameProcessFlag
{
	bool CustomFlag;
	bool PlayFlag;
	bool UseFrameCount;
	bool PlayCustom;
};

class BattleCity
{
private:
	//프레임카운터
	LARGE_INTEGER Start, End, Frequency;
	double Delta;
	double MakeEnemyCounter;
	//=======================
	//캐릭터
	Character* m_Player;
	list<Character*> m_EnemyList;
	map<int, POINT> respawn;
	//미사일
	list<Missile*> m_MissileList;
	//=======================
	//맵
	GameMap* m_Map;
	//=======================
	//게임플래그
	GameProcessFlag m_Flag;
	//=======================
	//버튼
	HWND CustomButtom[19];
	HWND TitleButtom[4];
	//=======================
	//기타정보
	int m_iStage; 
	int CurType;
	int g_map[13][13];
	int m_Move;
	int Total_Enemy;
	int Field_Enemy;
	char curFile[MAX_PATH] = "";
	//=======================
	//파일경로
	char ProjectPath[MAX_PATH] = "";
	//=======================
	static BattleCity* m_hThis;	
public:
	static BattleCity* GetGame()
	{
		if (m_hThis == NULL)
			m_hThis = new BattleCity;
		return m_hThis;
	}
	void Default(HWND hWnd);
	void SetProjectPath();
	void DefaultFlag();
	void SelectStage(bool CustomStart = false);
	void SaveMap(OPENFILENAME &OFN);
	void LoadMap(LPSTR hFile);

	//=============================================================
	//타이틀
	void SetTitleButton(HWND hWnd, HINSTANCE g_hInst);
	void EndTitle();
	//=============================================================

	//=============================================================
	//게임동작
	void Game_UpDate(HWND hWnd);
	void DrawGame(HWND hWnd);
	void SetOpenFile(HWND hWnd, int Type);
	void PlayerMove();
	void EnemyMove();
	void MissileMove();
	void ReleaseEnemy();//적 유닛 개별 삭제.
	void ReleaseMissile();//미사일 개별 삭제.
	void DamageCheck();//유닛이 데미지 입었는지 확인
	void QuestionNextStage(HWND hWnd);
	void MakeEnemy();
	void GameEnd(HWND hWnd, bool Over);
	//=============================================================

	//=============================================================
	//삭제 관련
	void ReleaseMap();
	void AllClearMissile();
	void AllClearEnemy();
	void ExitGame();
	//=============================================================

	//=============================================================
	//커스텀모드
	void InitCursor(int Type);
	void CustomStart(HWND hWnd, HINSTANCE g_hInst);
	void CheckRepetition(int x, int y);
	void CustomEnd();
	void ChangeBlock(POINT pt);
	void DeleteEnemy(int x, int y);
	//=============================================================

	//플래그 전달
	inline bool GetCustom()
	{
		return m_Flag.CustomFlag;
	}
	inline bool GetGameFlag()
	{
		return m_Flag.PlayFlag;
	}
};