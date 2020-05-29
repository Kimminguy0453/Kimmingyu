#include<Windows.h>
#include <iomanip>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;//글로벌 인스턴스핸들값
LPCTSTR lpszClass = TEXT("HelloWorld"); 

struct Circle 
{
	int x; 
	int y;
	int Radius;
};

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
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
		(HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	while (GetMessage(&Message, NULL, 0, 0)) 
	{
		TranslateMessage(&Message); 
		DispatchMessage(&Message); 
	}
	return (int)Message.wParam;
}

void DrawCircle(HDC hdc,int Radius1, int Radius2 = NULL)
{
	Circle c;
	for (int i = 0; i < 360; i++)
	{
		c.y = sin(i) * Radius1;
		if(Radius2 == NULL)
			c.x = cos(i) * Radius1;
		else
			c.x = cos(i) * Radius2;
		SetPixel(hdc, 100 + c.x, 100 + c.y, RGB(0, 0, 255));
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	RECT rt = { 100, 0, 200, 200 };
	HDC hdc;
	PAINTSTRUCT ps;
	LPCTSTR STR1 = TEXT("원그리기 너무 어려워요~");
	LPCTSTR STR2 = TEXT("뭘 써야하나요~");

	switch (iMessage)
	{
	case WM_DESTROY: 
		PostQuitMessage(0); 
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		DrawText(hdc, STR1, -1, &rt, DT_CENTER | DT_WORDBREAK);
		SetTextAlign(hdc, TA_CENTER);
		TextOut(hdc, 300, 300, STR2, 14);

		Rectangle(hdc, 100, 300, 200, 600);

		DrawCircle(hdc, 60);
		DrawCircle(hdc, 40);
		DrawCircle(hdc, 40, 60);

		EndPaint(hWnd, &ps);
		//원이란 한개의 점을 기준으로 모든 각도에서 동일한 길이의 거리를 가지는 점들의 집합.
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
