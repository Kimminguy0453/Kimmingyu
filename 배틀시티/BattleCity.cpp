#include "BattleCity.h"

BattleCity* BattleCity::m_hThis = NULL;
void BattleCity::Default(HWND hWnd)
{
	srand(time(NULL));
 	m_Map = new GameMap;
	m_Player = new Player;
	ReleaseMap();
	DefaultFlag();
	m_Player->InitMap(m_Map);//맵의 정보가 변하면 플레이어는 상시 그 변화를 가지고 있다.
	CurType = 0;
	QueryPerformanceFrequency(&Frequency);
	m_Move = STOP;
}

void BattleCity::DefaultFlag()
{
	m_Flag.CustomFlag = false;
	m_Flag.PlayCustom = false;
	m_Flag.PlayFlag = false;
	m_Flag.UseFrameCount = false;
}

void BattleCity::SetProjectPath()
{
	char str[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, str);
	wsprintf(ProjectPath, "%s\\Map", str);
}

//==================================================================================================================
//타이틀 관련
void BattleCity::SetTitleButton(HWND hWnd, HINSTANCE g_hInst)
{
	m_iStage = 1;
	CurType = 0;
	TitleButtom[0] = CreateWindow("button", "새게임", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 325, 250, 100, 30, hWnd, (HMENU)50, g_hInst, NULL);
	TitleButtom[1] = CreateWindow("button", "불러오기", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 325, 300, 100, 30, hWnd, (HMENU)51, g_hInst, NULL);
	TitleButtom[2] = CreateWindow("button", "커스텀 모드", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 325, 350, 100, 30, hWnd, (HMENU)52, g_hInst, NULL);
	TitleButtom[3] = CreateWindow("button", "게임 종료", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 325, 400, 100, 30, hWnd, (HMENU)53, g_hInst, NULL);
}

void BattleCity::EndTitle()
{
	for (int i = 0; i < 4; i++)
		DestroyWindow(TitleButtom[i]);
}
//==================================================================================================================

//==================================================================================================================
//맵초기화
void BattleCity::ReleaseMap()
{
	memset(g_map, 0, sizeof(int) * 13 * 13);
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
			m_Map->InitBloclk(j, i, NOT_BLOCK);
	}
	respawn.clear();
	AllClearEnemy();
	AllClearMissile();
}
//==================================================================================================================

//==================================================================================================================
//유닛 및 미사일 삭제
void BattleCity::AllClearMissile()
{
	for (auto iter = m_MissileList.begin(); iter != m_MissileList.end(); iter++)
	{
		delete (*iter);
		(*iter) = NULL;
	}
	m_MissileList.clear();
}

void BattleCity::AllClearEnemy()
{
	for (auto iter = m_EnemyList.begin(); iter != m_EnemyList.end(); iter++)
	{
		delete (*iter);
		(*iter) = NULL;
	}
	m_EnemyList.clear();
}

void BattleCity::ExitGame()
{
	delete m_Player;
	m_Player = NULL;
	delete m_Map;
	m_Map = NULL;
	GameImage::GetImageMaker()->DeleteMaker();
	respawn.clear();
	AllClearMissile();
}
//==================================================================================================================

//==================================================================================================================
//게임동작

void BattleCity::MakeEnemy()
{
	if (Total_Enemy >= 4)
	{
		int Count = rand() % respawn.size();
		m_EnemyList.push_back(new Enemy);
		m_EnemyList.back()->InitMap(m_Map);
		m_EnemyList.back()->InitData(respawn.find(Count)->second.x, respawn.find(Count)->second.y, ENEMY);
	}
}

void BattleCity::Game_UpDate(HWND hWnd)
{
	QueryPerformanceCounter(&End);
	if (m_Flag.UseFrameCount)
	{
		Field_Enemy = m_EnemyList.size();
		Delta = (double)(End.QuadPart - Start.QuadPart) / (double)(Frequency.QuadPart);
		MakeEnemyCounter += Delta;
		if (MakeEnemyCounter >= 2)
		{
			if (Field_Enemy < 4 && Total_Enemy > 0)
				MakeEnemy();
			MakeEnemyCounter = 0;
		}
		PlayerMove();
		EnemyMove();
		MissileMove();
		DamageCheck();
		ReleaseMissile();
		ReleaseEnemy();
	}
	else
		m_Flag.UseFrameCount = true;
	QueryPerformanceCounter(&Start);

	DrawGame(hWnd);
	if (Total_Enemy == 0)
	{
		if(m_iStage <= 4)
			QuestionNextStage(hWnd);
		else
			GameEnd(hWnd, false);
	}
	if (!m_Player->GetUseUnit() || m_Map->GetCommandCenter() == DEFEAT)
		GameEnd(hWnd, true);
}

