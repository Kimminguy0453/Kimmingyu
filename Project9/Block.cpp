#include "Block.h"



Block::Block()
{
}

Block::Block(string str, int x, int y)
{
	m_Data.str = str;
	m_Data.x = x;
	m_Data.y = y;
}

void Block::BackUP_Point()
{
	m_BackUp.x = m_Data.x;
	m_BackUp.y = m_Data.y;
}

void Block::BlockStyle(string str)
{
	m_Data.str = str;
}

void Block::DrawBlock()
{
	m_Draw.DrawBlock(m_Data.x, m_Data.y, m_Data.str);
}

void Block::EraseBlock()
{
	m_Draw.EraseBlock(m_Data.x, m_Data.y);
}

void Block::Set_Point(int x, int y)
{
	m_Data.x = x;
	m_Data.y = y;
}

Block::~Block()
{

}
