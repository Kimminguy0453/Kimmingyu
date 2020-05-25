#pragma once
#include "Snake.h"

#define MOVE_UP 'w'
#define MOVE_DOWN 's'
#define MOVE_LEFT 'a'
#define MOVE_RIGHT 'd'
#define MAKE_FEED_SPEED 1000

enum TITLE_OPTION
{
	GAME_STRAT = 1,
	GAME_END
};

enum MOVE
{
	DOWN = -1,
	NON,
	UP
};

class Game
{
private:
	Block* m_Block_OBSTACLE[OBSTACLE_MAX] = {NULL};
	Block *m_Block_FEED[FEED_MAX] = { NULL };;
	DrawManager m_Draw;
	int m_iScore;
public:
	Game();
	void GameStart();
	void TitlePage();
	void MakeObstacle();
	void MakeFeed();
	void Scoreboard();
	bool BlockCheck(Block* CheckBlock[], int Max, int x ,int y);
	void EatFeed(int x, int y);
	void ReSetBlock(Block* DeleteBlock[], int Max);
	~Game();
};

