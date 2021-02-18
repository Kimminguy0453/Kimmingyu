#pragma once
#include "JEngine.h"
#include "GlobalDefine.h"
#include "SingleTon.h"
#include "Defines.h"

class Rank : public SingleTon<Rank>
{
private:
	int PaperRank[5];
	int FlightRank[5];
	int GameType;
public:
	Rank();
	void LoadRank();
	void SaveRank(int type);
	void RenewalRank(int Score, int type);
	void InitGameType(int type);
	int GetScore(int Type, int i = 0)
	{
		if(Type == SCENE_INDEX_PAPER)
			return PaperRank[i];
		else
			return FlightRank[i];
	}
	int GetGameType()
	{
		return GameType;
	}

	~Rank();
};

