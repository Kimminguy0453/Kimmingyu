#include "Game.h"

Game::Game()
{
	char buf[256];
	sprintf(buf, "mode con: cols=%d lines=%d", WIDTH * 2, HEIGHT + 5);
	system(buf);
	MineCount = EASY;

	m_Player.x = WIDTH / 2;
	m_Player.y = HEIGHT / 2;
}



void Game::GameStart()
{
	system("cls");
	SetBoard();
	Block* tmp;
	SetMine();
	BACKGROUND_ORIGINAL
		m_Draw.BoxDraw(0, 0, WIDTH, HEIGHT);
	ORIGINAL
	DrawBoard();
	DrawPlayer();
	while (1)
	{
		if (kbhit())
		{
			switch (getch())
			{
			case UP:
				if (m_Player.y - 1 >= 1)
				{
					Black_ReDraw(m_Player.x, m_Player.y);
					m_Player.y--;
					m_Draw.DrawPoint(m_Player.Block, m_Player.x, m_Player.y);
				}
				break;
			case DOWN:
				if (m_Player.y + 1 < HEIGHT - 1)
				{
					Black_ReDraw(m_Player.x, m_Player.y);
					m_Player.y++;
					m_Draw.DrawPoint(m_Player.Block, m_Player.x, m_Player.y);
				}
				break;
			case RIGHT:
				if (m_Player.x + 1 < WIDTH - 1)
				{
					Black_ReDraw(m_Player.x, m_Player.y);
					m_Player.x++;
					m_Draw.DrawPoint(m_Player.Block, m_Player.x, m_Player.y);
				}
				break;
			case LEFT:
				if (m_Player.x - 1 >= 1)
				{
					Black_ReDraw(m_Player.x, m_Player.y);
					m_Player.x--;
					m_Draw.DrawPoint(m_Player.Block, m_Player.x, m_Player.y);
				}
				break;
			case SPACE:
				if (BlockCheck(m_Player.x, m_Player.y))
				{
					DrawBoard();
					m_Draw.DrawMidText("Game Over!", WIDTH, HEIGHT / 2);
					ResetGame();
					getch();
					return;
				}
				else
				{
					if (WinCheck())
					{
						DrawBoard();
						m_Draw.DrawMidText("Game Win!", WIDTH, HEIGHT / 2);
						ResetGame();
						getch();
						return;
					}
					else
					{
						DrawBoard();
						DrawPlayer();
					}
				}
				break;
			case 'q':
				for (auto iter = vec_BoardList.begin(); iter != vec_BoardList.end(); iter++)
				{
					if ((*iter)->GetBlock().x == m_Player.x && (*iter)->GetBlock().y == m_Player.y)
					{
						(*iter)->BlockCheck(CHECK);
						break;
					}
				}
				break;
			}
		}
	}
}

void Game::Black_ReDraw(int x, int y)
{
	for (auto iter = vec_BoardList.begin(); iter != vec_BoardList.end(); iter++)
	{
		if ((*iter)->GetBlock().x == x && (*iter)->GetBlock().y == y)
		{
			(*iter)->DrawBlock();
			break;
		}
	}
}


