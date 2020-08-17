#include "GameImage.h"

GameImage* GameImage::m_hThis = NULL;
void GameImage::SetBlock(HDC hdc)
{
	Screen.MemDC = CreateCompatibleDC(hdc);
	Screen.UseImage = CreateCompatibleBitmap(hdc, 1000, 700);
	Screen.OldImage = (HBITMAP)SelectObject(Screen.MemDC, Screen.UseImage);

	for (int i = 0; i < BLOCK_TYPE_MAX; i++)
	{
		Block[i].MemDC = CreateCompatibleDC(Screen.MemDC);
		Block[i].UseImage = (HBITMAP)LoadImage(NULL, SetBlockID(i+1), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		Block[i].OldImage = (HBITMAP)SelectObject(Block[i].MemDC, Block[i].UseImage);
	}
	for (int i = 0; i < ICON_MAX; i++)
	{
		IconImage[i].MemDC = CreateCompatibleDC(Screen.MemDC);
		IconImage[i].UseImage = (HBITMAP)LoadImage(NULL, SetIcon(i), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		IconImage[i].OldImage = (HBITMAP)SelectObject(IconImage[i].MemDC, IconImage[i].UseImage);
	}
}



void GameImage::SetScreen(bool Custom)
{
	HBRUSH hGray = (HBRUSH)GetStockObject(GRAY_BRUSH);
	SelectObject(Screen.MemDC, hGray);
	Rectangle(Screen.MemDC, 0, 0, 1000, 700);
	if (Custom)
	{
		HBRUSH hWhite = (HBRUSH)GetStockObject(WHITE_BRUSH);
		HBRUSH hold = (HBRUSH)SelectObject(Screen.MemDC, hWhite);
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 13; j++)
				Rectangle(Screen.MemDC, 50 + j* BLOCK_WIDTH, 50 + i * BLOCK_HEIGHT, (j* BLOCK_WIDTH + 50) + BLOCK_WIDTH , (i * BLOCK_HEIGHT + 50) + BLOCK_HEIGHT);
		}
		SelectObject(Screen.MemDC, Screen.UseImage);
		DeleteObject(hWhite);// 브러쉬 삭제
	}
	else
	{
		HBRUSH hBlack = (HBRUSH)GetStockObject(BLACK_BRUSH);
		SelectObject(Screen.MemDC, hBlack);
		Rectangle(Screen.MemDC, 50, 50, 13* BLOCK_WIDTH + 50, 13* BLOCK_HEIGHT + 50);
		SelectObject(Screen.MemDC, Screen.UseImage);
		DeleteObject(hBlack);
		SetTextColor(Screen.MemDC, RGB(255, 255, 255));
		SetBkColor(Screen.MemDC, RGB(0, 0, 0));
		TextOut(Screen.MemDC, ICON_X, STAGE_ICON_Y - 20, TEXT("STAGE"), 5);
		TextOut(Screen.MemDC, ICON_X, PLAYER_ICON_Y - 20, TEXT("PLAYER"), 6);
		TextOut(Screen.MemDC, ICON_X, ENEMY_ICON_Y - 20, TEXT("ENEMY"), 5);
	}

	DeleteObject(hGray);
}

void GameImage::DrawBlock(int Type, int x, int y)
{
	BITMAP btSize = CheckImageSize(Block[Type - 1].UseImage);
	TransparentBlt(Screen.MemDC, 50 + x * BLOCK_WIDTH, 50 + y * BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT, Block[Type - 1].MemDC, 0, 0, btSize.bmWidth, btSize.bmHeight, RGB(255, 0, 255));

}

