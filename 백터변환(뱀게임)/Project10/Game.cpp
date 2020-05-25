#include "Game.h"

Game::Game()
{
	char str[256];
	srand(time(NULL));
	sprintf(str, "mode con: lines=%d cols=%d", MAP_HEIGHT + 5, MAP_WIDTH *2 + 5);
	system(str);
}

void Game::TitlePage()
{
	int Select;
	while (1)
	{
		system("cls");
		m_Draw.MapDraw(BLOCK_WALL);
		m_Draw.MidText("★★★★★뱀게임★★★★★", MAP_WIDTH, MAP_HEIGHT / 2 - 6);
		m_Draw.MidText("1.게임시작", MAP_WIDTH, MAP_HEIGHT / 2 - 4);
		m_Draw.MidText("2.게임종료", MAP_WIDTH, MAP_HEIGHT / 2 - 2);
		m_Draw.gotoxy(MAP_WIDTH, MAP_HEIGHT / 2);
		cin >> Select;

		switch (Select)
		{
		case GAME_STRAT:
			GameStart();
			break;
		case GAME_END:
			return;
		}
	}
}

void Game::GameStart()
{
	int MakeFeed_Speed;
	char ch;
	bool MoveFlag = false; 
	system("cls");
	m_Draw.MapDraw(BLOCK_WALL);
	MakeObstacle();
	Snake::GetInstance()->ReSetSnake();
	Snake::GetInstance()->SetingSnake();
	m_iScore = Snake::GetInstance()->GetSize() - 1;
	Snake::GetInstance()->DrawSnake();
	MakeFeed_Speed = clock();
	Scoreboard();
	while (1)
	{
		if (clock() - MakeFeed_Speed > MAKE_FEED_SPEED)
		{
			MakeFeed();
			MakeFeed_Speed = clock();
		}
		if (kbhit())
		{
			ch = getch();
			switch (ch)
			{
			case MOVE_UP:
				Snake::GetInstance()->SetDirection(NON, DOWN);
				MoveFlag = true;
				break;
			case MOVE_DOWN:
				Snake::GetInstance()->SetDirection(NON, UP);
				MoveFlag = true;
				break;
			case MOVE_LEFT:
				Snake::GetInstance()->SetDirection(DOWN, NON);
				MoveFlag = true;
				break;
			case MOVE_RIGHT:
				Snake::GetInstance()->SetDirection(UP, NON);
				MoveFlag = true;
				break;
			}
		}
		if (MoveFlag == true)
		{
			Snake::GetInstance()->MoveSnake(m_Block_FEED);
			EatFeed(Snake::GetInstance()->GetSnake().x, Snake::GetInstance()->GetSnake().y);
			if (Snake::GetInstance()->GameOver(m_Block_OBSTACLE) == true)
			{
				system("cls");
				m_Draw.MidText("게임오버", MAP_WIDTH, MAP_HEIGHT / 2);
				ReSetBlock(m_Block_OBSTACLE, OBSTACLE_MAX);
				ReSetBlock(m_Block_FEED, FEED_MAX);
				Snake::GetInstance()->DeleteSnake();
				m_iScore = 0;
				getch();
				return;
			}
			if (m_iScore != Snake::GetInstance()->GetSize() - 1)
			{
				Scoreboard();
				m_iScore++;
			}
		}
	}
}

void Game::Scoreboard()
{
	string str;
	str = "게임 스코어 : ";
	m_Draw.gotoxy(MAP_WIDTH - str.size() / 2, MAP_HEIGHT + 3);
	cout << str << Snake::GetInstance()->GetSize()-1 << endl;
}

void Game::MakeObstacle()
{
	int x, y = 0;
	bool b;
	for (int i = 0; i < OBSTACLE_MAX; i++)
	{
		if(m_Block_OBSTACLE[i] == NULL)
			m_Block_OBSTACLE[i] = new Block;
		m_Block_OBSTACLE[i]->BlockStyle(BLOCK_OBSTACLE);
		while(1)
		{
			b = false;
			x = rand() % (MAP_WIDTH-2) + 1;
			y = rand() % (MAP_HEIGHT-2) + 1;
			if (BlockCheck(m_Block_OBSTACLE, i, x, y) == false)
			{
				m_Block_OBSTACLE[i]->Set_Point(x, y);
				break;
			}
		}
	}
	for (int i = 0; i < OBSTACLE_MAX; i++)
		m_Block_OBSTACLE[i]->DrawBlock();
}	

void Game::MakeFeed()
{
	int x, y;
	bool b;
	for (int i = 0; i < FEED_MAX; i++)
	{
		if (m_Block_FEED[i] == NULL)
		{
			m_Block_FEED[i] = new Block;
			m_Block_FEED[i]->BlockStyle(BLOCK_FEED);
			while (1)
			{
				b = false;
				x = rand() % (MAP_WIDTH-2) + 1;
				y = rand() % (MAP_HEIGHT - 2) + 1;
				if (BlockCheck(m_Block_OBSTACLE, OBSTACLE_MAX, x, y) == false && BlockCheck(m_Block_FEED, i, x, y) == false)
				{
					m_Block_FEED[i]->Set_Point(x, y);
					m_Block_FEED[i]->DrawBlock();
					return;
				}
			}
		}
	}
}


bool Game::BlockCheck(Block* CheckBlock[], int Max, int x, int y)
{
	bool b;
	b = false;
	for (int i = 0; i < Max; i++)
	{
		if (m_Block_OBSTACLE[i]->GetData().x == x && m_Block_OBSTACLE[i]->GetData().y == y)
			b = true;
	}
	return b;
}

void Game::EatFeed(int x, int y)
{
	for (int i = 0; i < FEED_MAX; i++)
	{
		if (m_Block_FEED[i] != NULL)
		{
			if ((x == (m_Block_FEED[i]->GetData().x)) && (y == (m_Block_FEED[i]->GetData().y)))
			{
				Snake::GetInstance()->SetingSnake();
				Snake::GetInstance()->DrawSnake();
				delete m_Block_FEED[i];
				m_Block_FEED[i] = NULL;
				break;
			}
		}
	}
}

void Game::ReSetBlock(Block*  DeleteBlock[], int Max)
{
	for (int i = 0; i < Max; i++)
	{
		if (DeleteBlock[i] != NULL)
		{
			delete DeleteBlock[i];
			DeleteBlock[i] = NULL;
		}
	}
}

Game::~Game()
{
}
