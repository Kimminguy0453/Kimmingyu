#include "Game.h"

int Menu()
{
	int Select;
	MapDraw Draw;
	system("cls");
	Draw.DrawMidText("�ڡڡڡ�����ã��ڡڡڡ�", WIDTH, HEIGHT * 0.25);
	Draw.DrawMidText("1.���ӽ���", WIDTH, HEIGHT * 0.25 + 2);
	Draw.DrawMidText("2.���̵� ����", WIDTH, HEIGHT * 0.25 + 3);
	Draw.DrawMidText("3.��������", WIDTH, HEIGHT * 0.25 + 4);
	Draw.DrawMidText("4.���ư���", WIDTH, HEIGHT * 0.25 + 5);
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