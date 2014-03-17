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
	double k = 4;//输入斜率的部分，可修改
	int y = 300;
	int x = 300;
	int dy = 0;
	int dx = 0;
	int a = 0;
	int b = 0;
	int d = 0;
	int d1 = 0;
	int d2 = 0;

	switch (message)
	{
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &PtStr);
		SetMapMode(hDC, MM_TEXT);

		if (k <= 1 && k >= 0){
			dx = 200;
			dy = dx * k;
			a = -dy;
			b = dx;
			d = 2 * a + b;
			d1 = 2 * a;
			d2 = 2 * (a + b);
			while (dx > 0){
				if (d < 0){
					x++;
					y--;
					d += d2;
					dx--;
				}
				else{
					x++;
					d += d1;
					dx--;
				}
				SetPixel(hDC, x, y, RGB(0, 0, 0));
			}
		}
		else if(k >= -1 && k < 0){
			k = -k;
			dx = 200;
			dy = dx * k;
			a = -dy;
			b = dx;
			d = 2 * a + b;
			d1 = 2 * a;
			d2 = 2 * (a + b);
			while (dx > 0){
				if (d < 0){
					x++;
					y++;
					d += d2;
					dx--;
				}
				else{
					x++;
					d += d1;
					dx--;
				}
				SetPixel(hDC, x, y, RGB(0, 0, 0));
			}
		}
		else if (k > 1){
			dy = 200;
			dx = dy / k;
			a = -dx;
			b = dy;
			d = 2 * a + b;
			d1 = 2 * a;
			d2 = 2 * (a + b);
			while (dy > 0){
				if (d < 0){
					y--;
					x++;
					d += d2;
					dy--;
				}
				else{
					y--;
					d += d1;
					dy--;
				}
				SetPixel(hDC, x, y, RGB(0, 0, 0));
			}
		}
		else if(k < -1){
			k = -k;
			dy = 200;
			dx = dy / k;
			a = -dx;
			b = dy;
			d = 2 * a + b;
			d1 = 2 * a;
			d2 = 2 * (a + b);
			while (dy > 0){
				if (d < 0){
					y++;
					x++;
					d += d2;
					dy--;
				}
				else{
					y++;
					d += d1;
					dy--;
				}
				SetPixel(hDC, x, y, RGB(0, 0, 0));
			}
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