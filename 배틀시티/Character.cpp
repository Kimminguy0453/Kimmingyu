#include "Character.h"

void Character::InitMap(GameMap* Map)
{
	ReadMap = Map;
	UseUnit = false;
}

void Character::SetDataPoint()
{
	m_Data.pt.x = m_Data.rt.left;
	m_Data.pt.y = m_Data.rt.top;
}

void Character::ReleaseFrame()
{
	FrameCounter = 0;
	SetDataPoint();
}

void Character::DrawCharacter()
{
	GameImage::GetImageMaker()->DrawUnit(m_Image, m_Data.rt.left, m_Data.rt.top);
}

void Character::SetWayImage(int Way)
{
	if (Way == LEFT)
	{
		if (WayImage != LEFT_1)
			WayImage = LEFT_1;
		else
			WayImage = LEFT_2;
	}
	else if(Way == RIGHT)
	{
		if (WayImage != RIGHT_1)
			WayImage = RIGHT_1;
		else
			WayImage = RIGHT_2;
	}
	else if (Way == UP)
	{
		if (WayImage != UP_1)
			WayImage = UP_1;
		else
			WayImage = UP_2;
	}
	else if (Way == DOWN)
	{
		if (WayImage != DOWN_1)
			WayImage = DOWN_1;
		else
			WayImage = DOWN_2;
	}
	ImageID();
}

void Character::SetRect(int x, int y)
{
	m_Data.rt.left = x;
	m_Data.rt.top = y;
	m_Data.rt.right = m_Data.rt.left + CHARACTER_WIDTH;
	m_Data.rt.bottom = m_Data.rt.top + CHARACTER_HEIGHT;
}


Missile* Character::MakeMissile()
{
	Shoot = false;
	if (MoveWay == LEFT)
		return new Missile(ReadMap, m_Data.Type, MoveWay, m_Data.rt.left, m_Data.rt.top + (CHARACTER_HEIGHT / 2) - 3);
	else if (MoveWay == RIGHT)
		return new Missile(ReadMap, m_Data.Type, MoveWay, m_Data.rt.right, m_Data.rt.top + (CHARACTER_HEIGHT / 2) - 3);
	else if (MoveWay == UP)
		return new Missile(ReadMap, m_Data.Type, MoveWay, m_Data.rt.left + (CHARACTER_WIDTH / 2) - 3, m_Data.rt.top);
	else if (MoveWay == DOWN)
		return new Missile(ReadMap, m_Data.Type, MoveWay, m_Data.rt.left + (CHARACTER_WIDTH / 2) -  3, m_Data.rt.bottom);
}

void  Character::DeathImage(int Number)
{
	if (Number == 0)
		m_Image = TEXT("BattleCity\\explosion_00.bmp");
	else if (Number == 1)
		m_Image = TEXT("BattleCity\\explosion_01.bmp");
	else if (Number == 2)
		m_Image = TEXT("BattleCity\\explosion_02.bmp");
	else if (Number == 3)
		m_Image = TEXT("BattleCity\\explosion_03.bmp");
	else if (Number == 4)
		m_Image = TEXT("BattleCity\\explosion_04.bmp");
}

//========================================================플레이어=====================================================================


void Player::InitData(int x, int y, int Type)
{
	BackPoint.x = 50 + x * BLOCK_WIDTH;
	BackPoint.y = 50 + y * BLOCK_HEIGHT;
	SetRect(BackPoint.x, BackPoint.y);m_Data.Type = Type;
	UseUnit = true;
	MoveSpeed = 80;
	m_Life = 6;
	DeathFlag = false;
	FrameCounter = 0;
	MissileCount = 0;
	MoveWay = UP;
	Back_Up_MoveWay = MoveWay;
	WayImage = UP_1;
	Shoot = true;
	SetDataPoint();
	ImageID();
}


