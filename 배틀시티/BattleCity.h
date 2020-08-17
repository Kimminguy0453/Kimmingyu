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
	//������ī����
	LARGE_INTEGER Start, End, Frequency;
	double Delta;
	double MakeEnemyCounter;
	//=======================
	//ĳ����
	Character* m_Player;
	list<Character*> m_EnemyList;
	map<int, POINT> respawn;
	//�̻���
	list<Missile*> m_MissileList;
	//=======================
	//��
	GameMap* m_Map;
	//=======================
	//�����÷���
	GameProcessFlag m_Flag;
	//=======================
	//��ư
	HWND CustomButtom[19];
	HWND TitleButtom[4];
	//=======================
	//��Ÿ����
	int m_iStage; 
	int CurType;
	int g_map[13][13];
	int m_Move;
	int Total_Enemy;
	int Field_Enemy;
	char curFile[MAX_PATH] = "";
	//=======================
	//���ϰ��
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
	//Ÿ��Ʋ
	void SetTitleButton(HWND hWnd, HINSTANCE g_hInst);
	void EndTitle();
	//=============================================================

	//=============================================================
	//���ӵ���
	void Game_UpDate(HWND hWnd);
	void DrawGame(HWND hWnd);
	void SetOpenFile(HWND hWnd, int Type);
	void PlayerMove();
	void EnemyMove();
	void MissileMove();
	void ReleaseEnemy();//�� ���� ���� ����.
	void ReleaseMissile();//�̻��� ���� ����.
	void DamageCheck();//������ ������ �Ծ����� Ȯ��
	void QuestionNextStage(HWND hWnd);
	void MakeEnemy();
	void GameEnd(HWND hWnd, bool Over);
	//=============================================================

	//=============================================================
	//���� ����
	void ReleaseMap();
	void AllClearMissile();
	void AllClearEnemy();
	void ExitGame();
	//=============================================================

	//=============================================================
	//Ŀ���Ҹ��
	void InitCursor(int Type);
	void CustomStart(HWND hWnd, HINSTANCE g_hInst);
	void CheckRepetition(int x, int y);
	void CustomEnd();
	void ChangeBlock(POINT pt);
	void DeleteEnemy(int x, int y);
	//=============================================================

	//�÷��� ����
	inline bool GetCustom()
	{
		return m_Flag.CustomFlag;
	}
	inline bool GetGameFlag()
	{
		return m_Flag.PlayFlag;
	}
};