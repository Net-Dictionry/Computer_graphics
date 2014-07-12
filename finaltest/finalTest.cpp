#include<windows.h>
#include<tchar.h>
#include<math.h>

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
	double t = 0;
	double x, y;
	HBRUSH hBrush;
	HPEN hPen;
	int x1 = 350;
	int y1 = 250;
	int x2 = 350;
	int y2 = 350;
	int x3 = 300;
	int y3 = 350;
	int x4 = 400;
	int y4 = 200;


	switch (message)
	{
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &PtStr);
		SetMapMode(hDC, MM_TEXT);
		SetPixel(hDC, (int) x1, (int) y1, RGB(0, 0, 0));
		SetPixel(hDC, (int) x2, (int) y2, RGB(0, 0, 0));
		SetPixel(hDC, (int) x3, (int) y3, RGB(0, 0, 0));
		SetPixel(hDC, (int) x4, (int) y4, RGB(0, 0, 0));

		//hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		//hBrush = CreateSolidBrush(RGB(255, 255, 255));

		for (; t <= 1; t += 0.0001){
			x = x1 * pow(t, 3) + x2 * pow(t, 2) * pow(1 - t, 1) * 3 + x3 * pow(t, 1) * pow(1 - t, 2) * 3 + x4*pow(1 - t, 3);
			y = y1 * pow(t, 3) + y2 * pow(t, 2) * pow(1 - t, 1) * 3 + y3 * pow(t, 1) * pow(1 - t, 2) * 3 + y4*pow(1 - t, 3);
			SetPixel(hDC, (int)x, (int)y, RGB(0, 0, 0));
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
	TCHAR szWindowClass [] = L"计算机图形学";
	TCHAR szTitle [] = L"计算机图形学";
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