bool Player::MoveCharacter()
{
	RECT tmp;
	int tmp_x;
	int tmp_y;
	int BackUp_Move = MoveWay;
	bool Check = false;

	if (GetKeyState(VK_LEFT) & 0x8000)
	{

		if (BackUp_Move != LEFT)
			ReleaseFrame();
		tmp_x = m_Data.pt.x - MoveSpeed * FrameCounter;
		tmp_y = m_Data.pt.y;
		tmp = { tmp_x , tmp_y, tmp_x + CHARACTER_WIDTH, tmp_y + CHARACTER_HEIGHT };
		if (ReadMap->CheckNotImpulse(tmp))
		{
			if (m_Data.pt.x - MoveSpeed * FrameCounter < 50)
				tmp_x = 50;
			else
				Check = true;
			SetRect(tmp_x, tmp_y);
			Back_Up_MoveWay = LEFT;
			MoveChange(true);
		}
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		if (BackUp_Move != RIGHT)
			ReleaseFrame();
		tmp_x = m_Data.pt.x + MoveSpeed * FrameCounter;
		tmp_y = m_Data.pt.y;
		tmp = { tmp_x , tmp_y, tmp_x + CHARACTER_WIDTH, tmp_y + CHARACTER_HEIGHT };
		if (ReadMap->CheckNotImpulse(tmp))
		{
			if (tmp_x + CHARACTER_WIDTH > 50 + BLOCK_WIDTH * 13)
				tmp_x = 50 + BLOCK_WIDTH * 13 - CHARACTER_WIDTH;
			else
				Check = true;
			SetRect(tmp_x, tmp_y);
			Back_Up_MoveWay = RIGHT;
			MoveChange(true);
		}
	}
	else if (GetKeyState(VK_UP) & 0x8000)
	{
		if (BackUp_Move != UP)
			ReleaseFrame();
		tmp_x = m_Data.pt.x;
		tmp_y = m_Data.pt.y - MoveSpeed * FrameCounter;
		tmp = { tmp_x , tmp_y, tmp_x + CHARACTER_WIDTH, tmp_y + CHARACTER_HEIGHT };
		if (ReadMap->CheckNotImpulse(tmp))
		{
			if (tmp_y < 50)
				tmp_y = 50;
			else
				Check = true;
			SetRect(tmp_x, tmp_y);
			Back_Up_MoveWay = UP;
			MoveChange(true);
		}
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		if (BackUp_Move != DOWN)
			ReleaseFrame();
		tmp_x = m_Data.pt.x;
		tmp_y = m_Data.pt.y + MoveSpeed * FrameCounter;
		tmp = { tmp_x , tmp_y, tmp_x + CHARACTER_WIDTH, tmp_y + CHARACTER_HEIGHT };
		if (ReadMap->CheckNotImpulse(tmp))
		{
			if (tmp_y + CHARACTER_HEIGHT > 50 + BLOCK_HEIGHT * 13)
				tmp_y = 50 + BLOCK_HEIGHT * 13 - CHARACTER_HEIGHT;
			else
				Check = true;
			SetRect(tmp_x, tmp_y);
			Back_Up_MoveWay = DOWN;
			MoveChange(true);
		}
	}
	return Check;
}

void Player::MoveChange(bool Change)
{
	if (Change)
	{
		MoveWay = Back_Up_MoveWay;
		SetWayImage(MoveWay);
	}
}

bool Player::DamageCheck(Missile* CheckMissile)
{
	RECT tmp;
	if (!DeathFlag)
	{
		if (IntersectRect(&tmp, &m_Data.rt, &(CheckMissile->GetMissileRect())))
		{
			m_Life--;
			DeathFlag = true;
			FrameCounter = 0;
			return true;
		}
	}
	return false;
}

void Player::SetFrame(double Delta)
{
	FrameCounter += Delta;
	if (FrameCounter > 1)
		FrameCounter = 1;
	if (FrameCounter == 1)
	{
		FrameCounter = 0;
		SetDataPoint();
	}


	if (!Shoot)
	{
		MissileCount += Delta;
		if (MissileCount > 0.6)
		{
			MissileCount = 0;
			Shoot = true;
		}
	}
}

void Player::DeathProcess()
{
	if(FrameCounter == 0)
	{
		DeathFlag = false;
		if (m_Life > 0)
		{
			SetRect(BackPoint.x, BackPoint.y);
			SetDataPoint();
			MoveWay = UP;
			SetWayImage(UP);
		}
		else
			UseUnit = false;
	}
	else if (FrameCounter < 0.20)
		DeathImage(0);
	else if (FrameCounter < 0.40)
		DeathImage(1);
	else if (FrameCounter < 0.60)
		DeathImage(2);
	else if (FrameCounter < 0.80)
		DeathImage(3);
	else if (FrameCounter < 1)
		DeathImage(4);
}