void GameImage::DrawUnit(LPCTSTR ID, int x, int y)
{
	Unit.MemDC = CreateCompatibleDC(Screen.MemDC);
	Unit.UseImage = (HBITMAP)LoadImage(NULL, ID, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_Missile.OldImage = (HBITMAP)SelectObject(Unit.MemDC, Unit.UseImage);

	BITMAP btSize = CheckImageSize(Unit.UseImage);
	TransparentBlt(Screen.MemDC, x, y, CHARACTER_WIDTH, CHARACTER_HEIGHT, Unit.MemDC, 0, 0, btSize.bmWidth, btSize.bmHeight, RGB(255, 0, 255));

	SelectObject(Unit.MemDC, Unit.OldImage);
	DeleteObject(Unit.UseImage);
	DeleteDC(Unit.MemDC);
}

void GameImage::DrawMissle(LPCTSTR ID, int x, int y, int Width, int Height)
{
	m_Missile.MemDC = CreateCompatibleDC(Screen.MemDC);
	m_Missile.UseImage = (HBITMAP)LoadImage(NULL, ID, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_Missile.OldImage = (HBITMAP)SelectObject(m_Missile.MemDC, m_Missile.UseImage);

	BITMAP btSize = CheckImageSize(m_Missile.UseImage);
	TransparentBlt(Screen.MemDC, x, y, Width, Height, m_Missile.MemDC, 0, 0, btSize.bmWidth, btSize.bmHeight, RGB(255, 0, 255));

	SelectObject(m_Missile.MemDC, m_Missile.OldImage);
	DeleteObject(m_Missile.UseImage);
	DeleteDC(m_Missile.MemDC);
}

BITMAP GameImage::CheckImageSize(HBITMAP Tmp)
{
	BITMAP btSize;
	GetObject(Tmp, sizeof(btSize), &btSize);
	return btSize;
}

void GameImage::DrawScreen(HDC hdc)
{
	TransparentBlt(hdc, 0, 0, 1000, 700, Screen.MemDC, 0, 0, 1000, 700, RGB(255, 0, 255));
}

void GameImage::DrawGameIcon(int x, int y, int Type, int Count)
{
	int Range = 0;
	BITMAP btSize = CheckImageSize(IconImage[Type].UseImage);
	for (int i = 0; i < Count; i++)
	{
		if (Type == STAGE_ICON)
		{
			TransparentBlt(Screen.MemDC, x + Range, y, 15, 15, IconImage[Type].MemDC, 0, 0, btSize.bmWidth, btSize.bmHeight, RGB(255, 0, 255));
			Range += 30;
		}
		else
		{
			TransparentBlt(Screen.MemDC, x + Range, y + 16 * (i / 2), 15, 15, IconImage[Type].MemDC, 0, 0, btSize.bmWidth, btSize.bmHeight, RGB(255, 0, 255));
			Range += 30;
			if(Range == 60)
				Range = 0;
		}
	}
}

LPCTSTR GameImage::SetBlockID(int Type)
{
	if (Type == INTACT_BRICK)
		return TEXT("BattleCity\\block00.bmp");
	else if (Type == TOP_BRICK)
		return TEXT("BattleCity\\block01.bmp");
	else if (Type == LEFT_BRICK)
		return TEXT("BattleCity\\block02.bmp");
	else if (Type == BOTTOM_BRICK)
		return TEXT("BattleCity\\block03.bmp");
	else if (Type == RIGHT_BRICK)
		return TEXT("BattleCity\\block04.bmp");
	else if (Type == ICE)
		return TEXT("BattleCity\\block05.bmp");
	else if (Type == THICKET)
		return TEXT("BattleCity\\block06.bmp");
	else if (Type == WATER)
		return TEXT("BattleCity\\block07.bmp");
	else if (Type == INTACT_METAL)
		return TEXT("BattleCity\\block08.bmp");
	else if (Type == TOP_METAL)
		return TEXT("BattleCity\\block09.bmp");
	else if (Type == LEFT_METAL)
		return TEXT("BattleCity\\block10.bmp");
	else if (Type == BOTTOM_METAL)
		return TEXT("BattleCity\\block11.bmp");
	else if (Type == RIGHT_METAL)
		return TEXT("BattleCity\\block12.bmp");
	else if (Type == COMMAND_CENTER)
		return TEXT("BattleCity\\block13.bmp");
	else if (Type == DEFEAT)
		return TEXT("BattleCity\\block14.bmp");
}

LPCTSTR GameImage::SetIcon(int Type)
{
	if (Type == STAGE_ICON)
		return TEXT("BattleCity\\stage_icon.bmp");
	else if (Type == ENEMY_ICON)
		return TEXT("BattleCity\\enemy_icon.bmp");
	else if (Type == PLAYER_ICON)
		return TEXT("BattleCity\\player_icon.bmp");
}

void GameImage::ReleaseMap()
{
	for (int i = 0; i < BLOCK_TYPE_MAX; i++)
	{
		SelectObject(Block[i].MemDC, Block[i].OldImage);
		DeleteObject(Block[i].UseImage);
		DeleteDC(Block[i].MemDC);
	}
	for (int i = 0; i < ICON_MAX; i++)
	{
		SelectObject(IconImage[i].MemDC, IconImage[i].OldImage);
		DeleteObject(IconImage[i].UseImage);
		DeleteDC(IconImage[i].MemDC);
	}
	SelectObject(Screen.MemDC, Screen.OldImage);
	DeleteObject(Screen.UseImage);
	DeleteDC(Screen.MemDC);
}

void GameImage::DeleteMaker()
{
	delete m_hThis;
	m_hThis = NULL;
}