void BattleCity::QuestionNextStage(HWND hWnd)
{
	if (MessageBox(hWnd, TEXT("GO Next Game?"), TEXT("Stage Clear!"), MB_YESNO) == IDYES)
	{
		if (!m_Flag.PlayCustom)
		{
			m_iStage++;
			SelectStage();
			DrawGame(hWnd);
		}
		else
		{
			SetOpenFile(hWnd, LOAD);
			DrawGame(hWnd);
		}
	}
	else
	{
		m_Flag.PlayFlag = false;
		m_Flag.PlayCustom = false;
		ReleaseMap();
		DrawGame(hWnd);
	}
}

void BattleCity::GameEnd(HWND hWnd, bool Over)
{
	bool End = true;
	if (Over)
	{
		if (MessageBox(hWnd, TEXT("New Game"), TEXT("GAME OVER"), MB_YESNO) == IDYES)
			End = false;
	}
	else
	{
		if (MessageBox(hWnd, TEXT("New Game"), TEXT("GAME CLEAR"), MB_YESNO) == IDYES)
			End = false;
	}
	if (!End)
	{
		if (!m_Flag.PlayCustom)
		{
			m_iStage = 1;
			SelectStage();
			DrawGame(hWnd);
		}
		else
		{
			LoadMap(curFile);
			DrawGame(hWnd);
		}
	}
	else
	{
		m_Flag.PlayFlag = false;
		m_Flag.PlayCustom = false;
		ReleaseMap();
		DrawGame(hWnd);
	}
}

void BattleCity::PlayerMove()
{
	bool DeathCheck = m_Player->GetDeath();

	m_Player->SetFrame(Delta);
	if(m_Player->GetDeath())
		m_Player->DeathProcess();
	else 
	{
		if(!m_Player->MoveCharacter())
			m_Player->ReleaseFrame();
		if (GetKeyState(VK_SPACE) & 0x8000)
		{
			if (m_Player->UseShoot())
				m_MissileList.push_back(m_Player->MakeMissile());
		}
	}
}

void BattleCity::EnemyMove()
{
	int RandomMissile; 

	for (auto iter = m_EnemyList.begin(); iter != m_EnemyList.end(); iter++)
	{
		bool UseMissile = (*iter)->UseShoot();
		int RandomShoot = rand() % 100 + 1;
		(*iter)->SetFrame(Delta);
		if (!(*iter)->GetDeath())
		{
			if (!(*iter)->MoveCharacter())
			{
				if (UseMissile)
					(*iter)->MoveChange(false);
				else
					(*iter)->MoveChange(true);
			}
			else
				(*iter)->MoveChange(true);
			if (RandomShoot < (*iter)->GetMoveSpeed() / 5)
			{
				if (UseMissile)
					m_MissileList.push_back((*iter)->MakeMissile());
			}
		}
		else
			(*iter)->DeathProcess();
	}
}

void BattleCity::MissileMove()
{
	if (m_MissileList.size() != 0)
	{
		for (auto iter = m_MissileList.begin(); iter != m_MissileList.end(); iter++)
		{
			(*iter)->SetFrameCounter(Delta);
			(*iter)->MoveMissile();
		}
	}
}

void BattleCity::ReleaseEnemy()
{
	bool NotDelete;
	while (1)
	{
		NotDelete = true;
		for (auto iter = m_EnemyList.begin(); iter != m_EnemyList.end(); iter++)
		{
			if (!(*iter)->GetUseUnit() && (*iter)->GetDeath())
			{
				iter = m_EnemyList.erase(iter);
				NotDelete = false;
				break;
			}
		}
		if (NotDelete)
			return;
		else
			Total_Enemy--;
	}
}


void BattleCity::ReleaseMissile()
{
	bool NotDelete;
	while (1)
	{
		NotDelete = true;
		for (auto iter = m_MissileList.begin(); iter != m_MissileList.end(); iter++)
		{
			if (!(*iter)->GetStand())
			{
				iter = m_MissileList.erase(iter);
				NotDelete = false;
				break;
			}
		}
		if (NotDelete)
			return;
	}
}

void BattleCity::DamageCheck()
{
	for (auto iter = m_MissileList.begin(); iter != m_MissileList.end(); iter++)
	{
		if ((*iter)->GetStartUnit() == ENEMY)
		{
			if (m_Player->DamageCheck(*iter))
				(*iter)->ReleaseStand();
		}
		else if ((*iter)->GetStartUnit() == PLAYER)
		{
			for (auto iter2 = m_EnemyList.begin(); iter2 != m_EnemyList.end(); iter2++)
			{
				if ((*iter2)->DamageCheck(*iter))
				{
					(*iter)->ReleaseStand();
					break;
				}
			}
		}
	}
}

