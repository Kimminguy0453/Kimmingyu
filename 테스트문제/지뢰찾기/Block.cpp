#include "Block.h"


Block::Block(int x, int y)
{
	m_Block.x = x;
	m_Block.y = y;
	m_Block.style = DEFAULT_BLOCK;
	m_Block.Check = false;
}

void Block::BlockCheck(int Count)
{
	m_Block.Check = true;
	if (Count == NOT_MINE)
		m_Block.style = DELETE_BLOCK;
	else if (Count == COUNT_1)
		m_Block.style = MINE_COUNT_1;
	else if (Count == COUNT_2)
		m_Block.style = MINE_COUNT_2;
	else if (Count == COUNT_3)
		m_Block.style = MINE_COUNT_3;
	else if (Count == COUNT_4)
		m_Block.style = MINE_COUNT_4;
	else if (Count == COUNT_5)
		m_Block.style = MINE_COUNT_5;
	else if (Count == COUNT_6)
		m_Block.style = MINE_COUNT_6;
	else if (Count == COUNT_7)
		m_Block.style = MINE_COUNT_7;
	else if (Count == COUNT_8)
		m_Block.style = MINE_COUNT_8;
	else if (Count == MINE)
		m_Block.style = MINE_BLOCK;
	else if (Count == CHECK)
		m_Block.style = CHECK_BLOCK;
}

void Block::DrawBlock()
{
	BACKGROUND_ORIGINAL		
		m_Draw.DrawPoint(m_Block.style, m_Block.x, m_Block.y);
	ORIGINAL
}


Block::~Block()
{

}