void Player::ImageID()
{
		if (WayImage == DOWN_1)
			m_Image = TEXT("BattleCity\\tank_down_00.bmp");
		else if (WayImage == DOWN_2)
			m_Image = TEXT("BattleCity\\tank_down_01.bmp");
		if (WayImage == LEFT_1)
			m_Image = TEXT("BattleCity\\tank_left_00.bmp");
		else if (WayImage == LEFT_2)
			m_Image = TEXT("BattleCity\\tank_left_01.bmp");
		if (WayImage == RIGHT_1)
			m_Image = TEXT("BattleCity\\tank_right_00.bmp");
		else if (WayImage == RIGHT_2)
			m_Image = TEXT("BattleCity\\tank_right_01.bmp");
		if (WayImage == UP_1)
			m_Image = TEXT("BattleCity\\tank_up_00.bmp");
		else if (WayImage == UP_2)
			m_Image = TEXT("BattleCity\\tank_up_01.bmp");
}

//========================================================적 캐릭터=====================================================================

void Enemy::InitData(int x, int y, int Type)
{
	int tmp_Life = rand() % 100 + 1;
	SetRect(50 + x * BLOCK_WIDTH, 50 + y * BLOCK_HEIGHT);
	m_Data.Type = Type;
	FrameCounter = 0;
	MissileCount = 0;
	DamageCounter = 0;
	MoveChangeCounter = 0;
	UseUnit = true;
	MoveFlag = true;
	Counterattack = false;
	NotImpulseFlag = false;
	DamageFlag = false;
	DeathFlag = false;
	Shoot = true;
	MoveWay = Movepossible(false);
	Pre_Distractor = Cur_Distractor;
	SetWayImage(MoveWay);
	SetDataPoint();
	ImageID();

	if (tmp_Life <= 80)
	{
		ShootCounter = 2.5;
		m_Life = 2;
		MoveSpeed = 70;
	}
	else
	{
		ShootCounter = 1.8;
		m_Life = 3;
		MoveSpeed = 100;
	}
}


bool Enemy::MoveCharacter()
{
	bool Check = false;

	RECT tmp;
	int tmp_x;
	int tmp_y;
	int ChangeMove;

	if (!DamageFlag)
	{
		if (MoveFlag || NotImpulseFlag)
			MoveChange(true);

		if (MoveWay == LEFT)
		{
			SetWayImage(LEFT);
			tmp_x = m_Data.pt.x - MoveSpeed * FrameCounter;
			tmp_y = m_Data.pt.y;
			tmp = { tmp_x , tmp_y, tmp_x + CHARACTER_WIDTH, tmp_y + CHARACTER_HEIGHT };
			NotImpulseFlag = ReadMap->CheckNotImpulse(tmp);
			if (NotImpulseFlag)
			{
				if (m_Data.pt.x - MoveSpeed * FrameCounter < 50)
					tmp_x = 50;
				else 
				{
					SetRect(tmp_x, tmp_y);
					Check = true;
				}	
			}
		}
		else if (MoveWay == RIGHT)
		{
			SetWayImage(RIGHT);
			tmp_x = m_Data.pt.x + MoveSpeed * FrameCounter;
			tmp_y = m_Data.pt.y;
			tmp = { tmp_x , tmp_y, tmp_x + CHARACTER_WIDTH, tmp_y + CHARACTER_HEIGHT };
			NotImpulseFlag = ReadMap->CheckNotImpulse(tmp);
			if (NotImpulseFlag)
			{
				if (tmp_x + CHARACTER_WIDTH > 50 + BLOCK_WIDTH * 13)
					tmp_x = 50 + BLOCK_WIDTH * 13 - CHARACTER_WIDTH;
				else
				{
					SetRect(tmp_x, tmp_y);
					Check = true;
				}
			}
		}
		else if (MoveWay == UP)
		{
			SetWayImage(UP);
			tmp_x = m_Data.pt.x;
			tmp_y = m_Data.pt.y - MoveSpeed * FrameCounter;
			tmp = { tmp_x , tmp_y, tmp_x + CHARACTER_WIDTH, tmp_y + CHARACTER_HEIGHT };
			NotImpulseFlag = ReadMap->CheckNotImpulse(tmp);
			if (NotImpulseFlag)
			{
				if (tmp_y < 50)
					tmp_y = 50;
				else
				{
					SetRect(tmp_x, tmp_y);
					Check = true;
				}
			}
		}
		else if (MoveWay == DOWN)
		{
			SetWayImage(DOWN);
			tmp_x = m_Data.pt.x;
			tmp_y = m_Data.pt.y + MoveSpeed * FrameCounter;
			tmp = { tmp_x , tmp_y, tmp_x + CHARACTER_WIDTH, tmp_y + CHARACTER_HEIGHT };
			NotImpulseFlag = ReadMap->CheckNotImpulse(tmp);
			if (NotImpulseFlag)
			{
				if (tmp_y + CHARACTER_HEIGHT > 50 + BLOCK_HEIGHT * 13)
					tmp_y = 50 + BLOCK_HEIGHT * 13 - CHARACTER_HEIGHT;
				else
				{
					SetRect(tmp_x, tmp_y);
					Check = true;
				}
			}
		}
		MoveFlag = Check;
		if (Counterattack)
			Counterattack = false;
	}
	else
	{
		Check = true;
		ImageID();
		if (DamageCounter == 1)
		{
			DamageCounter = 0;
			FrameCounter = 0;
			DamageFlag = false;
			Counterattack = true;
			MoveWay = Hit_Direction;
		}
	}
	return Check;
}

