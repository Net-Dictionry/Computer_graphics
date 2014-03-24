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
	
	int r = 100;
	int y = 300;
	int x = 300;

	switch (message)
	{
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &PtStr);
		SetMapMode(hDC, MM_TEXT);
		int delta, delta1, delta2, direction;

		while (x >= 200){
			delta = (x - 1 - 200) * (x - 1 - 200) + (y - 1 - 300) * (y - 1 - 300) - r * r;
			SetPixel(hDC, x, y, RGB(0, 0, 0));
			if (delta < 0){
				delta1 = abs((x - 200)*(x - 200) + (y - 1 - 300)*(y - 1 - 300) - r*r) - abs(delta);
				if (delta1 <= 0)
					direction = 1;
				else
					direction = 2;
			}
			else if (delta > 0){
				delta2 = abs((x - 1 - 200)*(x - 1 - 200) + (y - 300)*(y - 300) - r*r) - abs(delta);
				if (delta2 <= 0)
					direction = 3;
				else
					direction = 2;
			}
			else
				direction = 2;
			switch (direction){
			case 1:
				y--;
				break;
			case 2:
				x--;
				y--;
				break;
			case 3:
				x--;
				break;
			}
			Sleep(10);
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
	TCHAR szWindowClass[] = L"窗口示例";
	TCHAR szTitle[] = L"映射模式及填充示例图";
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