bool Game::BlockCheck(int x, int y)
{
	int count = 0;
	if (MineCheck(x, y))
		return true;
	else
	{
		if ((x >= 1 && x < WIDTH - 1) && (y >= 1 && y < HEIGHT - 1))
		{
			for (auto iter = vec_BoardList.begin(); iter < vec_BoardList.end(); iter++)
			{
				if ((*iter)->GetBlock().x == x && (*iter)->GetBlock().y == y)
				{
					if (MineCheck(x - 1, y - 1))
						count++;
					if (MineCheck(x - 1, y))
						count++;
					if (MineCheck(x - 1, y + 1))
						count++;
					if (MineCheck(x, y - 1))
						count++;
					if (MineCheck(x - 1, y + 1))
						count++;
					if (MineCheck(x + 1, y - 1))
						count++;
					if (MineCheck(x + 1, y))
						count++;
					if (MineCheck(x + 1, y + 1))
						count++;
					if (count == 0 && !(*iter)->GetBlock().Check)
					{
						(*iter)->BlockCheck();
						BlockCheck(x - 1, y - 1);
						BlockCheck(x - 1, y);
						BlockCheck(x - 1, y + 1);
						BlockCheck(x, y - 1);
						BlockCheck(x, y + 1);
						BlockCheck(x + 1, y - 1);
						BlockCheck(x + 1, y);
						BlockCheck(x + 1, y + 1);
					}
					else
						(*iter)->BlockCheck(count);
					break;
				}
			}
		}
	}
	return false;
}

bool Game::MineCheck(int x, int y)
{
	for (auto iter = vec_MineList.begin(); iter < vec_MineList.end(); iter++)
	{
		if ((*iter)->GetBlock().x == x && (*iter)->GetBlock().y == y)
			return true;
	}
	return false;
}



void Game::GameLevel()
{
	int Select;
	system("cls");
	m_Draw.DrawMidText("★★★★난이도★★★★", WIDTH, HEIGHT * 0.25);
	m_Draw.DrawMidText("1.Easy", WIDTH, HEIGHT * 0.25 + 2);
	m_Draw.DrawMidText("2.Nomal", WIDTH, HEIGHT * 0.25 + 3);
	m_Draw.DrawMidText("3.Hard", WIDTH, HEIGHT * 0.25 + 4);
	m_Draw.DrawMidText("4.돌아가기", WIDTH, HEIGHT * 0.25 + 5);
	Select = m_Draw.MenuSelectCursor(4, 1, WIDTH *0.20, HEIGHT * 0.25 + 2);

	switch (Select)
	{
	case 1:
		MineCount = 10;
		break;
	case 2:
		MineCount = 15;
		break;
	case 3:
		MineCount = 20;
		break;
	case 4:
		return;
	}
}

void Game::DrawPlayer()
{
	m_Draw.DrawPoint(m_Player.Block, m_Player.x, m_Player.y);
}

void Game::SetBoard()
{
	for (int x = 1; x < WIDTH - 1; x++)
	{
		for(int y = 1; y < HEIGHT - 1; y++)
			vec_BoardList.push_back(new Block(x, y));
	}
}

void Game::SetMine()
{
	int x, y;
	bool Check;
	srand(time(NULL));
	for (int i = 1; i <= MineCount; i++)
	{
		Check = true;
		x = rand() % (WIDTH - 2) + 1;
		y = rand() % (HEIGHT - 2) + 1;
		for (auto iter = vec_MineList.begin(); iter != vec_MineList.end(); iter++)
		{
			if ((*iter)->GetBlock().x == x && (*iter)->GetBlock().y == y)
				Check = false;
		}
		if (Check)
			vec_MineList.push_back(new Block(x, y));
		else
			i--;
	}
}

void Game::DrawBoard()
{
	for (auto iter = vec_BoardList.begin(); iter != vec_BoardList.end(); iter++)
		(*iter)->DrawBlock();
}

void Game::ResetGame()
{
	for (auto iter = vec_BoardList.begin(); iter != vec_BoardList.end(); iter++)
		delete (*iter);
	vec_BoardList.clear();
	for (auto iter = vec_MineList.begin(); iter != vec_MineList.end(); iter++)
		delete (*iter);
	vec_MineList.clear();
}

bool Game::WinCheck()
{
	int Check_Count = 0;
	for (auto iter = vec_BoardList.begin(); iter != vec_BoardList.end(); iter++)
	{
		if(!(*iter)->GetBlock().Check)
			Check_Count++;
	}
	if (Check_Count == vec_MineList.size())
		return true;
	else
		return false;
}

Game::~Game(){}