void BattleCity::DrawGame(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	GameImage::GetImageMaker()->SetBlock(hdc);
	if (m_Flag.CustomFlag)
	{
		GameImage::GetImageMaker()->SetScreen(true);
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				if (g_map[i][j] == PLAYER)
					GameImage::GetImageMaker()->DrawUnit(TEXT("BattleCity\\tank_up_00.bmp"), 50 + j * BLOCK_WIDTH, 50 + i * BLOCK_HEIGHT);
				else if (g_map[i][j] == ENEMY)
					GameImage::GetImageMaker()->DrawUnit(TEXT("BattleCity\\e_down_00.bmp"), 50 + j * BLOCK_WIDTH, 50 + i * BLOCK_HEIGHT);
				else if (g_map[i][j] != 0)
					GameImage::GetImageMaker()->DrawBlock(g_map[i][j], j, i);
			}
		}
	}
	else
	{
		GameImage::GetImageMaker()->SetScreen(false);
		if (m_Flag.PlayFlag)
		{
			m_Map->DrawMap();
			if (m_Player->GetUseUnit())
				m_Player->DrawCharacter();
			for (auto iter = m_EnemyList.begin(); iter != m_EnemyList.end(); iter++)
				(*iter)->DrawCharacter();
			for (auto iter = m_MissileList.begin(); iter != m_MissileList.end(); iter++)
			{
				if ((*iter)->GetStand())
					(*iter)->DrawMissile();
			}
			GameImage::GetImageMaker()->DrawGameIcon(ICON_X, PLAYER_ICON_Y, PLAYER_ICON, m_Player->GetLife());
			GameImage::GetImageMaker()->DrawGameIcon(ICON_X, STAGE_ICON_Y, STAGE_ICON, m_iStage);
			GameImage::GetImageMaker()->DrawGameIcon(ICON_X, ENEMY_ICON_Y, ENEMY_ICON, Total_Enemy);
		}
		m_Map->DrawThicket();
	}
	GameImage::GetImageMaker()->DrawScreen(hdc);
	GameImage::GetImageMaker()->ReleaseMap();
	ReleaseDC(hWnd, hdc);
}


//==================================================================================================================


//==================================================================================================================
//커스텀모드
void BattleCity::CustomStart(HWND hWnd, HINSTANCE g_hInst)
{
	m_Flag.CustomFlag = true;
	m_Map->CheckUseMap(true);
	CustomButtom[0] = CreateWindow("button", "1. 빈공간", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 1010, 50, 100, 30, hWnd, (HMENU)0, g_hInst, NULL);
	CustomButtom[1] = CreateWindow("button", "2. 벽돌", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 1010, 90, 100, 30, hWnd, (HMENU)1, g_hInst, NULL);
	CustomButtom[2] = CreateWindow("button", "3. 위벽돌", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 1010, 130, 100, 30, hWnd, (HMENU)2, g_hInst, NULL);
	CustomButtom[3] = CreateWindow("button", "4. 좌벽돌", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 1010, 170, 100, 30, hWnd, (HMENU)3, g_hInst, NULL);
	CustomButtom[4] = CreateWindow("button", "5. 아래벽돌", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 1010, 210, 100, 30, hWnd, (HMENU)4, g_hInst, NULL);
	CustomButtom[5] = CreateWindow("button", "6. 우벽돌", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 1010, 250, 100, 30, hWnd, (HMENU)5, g_hInst, NULL);
	CustomButtom[6] = CreateWindow("button", "7. 얼음", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 1010, 290, 100, 30, hWnd, (HMENU)6, g_hInst, NULL);
	CustomButtom[7] = CreateWindow("button", "8. 수풀", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 1010, 330, 100, 30, hWnd, (HMENU)7, g_hInst, NULL);
	CustomButtom[8] = CreateWindow("button", "9. 물", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 1010, 370, 100, 30, hWnd, (HMENU)8, g_hInst, NULL);
	CustomButtom[9] = CreateWindow("button", "10. 철벽", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 1010, 410, 100, 30, hWnd, (HMENU)9, g_hInst, NULL);
	CustomButtom[10] = CreateWindow("button", "11. 위철벽", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 1010, 450, 100, 30, hWnd, (HMENU)10, g_hInst, NULL);
	CustomButtom[11] = CreateWindow("button", "12. 좌철벽", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 1010, 490, 100, 30, hWnd, (HMENU)11, g_hInst, NULL);
	CustomButtom[12] = CreateWindow("button", "13. 아래철벽", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 1010, 530, 100, 30, hWnd, (HMENU)12, g_hInst, NULL);
	CustomButtom[13] = CreateWindow("button", "14. 우철벽", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 1010, 570, 100, 30, hWnd, (HMENU)13, g_hInst, NULL);
	CustomButtom[14] = CreateWindow("button", "Player", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 1130, 50, 100, 30, hWnd, (HMENU)16, g_hInst, NULL);
	CustomButtom[15] = CreateWindow("button", "Enemy", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 1130, 90, 100, 30, hWnd, (HMENU)17, g_hInst, NULL);
	CustomButtom[16] = CreateWindow("button", "Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1250, 50, 100, 30, hWnd, (HMENU)100, g_hInst, NULL);
	CustomButtom[17] = CreateWindow("button", "Load", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1250, 90, 100, 30, hWnd, (HMENU)101, g_hInst, NULL);
	CustomButtom[18] = CreateWindow("button", "EXIT", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1250, 130, 100, 30, hWnd, (HMENU)102, g_hInst, NULL);
	SelectStage(true);
}

void BattleCity::CustomEnd()
{
	for (int i = 0; i < 20; i++)
		DestroyWindow(CustomButtom[i]);
	m_Flag.CustomFlag = false;

}

void BattleCity::InitCursor(int Type)
{
	CurType = Type;
}

void BattleCity::ChangeBlock(POINT pt)
{
	int x = (pt.x - 50) / BLOCK_WIDTH;
	int y = (pt.y - 50) / BLOCK_HEIGHT;
	if ((pt.x < BLOCK_WIDTH * 13 + 50 && pt.x > 50) && (pt.y < BLOCK_HEIGHT * 13 + 50 && pt.y > 50))
	{
		if(g_map[y][x] != COMMAND_CENTER)
			g_map[y][x] = CurType;
		if(CurType == PLAYER)
			CheckRepetition(x, y);
	}
}

void BattleCity::CheckRepetition(int x, int y)
{
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			if (g_map[i][j] == CurType &&  (i != y || j != x))
				g_map[i][j] = NOT_BLOCK;
		}
	}
}


