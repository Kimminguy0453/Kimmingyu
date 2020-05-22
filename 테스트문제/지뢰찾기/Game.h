#pragma once
#include "Block.h"
#include<vector>


enum MINE_COUNT
{
	EASY = 15,
	NOMAL = 20,
	HARD = 25
};

struct Player
{
	string Block = "¢Ã";
	int x;
	int y;
};

class Game
{
private:
	int MineCount;
	Player m_Player;
	MapDraw m_Draw;
	vector<Block*> vec_BoardList;
	vector<Block*> vec_MineList;
public:
	Game();
	void GameLevel();
	void Black_ReDraw(int x, int y);
	void DrawPlayer();
	void GameStart();
	void SetBoard();
	void SetMine();
	void DrawBoard();
	bool BlockCheck(int x, int y);
	bool MineCheck(int x, int y);
	void ResetGame();
	bool WinCheck();
	~Game();
};

