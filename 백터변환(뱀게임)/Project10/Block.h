#include "DrawManager.h"
#define BLOCK_WALL "¢Ë"
#define BLOCK_OBSTACLE "¢Ã"
#define BLOCK_FEED "¡Ú"

struct BlockData
{
	int x;
	int y;
	string str;
};

struct Back_Up
{
	int x;
	int y;
};

class Block
{
private:
	BlockData m_Data;
	DrawManager m_Draw;
	Back_Up m_BackUp;
public:
	Block();
	Block(string str, int x, int y);
	void EraseBlock();
	void Set_Point(int x, int y);
	void BackUP_Point();
	void DrawBlock();
	void BlockStyle(string str);
	inline BlockData GetData()
	{
		return m_Data;
	}
	inline Back_Up GetBackUP()
	{
		return m_BackUp;
	}
	~Block();
};

