#include "Block.h"
#include <vector>
#define SNAKE_HEAD "¡Ý"
#define SNAKE_TAIL "¡Û"
#define MAX_SPEED 400
#define BOOST_SPEED 50
#define SPEED 700
#define FEED_MAX 10
#define OBSTACLE_MAX 10

struct Direction
{
	int x;
	int y;
};

class Snake
{
private:
	vector<Block*> vec_Snake;
	int m_iSize;
	int Move_Speed;
	int MoveClock;
	Direction m_Direction;
	static Snake* m_hThis;
public:
	Snake();
	static Snake* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new Snake;
		return m_hThis;
	}
	inline int GetSize()
	{
		return m_iSize;
	}
	BlockData GetSnake();
	void SetingSnake();
	void DrawSnake();
	void MoveSnake(Block* p_Feed[]);
	void SetDirection(int x, int y);
	bool GameOver(Block* p_Obstacle[]);
	void ReSetSnake();
	void DeleteSnake();
	
	~Snake();
};