void Enemy::MoveChange(bool Change)
{
	int ChangeMove;
	int ChangeFlag = Change;
	POINT pt = ReadMap->GetCommandPoint();
	int Key = ReadMap->GetCommandKey();

	if (!Counterattack)
	{
		if (MoveWay == LEFT)
		{
			int x = 50 + pt.x * BLOCK_WIDTH + BLOCK_WIDTH;
			int y = 50 + pt.y * BLOCK_HEIGHT;
			int tmp = m_Data.rt.top + (CHARACTER_HEIGHT / 2);
			if (x < m_Data.rt.left && y <= tmp && y + BLOCK_WIDTH >= tmp)
			{
				if (ReadMap->GetProtectBlock(Key + 1) == NOT_BLOCK)
					ChangeFlag = false;
			}
		}
		else if (MoveWay == RIGHT)
		{
			int x = 50 + pt.x * BLOCK_WIDTH;
			int y = 50 + pt.y * BLOCK_HEIGHT;
			int tmp = m_Data.rt.top + (CHARACTER_HEIGHT / 2);
			if (x > m_Data.rt.right && y <= tmp && y + BLOCK_WIDTH >= tmp)
			{
				if (ReadMap->GetProtectBlock(Key - 1) == NOT_BLOCK)
					ChangeFlag = false;
			}
		}
		else if (MoveWay == DOWN)
		{
			bool Check = true;
			int x = 50 + pt.x * BLOCK_WIDTH;
			int y = 50 + pt.y * BLOCK_HEIGHT;
			int tmp = m_Data.rt.left + (CHARACTER_WIDTH / 2);
			if ((x <= tmp && x + BLOCK_WIDTH >= tmp) && y > m_Data.rt.bottom)
			{
				while (1)
				{
					Key -= 13;
					if (Key < 0)
						break;
					else if (ReadMap->GetProtectBlock(Key) != NOT_BLOCK)
						Check = false;

					if (!Check)
					{
						ChangeFlag = false;
						break;
					}
				}

			}
		}
		if (ChangeFlag)
		{
			if (!MoveFlag)
			{
				if (!NotImpulseFlag)
					ChangeMove = Movepossible(false);
				else
					ChangeMove = Movepossible(true);
				if (ChangeMove != MoveWay)
					ReleaseFrame();
				MoveWay = ChangeMove;
				MoveFlag = true;
			}
			else
			{
				ChangeMove = Movepossible(true);
				if (Pre_Distractor < Cur_Distractor)
				{
					if (ChangeMove != MoveWay)
						ReleaseFrame();
					MoveWay = ChangeMove;
					MoveFlag = true;
				}
				else if(MoveChangeCounter > 2)
				{
					if (ChangeMove != MoveWay)
						ReleaseFrame();
					MoveWay = ChangeMove;
					MoveFlag = true;
				}
			}
			MoveChangeCounter = 0;
		}
	}
}

