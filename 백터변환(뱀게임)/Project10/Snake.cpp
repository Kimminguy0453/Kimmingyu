#include "Snake.h"

Snake* Snake::m_hThis = NULL;
Snake::Snake()
{
}

void Snake::SetingSnake()
{
	m_iSize++;
	if (m_iSize == 1)
		vec_Snake.push_back(new Block(SNAKE_HEAD, MAP_WIDTH / 2, MAP_HEIGHT / 2));
	else
	{
		vec_Snake.push_back(new Block(SNAKE_TAIL, vec_Snake.back()->GetBackUP().x, vec_Snake.back()->GetBackUP().y));
		if (Move_Speed > MAX_SPEED)
			Move_Speed -= BOOST_SPEED;
	}
}

void Snake::DrawSnake()
{
	for (auto iter = vec_Snake.begin(); iter != vec_Snake.end(); iter++)
		(*iter)->DrawBlock();
}

void Snake::MoveSnake(Block* p_Feed[])
{
	int x;
	int y;
	if (clock() - MoveClock > Move_Speed)
	{
		for (auto iter = vec_Snake.begin(); iter != vec_Snake.end(); iter++)
		{
			(*iter)->BackUP_Point();
			(*iter)->EraseBlock();
			if (iter == vec_Snake.begin())
				(*iter)->Set_Point((*iter)->GetData().x + m_Direction.x, (*iter)->GetData().y + m_Direction.y);
			else
				(*iter)->Set_Point(x, y);
			x = (*iter)->GetBackUP().x;
			y = (*iter)->GetBackUP().y;
		}

		DrawSnake();
		MoveClock = clock();
	}
}


void Snake::SetDirection(int x, int y)
{
	m_Direction.x = x;
	m_Direction.y = y;
}


bool Snake::GameOver(Block* p_Obstacle[])
{
	auto iter = vec_Snake.begin();
	int x = (*iter)->GetData().x;
	int y = (*iter)->GetData().y;
	iter++;

	if (vec_Snake[0] != NULL)
	{
		for (iter; iter != vec_Snake.end(); iter++)
		{
				if ((*iter)->GetData().x == x && (*iter)->GetData().y == y)
					return true;
		}
	}
	if (x == 0 || x == MAP_WIDTH * 2 - 1 || y == 0 ||y == MAP_HEIGHT - 1)
		return true;
	for (int i = 0; i < OBSTACLE_MAX; i++)
	{
		if ((x == p_Obstacle[i]->GetData().x) && (y == p_Obstacle[i]->GetData().y))
			return true;
	}
	return false;
}

void Snake::ReSetSnake()
{
	m_iSize = 0;
	SetDirection(0, 0);
	Move_Speed = SPEED;
	MoveClock = clock();
}

void Snake::DeleteSnake()
{
	for (auto iter = vec_Snake.begin(); iter != vec_Snake.end(); iter++)
		delete *iter;
	vec_Snake.clear();
	delete m_hThis;
	m_hThis = NULL;
}

BlockData Snake::GetSnake()
{
	auto iter = vec_Snake.begin();

	return (*iter)->GetData();
}


Snake::~Snake()
{
}
