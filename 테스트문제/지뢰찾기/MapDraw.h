#pragma once
#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<string>
#include<fstream>
#include<time.h>
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define SPACE 32
#define ENTER 13
#define WIDTH 16
#define HEIGHT 16
using namespace std;


//////////////////////////////////////////////////////
#define col GetStdHandle(STD_OUTPUT_HANDLE) 		//색상 지정
#define ORIGINAL SetConsoleTextAttribute( col,0x0007 );
#define RED SetConsoleTextAttribute( col,0x000c );
#define BACKGROUND_ORIGINAL SetConsoleTextAttribute( col,0x0087 );
#define BACKGROUND_RED SetConsoleTextAttribute( col,0x008c );
///////////////////////

class MapDraw
{
public:
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	void BoxDraw(int Start_x, int Start_y, int Width, int Height);
	void ErasePoint(int x, int y);
	void DrawPoint(string str, int x, int y);
	void BoxErase(int Width, int Height);
	void DrawMidText(string str, int x, int y);
	void ButtonDraw();
	int MenuSelectCursor(int MenuLen, int AddCol, int x, int y);
};

