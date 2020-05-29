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
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	Circle c1, c2, c3;
	c1.Radius = 60;
	c2.Radius  = 40;
	RECT rt = { 100, 0, 200, 200 };
	HDC hdc;
	PAINTSTRUCT ps;	LPCTSTR STR1 = TEXT("원그리기 너무 어려워요~");	LPCTSTR STR2 = TEXT("뭘 써야하나요~");
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
		for (int i = 0; i < 360; i++)
		{
			c1.y = sin(i) * c1.Radius;//sin(각도) / 반지름 = y좌표
			c1.x = cos(i) * c1.Radius;// cos(각도) / 반지름 = x좌표
			SetPixel(hdc, 100 + c1.x, 100 + c1.y, RGB(255, 0, 0));
		}
		for (int i = 0; i < 360; i++)
		{
			c2.y = sin(i) * c2.Radius;//sin(각도) / 반지름 = y좌표
			c2.x = cos(i) * c2.Radius;//cos(각도) / 반지름 = x좌표
			SetPixel(hdc, 100 + c2.x, 100 + c2.y, RGB(0, 255, 0));
		}
		for (int i = 0; i < 360; i++)
		{
			c3.y = c2.y = sin(i) * c2.Radius;
			c3.x = cos(i) * c1.Radius;
			SetPixel(hdc, 100 + c3.x, 100 + c3.y, RGB(0, 0, 255));
		}
		EndPaint(hWnd, &ps);
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}