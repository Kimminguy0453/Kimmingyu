#include "BattleCity.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("BattleCity");
char ProjectPath[MAX_PATH];
bool GameFlag = false;
int g_map[13][13];
bool t = true;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	BattleCity::GetGame()->Default(hWnd);
	BattleCity::GetGame()->SetTitleButton(hWnd, g_hInst);
	BattleCity::GetGame()->DrawGame(hWnd);
	BattleCity::GetGame()->SetProjectPath();
	while (1)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
			if (Message.message == WM_QUIT)
				break;
		}
		else
		{
			if (BattleCity::GetGame()->GetGameFlag())
			{
				BattleCity::GetGame()->Game_UpDate(hWnd);
				if(!BattleCity::GetGame()->GetGameFlag())
					BattleCity::GetGame()->SetTitleButton(hWnd, g_hInst);
			}
		}
	}
	return (int)Message.wParam;
}

void TitleProcess(HWND hWnd, int Select);
void CustomProcess(HWND hWnd, int Select);
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int Counter;
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_COMMAND:
		if (!BattleCity::GetGame()->GetGameFlag())
		{
			if (BattleCity::GetGame()->GetCustom())
				CustomProcess(hWnd, LOWORD(wParam));
			else
				TitleProcess(hWnd, LOWORD(wParam));
		}
		return 0;
	case WM_LBUTTONDOWN:
		POINT pt;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		if (BattleCity::GetGame()->GetCustom())
		{
			BattleCity::GetGame()->ChangeBlock(pt);
			BattleCity::GetGame()->DrawGame(hWnd);
		}
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void TitleProcess(HWND hWnd, int Select)
{
	if (Select == 50)
	{
		BattleCity::GetGame()->SelectStage();
		BattleCity::GetGame()->EndTitle();
	}
	else if (Select == 51)
	{
		BattleCity::GetGame()->SetOpenFile(hWnd, 101);
		if(BattleCity::GetGame()->GetGameFlag())
			BattleCity::GetGame()->EndTitle();
	}
	else if (Select == 52)
	{
		BattleCity::GetGame()->EndTitle();
		BattleCity::GetGame()->CustomStart(hWnd, g_hInst);
		BattleCity::GetGame()->DrawGame(hWnd);
	}
	else if (Select == 53)
	{
		BattleCity::GetGame()->ExitGame();
		PostQuitMessage(0);
		return;
	}
}

void CustomProcess(HWND hWnd, int Select)
{
	if (Select >= 0 && Select < 14 || Select >= 16 && Select <= 18)
		BattleCity::GetGame()->InitCursor(Select);
	else if (Select == 100 || Select == 101)
		BattleCity::GetGame()->SetOpenFile(hWnd, Select);
	else if (Select == 102)
	{
		BattleCity::GetGame()->CustomEnd();
		BattleCity::GetGame()->ReleaseMap();
		BattleCity::GetGame()->SetTitleButton(hWnd, g_hInst);
	}
	BattleCity::GetGame()->DrawGame(hWnd);
}
