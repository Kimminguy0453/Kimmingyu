#include "Game.h"

int Menu()
{
	int Select;
	MapDraw Draw;
	system("cls");
	Draw.DrawMidText("★★★★지뢰찾기★★★★", WIDTH, HEIGHT * 0.25);
	Draw.DrawMidText("1.게임시작", WIDTH, HEIGHT * 0.25 + 2);
	Draw.DrawMidText("2.난이도 변경", WIDTH, HEIGHT * 0.25 + 3);
	Draw.DrawMidText("3.게임종료", WIDTH, HEIGHT * 0.25 + 4);
	Draw.DrawMidText("4.돌아가기", WIDTH, HEIGHT * 0.25 + 5);
	Select = Draw.MenuSelectCursor(4, 1, WIDTH *0.20, HEIGHT * 0.25 + 2);

	return Select;
}

void main()
{
	Game Gamer;

	while (1)
	{
		switch (Menu())
		{
		case 1:
			Gamer.GameStart();
			break;
		case 2:
			Gamer.GameLevel();
			break;
		case 3:
			return;
		}
	}
}