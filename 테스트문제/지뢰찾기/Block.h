#include "MapDraw.h"
#define DELETE_BLOCK "¢Ë"

#define DEFAULT_BLOCK "¡à"
#define MINE_COUNT_1 "¨ç"
#define MINE_COUNT_2 "¨è"
#define MINE_COUNT_3 "¨é"
#define MINE_COUNT_4 "¨ê"
#define MINE_COUNT_5 "¨ë"
#define MINE_COUNT_6 "¨ì"
#define MINE_COUNT_7 "¨í"
#define MINE_COUNT_8 "¨î"
#define MINE_BLOCK "¢Á"
#define CHECK_BLOCK "¢Â"

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


