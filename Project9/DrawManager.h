#pragma once
#pragma once
#include<iostream>
#include<time.h>
#include<Windows.h>
#include<string>
#include<conio.h>
#include <stdlib.h>
using namespace std;

#define MAP_WIDTH 70
#define MAP_HEIGHT 50

class DrawManager
{
public:
	void DrawBlock(int x, int y, string str);
	void EraseBlock(int x, int y);
	void MidText(string str, int x, int y);
	void MapDraw(string str);
	inline void gotoxy(int x, int y)//위치 잡아주는 용도
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
};

