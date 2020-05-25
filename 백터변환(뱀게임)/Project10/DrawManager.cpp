#include "DrawManager.h"

void DrawManager::DrawBlock(int x, int y, string str)
{
	gotoxy(x *2, y);
	cout << str;
	return;
}

void DrawManager::EraseBlock(int x, int y)
{
	gotoxy(x *2, y);
	cout << "  ";
	return;
}

void DrawManager::MidText(string str, int x, int y)
{
	if (x > str.size() / 2)
		x -= str.size() / 2;
	gotoxy(x, y);
	cout << str;
	return;
}

void DrawManager::MapDraw(string str)
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (y == 0)
				DrawBlock(x, y, str);
			else if (y == MAP_HEIGHT - 1)
				DrawBlock(x, y, str);
			else
			{
				if (x == 0 || x == MAP_WIDTH - 1)
					DrawBlock(x, y, str);
			}
		}
	}
}