int Enemy::Movepossible(bool  NotImpulse)
{
	int Change;
	int MoveKey = 0;
	bool CreateList;
	map<int, int> MoveList;
	POINT pt;
	pt = ReadMap->GetCommandPoint();

	if (ReadMap->CheckNotImpulse(MakeRect(m_Data.rt.left - CHARACTER_WIDTH / 2, m_Data.rt.top)))
	{
		CreateList = false;
		if (m_Data.rt.left - CHARACTER_WIDTH / 2 > 50)
		{
			if (!NotImpulse)
				CreateList = true;
			else if (pt.x*BLOCK_WIDTH + 50 + BLOCK_WIDTH < m_Data.rt.left)
				CreateList = true;		
		}
		if (CreateList)
		{
			MoveList.insert(pair<int, int>(MoveKey, LEFT));
			MoveKey++;
		}
	}
	else
	{
		if(CheckImpluseCommand(pt, LEFT))
		{
			MoveList.insert(pair<int, int>(MoveKey, LEFT));
			MoveKey++;
		}
	}

	if (ReadMap->CheckNotImpulse(MakeRect(m_Data.rt.left + CHARACTER_WIDTH / 2, m_Data.rt.top)))
	{
		CreateList = false;
		if (m_Data.rt.left + CHARACTER_WIDTH / 2 < 50 + BLOCK_WIDTH *13)
		{
			if (!NotImpulse)
				CreateList = true;
			else if (pt.x*BLOCK_WIDTH + 50 > m_Data.rt.right)
				CreateList = true;
		}
		if (CreateList)
		{
			MoveList.insert(pair<int, int>(MoveKey, RIGHT));
			MoveKey++;
		}
	}
	else
	{
		if (CheckImpluseCommand(pt, RIGHT))
		{
			MoveList.insert(pair<int, int>(MoveKey, RIGHT));
			MoveKey++;
		}
	}

	if (ReadMap->CheckNotImpulse(MakeRect(m_Data.rt.left, m_Data.rt.top + CHARACTER_HEIGHT / 2)))
	{
		CreateList = false;
		if (m_Data.rt.bottom + CHARACTER_HEIGHT / 2 < 50 + BLOCK_HEIGHT * 13)
		{
			if (!NotImpulse)
				CreateList = true;
			else if (pt.y * BLOCK_HEIGHT + 50 > m_Data.rt.top)
				CreateList = true;
		}
		if (CreateList)
		{
			MoveList.insert(pair<int, int>(MoveKey, DOWN));
			MoveKey++;
		}
	}
	else
	{
		if (CheckImpluseCommand(pt, DOWN))
		{
			MoveList.insert(pair<int, int>(MoveKey, DOWN));
			MoveKey++;
		}
	}

	if (ReadMap->CheckNotImpulse(MakeRect(m_Data.rt.left, m_Data.rt.top - CHARACTER_HEIGHT / 2)))
	{
		CreateList = false;
		if (m_Data.rt.top - CHARACTER_HEIGHT / 2  > 50)
		{
			CreateList = false;
			if (!NotImpulse)
				CreateList = true;
			if (CreateList)
			{
				MoveList.insert(pair<int, int>(MoveKey, UP));
				MoveKey++;
			}
		}
	}
	if (MoveList.size() != 0)
	{
		Pre_Distractor = Cur_Distractor;
		Cur_Distractor = MoveList.size();
		Change = rand() % Cur_Distractor;
		return MoveList.find(Change)->second;
	}
	else
		return Movepossible(false);
}

bool Enemy::CheckImpluseCommand(POINT pt, int Move)
{
	if (Move == DOWN)
	{
		if (m_Data.rt.bottom + FrameCounter >= 50 + pt.y*BLOCK_HEIGHT && m_Data.rt.bottom + FrameCounter <= 50 + (pt.y*BLOCK_HEIGHT) + BLOCK_HEIGHT)
		{
			if (m_Data.rt.left + CHARACTER_WIDTH / 2 >= 50 + pt.x*BLOCK_WIDTH && m_Data.rt.left + CHARACTER_WIDTH / 2 <= 50 + (pt.x * BLOCK_WIDTH) + BLOCK_WIDTH)
				return true;
		}
	}
	else if (Move == LEFT)
	{
		if (m_Data.rt.left - FrameCounter >= 50 + pt.x*BLOCK_WIDTH && m_Data.rt.left - FrameCounter <= 50 + (pt.x * BLOCK_WIDTH) + BLOCK_WIDTH)
		{
			if (m_Data.rt.top + CHARACTER_HEIGHT / 2 >= 50 + pt.y*BLOCK_HEIGHT && m_Data.rt.top + CHARACTER_HEIGHT / 2 <= 50 + (pt.y*BLOCK_HEIGHT) + BLOCK_HEIGHT)
				return true;
		}
	}
	else if (Move == RIGHT)
	{
		if (m_Data.rt.left + CHARACTER_WIDTH + FrameCounter >= 50 + pt.x*BLOCK_WIDTH && m_Data.rt.left + CHARACTER_WIDTH + FrameCounter <= 50 + (pt.x * BLOCK_WIDTH) + BLOCK_WIDTH)
		{
			if (m_Data.rt.top + CHARACTER_HEIGHT / 2 >= 50 + pt.y*BLOCK_HEIGHT && m_Data.rt.top + CHARACTER_HEIGHT / 2 <= 50 + (pt.y*BLOCK_HEIGHT) + BLOCK_HEIGHT)
				return true;
		}
	}

	return false;
}

