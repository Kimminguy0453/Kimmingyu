#include "MapDraw.h"
#define DELETE_BLOCK "��"

#define DEFAULT_BLOCK "��"
#define MINE_COUNT_1 "��"
#define MINE_COUNT_2 "��"
#define MINE_COUNT_3 "��"
#define MINE_COUNT_4 "��"
#define MINE_COUNT_5 "��"
#define MINE_COUNT_6 "��"
#define MINE_COUNT_7 "��"
#define MINE_COUNT_8 "��"
#define MINE_BLOCK "��"
#define CHECK_BLOCK "��"

enum BLOCK_TYPE
{
	NOT_MINE,
	COUNT_1,
	COUNT_2,
	COUNT_3,
	COUNT_4,
	COUNT_5,
	COUNT_6,
	COUNT_7,
	COUNT_8,
	MINE,
	CHECK
};
struct BlockData
{
	int x;
	int y;
	string style;
	bool Check;
};

class Block
{
private:
	BlockData m_Block;
	MapDraw m_Draw;
public:
	Block(int x, int y);
	void DrawBlock();
	void BlockCheck(int Count = 0);
	inline BlockData GetBlock()
	{
		return m_Block;
	}
	~Block();
};


