#include<windows.h>
#include<tchar.h>
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

//定义部分
int x1 = 200;
int y1 = 90;
int x2 = 90;
int y2 = 200;
int xl = 50;
int xr = 180;
int yb = 50;
int yt = 180;

int encode(double x, double y){
	int c = 0;
	if (x < xl) c |= LEFT;
	if (x > xr) c |= RIGHT;
	if (y < yb) c |= BOTTOM;
	if (y > yt) c |= TOP;
	return c;
}

BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	MSG msg;
	if (!InitWindowClass(hInstance, nCmdShow)){
		MessageBox(NULL, L"创建窗口失败！", _T("创建窗口"), NULL);
		return 1;
	}
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	HDC hDC;
	PAINTSTRUCT PtStr;

	int code1 = 0;
	int code2 = 0;
	int code = 0;
	int temp = 0;
	double differ = 100;
	code1 = encode(x1, y1);
	code2 = encode(x2, y2);
	double tempx1 = x1;
	double tempx2 = x2;
	double tempy1 = y1;
	double tempy2 = y2;
	double x = (tempx1 + tempx2) / 2;
	double y = (tempy1 + tempy2) / 2;

	switch (message)
	{
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &PtStr);
		SetMapMode(hDC, MM_TEXT);

		MoveToEx(hDC, xl, yb, NULL);
		LineTo(hDC, xr, yb);
		LineTo(hDC, xr, yt);
		LineTo(hDC, xl, yt);
		LineTo(hDC, xl, yb);

		if (code1 != 0 || code2 != 0){
			if ((code1&code2) != 0){
				temp = 1;
			}
			else{
				while (differ > 1){
					code = encode(x, y);
					if ((code&code1) != 0){
						tempx1 = x;
						tempy1 = y;
						code1 = encode(tempx1, tempy1);
					}
					else{
						tempx2 = x;
						tempy2 = y;
						code2 = encode(tempx2, tempy2);
					}
					x = (tempx1 + tempx2) / 2;
					y = (tempy1 + tempy2) / 2;
					differ = (tempx1 - x)*(tempx1 - x) + (tempy1 - y)*(tempy1 - y);
				}
				x1 = tempx1;
				y1 = tempy1;
				tempx2 = x2;
				tempy2 = y2;
				code2 = encode(tempx2, tempy2);
				differ = 100;
				x = (tempx1 + tempx2) / 2;
				y = (tempy1 + tempy2) / 2;
				while (differ > 1){
					code = encode(x, y);
					if ((code&code2) != 0){
						tempx2 = x;
						tempy2 = y;
						code2 = encode(tempx2, tempy2);
					}
					else{
						tempx1 = x;
						tempy1 = y;
						code1 = encode(tempx1, tempy1);
					}
					x = (tempx1 + tempx2) / 2;
					y = (tempy1 + tempy2) / 2;
					differ = (tempx2 - x)*(tempx2 - x) + (tempy2 - y)*(tempy2 - y);
				}
				x2 = tempx2;
				y2 = tempy2;
			}
		}
		if (temp == 0){
			MoveToEx(hDC, x1, y1, NULL);
			LineTo(hDC, x2, y2);
		}

		EndPaint(hWnd, &PtStr);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}

BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow){
	WNDCLASSEX wcex;
	HWND hWnd;
	TCHAR szWindowClass[] = L"计算机图形学";
	TCHAR szTitle[] = L"计算机图形学";
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = 0;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	if (!RegisterClassEx(&wcex))
		return FALSE;
	hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
		);
	if (!hWnd)
		return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}