RECT Enemy::MakeRect(int x, int y)
{
	RECT tmp;
	tmp = { x, y, x + CHARACTER_WIDTH, y + CHARACTER_HEIGHT };

	return tmp;
}


bool Enemy::DamageCheck(Missile* CheckMissile)
{
	RECT tmp;
	if (!DeathFlag)
	{
		if (IntersectRect(&tmp, &m_Data.rt, &(CheckMissile->GetMissileRect())))
		{
			if (!DamageFlag)
			{
				m_Life--;
				if (m_Life > 0)
				{
					if (CheckMissile->GetMoveWay() == LEFT)
						Hit_Direction = RIGHT;
					else if (CheckMissile->GetMoveWay() == RIGHT)
						Hit_Direction = LEFT;
					else if (CheckMissile->GetMoveWay() == UP)
						Hit_Direction = DOWN;
					else if (CheckMissile->GetMoveWay() == DOWN)
						Hit_Direction = UP;
					DamageFlag = true;
				}
				else
				{
					DeathFlag = true;
					FrameCounter = 0;
				}
			}
			return true;
		}
	}
	return false;
}

void Enemy::DeathProcess()
{
	if (FrameCounter == 0)
		UseUnit = false;
	else if ( FrameCounter < 0.20)
		DeathImage(0);
	else if (FrameCounter < 0.40)
		DeathImage(1);
	else if (FrameCounter < 0.60)
		DeathImage(2);
	else if (FrameCounter < 0.80)
		DeathImage(3);
	else if (FrameCounter < 1)
		DeathImage(4);
}

void Enemy::SetFrame(double Delta)
{	
	FrameCounter += Delta;
	if (FrameCounter > 1)
		FrameCounter = 1;
	if (FrameCounter == 1)
		ReleaseFrame();
	MoveChangeCounter += Delta;

	if (!Shoot)
	{
		if (!DamageFlag)
		{
			MissileCount += Delta;
			if (MissileCount > ShootCounter)
			{
				MissileCount = 0;
				Shoot = true;
			}
		}
	}
	if (DamageFlag)
	{
		DamageCounter += Delta;
		if (DamageCounter > 1)
			DamageCounter = 1;
	}
}

void Enemy::ImageID()
{
	if (!DamageFlag)
	{
		if (WayImage == DOWN_1)
			m_Image = TEXT("BattleCity\\e_down_00.bmp");
		else if (WayImage == DOWN_2)
			m_Image = TEXT("BattleCity\\e_down_01.bmp");
		else if (WayImage == LEFT_1)
			m_Image = TEXT("BattleCity\\e_left_00.bmp");
		else if (WayImage == LEFT_2)
			m_Image = TEXT("BattleCity\\e_left_01.bmp");
		else if (WayImage == RIGHT_1)
			m_Image = TEXT("BattleCity\\e_right_00.bmp");
		else if (WayImage == RIGHT_2)
			m_Image = TEXT("BattleCity\\e_right_01.bmp");
		else if (WayImage == UP_1)
			m_Image = TEXT("BattleCity\\e_up_00.bmp");
		else if (WayImage == UP_2)
			m_Image = TEXT("BattleCity\\e_up_01.bmp");
	}
	else
	{
		if(MoveWay == DOWN)
			m_Image = TEXT("BattleCity\\e_down_02.bmp");
		else if (MoveWay == LEFT)
			m_Image = TEXT("BattleCity\\e_left_02.bmp");
		else if (MoveWay == RIGHT)
			m_Image = TEXT("BattleCity\\e_right_02.bmp");
		else if (MoveWay == UP)
			m_Image = TEXT("BattleCity\\e_UP_02.bmp");
	}
}