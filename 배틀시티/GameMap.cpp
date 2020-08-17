#include "GameMap.h"

GameMap::GameMap()
{
	int Key;
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			Key = j + i * 13;
			if (Key == 139)
				Key = 139;
			BlockRect.insert(pair<int, BlockData>(Key, MakeData(j, i, NOT_BLOCK)));
		}
	}
}

void GameMap::CheckUseMap(bool Check)
{
	UseMap = Check;
}

void GameMap::InitBloclk(int x, int y, int Type)
{
	int Key = x + y * 13;
	BlockRect.find(Key)->second.Type = Type;


	BlockRect.find(Key)->second.rt.top = 50 + y * BLOCK_HEIGHT;
	BlockRect.find(Key)->second.rt.bottom = (50 + y * BLOCK_HEIGHT) + BLOCK_HEIGHT;
	BlockRect.find(Key)->second.rt.left = 50 + x * BLOCK_WIDTH;
	BlockRect.find(Key)->second.rt.right = (50 + x * BLOCK_WIDTH) + BLOCK_WIDTH;


	if (Type == TOP_BRICK || Type == TOP_METAL)
		BlockRect.find(Key)->second.rt.bottom = (50 + y * BLOCK_HEIGHT) + (BLOCK_HEIGHT / 2);
	else if (Type == BOTTOM_BRICK || Type == BOTTOM_METAL)
		BlockRect.find(Key)->second.rt.top = (50 + y * BLOCK_HEIGHT) + (BLOCK_HEIGHT / 2);
	else if (Type == LEFT_BRICK || Type == LEFT_METAL)
		BlockRect.find(Key)->second.rt.right = (50 + x * BLOCK_WIDTH) + (BLOCK_WIDTH / 2);
	else if (Type == RIGHT_BRICK || Type == RIGHT_METAL)
		BlockRect.find(Key)->second.rt.left = (50 + x * BLOCK_WIDTH) + (BLOCK_WIDTH / 2);

	if (Type == COMMAND_CENTER)
		Command_Key = Key;
}


void GameMap::ReleaseMap()
{
	if (BlockRect.size() != 0)
		BlockRect.clear();
}

BlockData GameMap::MakeData(int x, int y, int Type)
{
	BlockData tmp;
	tmp.Type = Type;
	tmp.pt.x = x;
	tmp.pt.y = y;
	tmp.rt = { 50 + x * BLOCK_WIDTH , 50 + y * BLOCK_HEIGHT,  (50 + x * BLOCK_WIDTH) + BLOCK_WIDTH , (50 + y * BLOCK_HEIGHT) + BLOCK_HEIGHT };
	return tmp;
}

void GameMap::DrawMap()
{
	if (UseMap)
	{
		for (auto iter = BlockRect.begin(); iter != BlockRect.end(); iter++)
		{
			if ((*iter).second.Type != 0)
				GameImage::GetImageMaker()->DrawBlock((*iter).second.Type, (*iter).second.pt.x, (*iter).second.pt.y);
		}
	}
}

void GameMap::DrawThicket()
{
	for (auto iter = BlockRect.begin(); iter != BlockRect.end(); iter++)
	{
		if ((*iter).second.Type == THICKET)
			GameImage::GetImageMaker()->DrawBlock((*iter).second.Type, (*iter).second.pt.x, (*iter).second.pt.y);
	}
}

bool GameMap::CheckNotImpulse(RECT rt, bool missile)
{
	RECT tmp;
	for (auto iter = BlockRect.begin(); iter != BlockRect.end(); iter++)
	{
		if ((*iter).second.Type != NOT_BLOCK && (*iter).second.Type != ICE && (*iter).second.Type != THICKET)
		{
			if (IntersectRect(&tmp, &rt, &((*iter).second.rt)))
			{
				if (missile && (*iter).second.Type == WATER)
					return true;
				else
					return false;
			}
		}
	}
	return true;
}

void GameMap::BorkenWall(RECT rt, int ImpulseWay)
{
	RECT tmp;
	bool check = false;
	for (auto iter = BlockRect.begin(); iter != BlockRect.end(); iter++)
	{
		if (IntersectRect(&tmp, &rt, &((*iter).second.rt)))
		{
			if ((*iter).second.Type == INTACT_BRICK)
			{
				if (ImpulseWay == LEFT)
				{
					InitBloclk((*iter).second.pt.x, (*iter).second.pt.y, LEFT_BRICK);
					break;
				}
				else if (ImpulseWay == RIGHT)
				{
					InitBloclk((*iter).second.pt.x, (*iter).second.pt.y, RIGHT_BRICK);
					break;
				}
				else if (ImpulseWay == UP)
				{
					InitBloclk((*iter).second.pt.x, (*iter).second.pt.y, TOP_BRICK);
					break;
				}
				else if (ImpulseWay == DOWN)
				{
					InitBloclk((*iter).second.pt.x, (*iter).second.pt.y, BOTTOM_BRICK);
					break;
				}
			}
			else if ((*iter).second.Type == TOP_BRICK || (*iter).second.Type == RIGHT_BRICK || (*iter).second.Type == LEFT_BRICK || (*iter).second.Type == BOTTOM_BRICK)
			{
				InitBloclk((*iter).second.pt.x, (*iter).second.pt.y, NOT_BLOCK);
				break;
			}
			else if ((*iter).second.Type == COMMAND_CENTER)
			{
				InitBloclk((*iter).second.pt.x, (*iter).second.pt.y, DEFEAT);
				break;
			}
		}
	}
}
GameMap::~GameMap()
{
	ReleaseMap();
}