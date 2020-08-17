#pragma once
#include "GameImage.h"
#include <map>
using namespace std;

struct BlockData
{
	int Type;
	POINT pt;
	RECT rt;
};

class GameMap
{
private:
	bool UseMap;
	int Command_Key;
	map <int, BlockData> BlockRect;
public:
	GameMap();
	void CheckUseMap(bool Check);
	void ReleaseMap();
	void InitBloclk(int x, int y, int Type);
	BlockData MakeData(int x, int y, int Type);
	void DrawMap();
	bool CheckNotImpulse(RECT rt, bool missile = false);
	void BorkenWall(RECT rt, int ImpulseWay);
	void DrawThicket();
	inline int GetProtectBlock(int Key)
	{
		return BlockRect.find(Key)->second.Type;
	}
	inline int GetCommandCenter()
	{
		return BlockRect.find(Command_Key)->second.Type;
	}
	inline int GetCommandKey()
	{
		return Command_Key;
	}
	inline POINT GetCommandPoint()
	{
		return BlockRect.find(Command_Key)->second.pt;
	}
	~GameMap();
};