void BattleCity::DeleteEnemy(int x, int y)
{
	POINT pt;
	for (auto iter = m_EnemyList.begin(); iter != m_EnemyList.end(); iter++)
	{
		pt = (*iter)->GetPoint();
		if(pt.x == 50 + x * BLOCK_WIDTH && pt.y == 50 + y * BLOCK_HEIGHT)
		{
			iter = m_EnemyList.erase(iter);
			return;
		}
	}
}
//==================================================================================================================

//==================================================================================================================
//스테이지 불러오기에 사용.
void BattleCity::SelectStage(bool CustomStart)
{
	char File[MAX_PATH] = "";

	if(CustomStart)
		wsprintf(File, "%s\\DefaultMap", ProjectPath);
	else
		wsprintf(File, "%s\\Stage%d", ProjectPath, m_iStage);
	
	LoadMap(File);
}

//==================================================================================================================

//==================================================================================================================
//파일입출력
void BattleCity::SetOpenFile(HWND hWnd, int Type)
{
	OPENFILENAME OFN;
	char lpstrFile[MAX_PATH] = "";
	char lpstrPath[MAX_PATH] = "";
	char str[MAX_PATH] = "";

	memset(&OFN, 0, sizeof(OPENFILENAME));//
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = hWnd;
	OFN.lpstrFilter = "File\0*.*\0Text File\0*.txt;*.doc\0";
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 256;

	OFN.lpstrInitialDir = ProjectPath;

	if (Type == 100)
		SaveMap(OFN);
	else
	{
		if(!m_Flag.CustomFlag)
			m_Flag.PlayCustom = true;
		if (GetOpenFileName(&OFN) != 0)
		{
			wsprintf(curFile, "%s", OFN.lpstrFile);
			LoadMap(OFN.lpstrFile);
		}
	}
}

void BattleCity::SaveMap(OPENFILENAME &OFN)
{
	if (GetSaveFileName(&OFN) != 0)
	{
		HANDLE hFile = CreateFile(OFN.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				DWORD writeB;
				WriteFile(hFile, &g_map[i][j], sizeof(int), &writeB, NULL);
			}
		}
		CloseHandle(hFile);
	}
}

void BattleCity::LoadMap(LPSTR hFileName)
{
	int Count = 0;
	ReleaseMap();
	HANDLE hFile = CreateFile(hFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			DWORD readB;
			POINT pt;
			pt.x = j;
			pt.y = i;
			ReadFile(hFile, &g_map[i][j], sizeof(int), &readB, NULL);
			if (!m_Flag.CustomFlag)
			{
				if (g_map[i][j] == PLAYER)
					m_Player->InitData(j, i, g_map[i][j]);
				else if (g_map[i][j] == ENEMY)
					respawn.insert(pair<int, POINT>(Count++, pt));
				else
					m_Map->InitBloclk(j, i, g_map[i][j]);
			}
		}
	}
	CloseHandle(hFile);
	if (!m_Flag.CustomFlag)
	{
		MakeEnemyCounter = 1.5;
		Total_Enemy = 18;
		m_Map->CheckUseMap(true);
		m_Flag.PlayFlag = true;
	}
}
//==================================================================================================================
