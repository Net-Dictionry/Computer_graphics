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
	HBRUSH hBrush;

	int y = 300;
	int x = 300;
	static double theta = 0;
	static double magn = 1;
	static double x1 = x;
	static double x2 = x;
	static double x3 = x;
	static double y1 = y;
	static double y2 = y;
	static double y3 = y;
	static int t = 0;

	switch (message)
	{
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &PtStr);
		SetMapMode(hDC, MM_TEXT);
		hBrush = CreateSolidBrush(NULL_BRUSH);

		t++;
		SetPixel(hDC, (int) x1, (int) y1, RGB(0, 0, 0));
		Ellipse(hDC, (int) x1 - 10, (int) y1 - 10, (int) x1 + 10, (int) y1 + 10);
		SetPixel(hDC, (int) x2, (int) y2, RGB(0, 0, 0));
		Ellipse(hDC, (int) x2 - 10, (int) y2 - 10, (int) x2 + 10, (int) y2 + 10);
		SetPixel(hDC, (int) x3, (int) y3, RGB(0, 0, 0));
		Ellipse(hDC, (int) x3 - t, (int) y3 - t, (int) x3 + t, (int) y3 + t);

		x1 += 1;
		theta += 0.01;
		x2 = x*cos(theta) - y*sin(theta);
		y2 = x*sin(theta) + y*cos(theta);
		magn += 0.005;
		x3 = x*magn;
		y3 = y*magn;

		EndPaint(hWnd, &PtStr);
		Sleep(25);
		InvalidateRect(hWnd, NULL, true);
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
	TCHAR szWindowClass [] = L"窗口示例";
	TCHAR szTitle [] = L"映射模式及填充示例图";
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