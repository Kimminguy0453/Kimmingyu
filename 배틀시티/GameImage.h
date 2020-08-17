#pragma once
#include <Windows.h>
#define BLOCK_WIDTH 56
#define BLOCK_HEIGHT 48
#define CHARACTER_WIDTH 51
#define CHARACTER_HEIGHT 43
#define MISSILE_WIDTH 15
#define MISSILE_HEIGHT 7

#define PLAYER 16
#define ENEMY 17

#define BLOCK_TYPE_MAX 15
#define PLAYER_MOVE_MAX 8
#define ENEMY_MOVE_MAX 12

#define ICON_X 800
#define STAGE_ICON_Y 80
#define PLAYER_ICON_Y 150
#define ENEMY_ICON_Y 330


enum BLCOK_TYPE
{
	NOT_BLOCK,
	INTACT_BRICK,
	TOP_BRICK,
	LEFT_BRICK,
	BOTTOM_BRICK,
	RIGHT_BRICK,
	ICE,//얼음지역
	THICKET,//수풀
	WATER,//물지역
	INTACT_METAL,
	TOP_METAL,
	LEFT_METAL,
	BOTTOM_METAL,
	RIGHT_METAL,
	COMMAND_CENTER,
	DEFEAT,
	BLOCK_MAX
};

enum CHARACTER_MOVE
{
	DOWN_1,
	DOWN_2,
	LEFT_1,
	LEFT_2,
	RIGHT_1,
	RIGHT_2,
	UP_1,
	UP_2,
	DOWN_DAMAGE,
	LEFT_DAMAGE,
	RIGHT_DAMAGE,
	UP_DAMAGE
};

enum MOVEWAY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	STOP
};

enum DTAT_INTERFACE
{
	STAGE_ICON,
	ENEMY_ICON,
	PLAYER_ICON,
	ICON_MAX
};

struct IMAGE
{
	HDC MemDC;
	HBITMAP UseImage;
	HBITMAP OldImage;
};

class GameImage
{
private:
	IMAGE Screen;
	IMAGE Block[BLOCK_MAX];
	IMAGE IconImage[ICON_MAX];
	IMAGE Unit;
	IMAGE m_Missile;
	static GameImage* m_hThis;
public:
	static GameImage* GetImageMaker()
	{
		if (m_hThis == NULL)
			m_hThis = new GameImage;
		return m_hThis;
	}
	void SetBlock(HDC hdc);
	LPCTSTR SetBlockID(int Type);
	LPCTSTR SetIcon(int Type);
	//그리기
	void DrawBlock(int Type, int x, int y);
	void DrawUnit(LPCTSTR ID, int x, int y);
	void DrawMissle(LPCTSTR ID, int x, int y, int Width, int Height);
	void DrawGameIcon(int x, int y, int Type, int Count);
	//
	BITMAP CheckImageSize(HBITMAP Tmp);
	void SetScreen(bool Custom);
	void DrawScreen(HDC hdc);
	void ReleaseMap();
	void DeleteMaker();
};

