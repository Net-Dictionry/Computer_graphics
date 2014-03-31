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
	HPEN hPen;

	switch (message)
	{
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &PtStr);
		SetMapMode(hDC, MM_TEXT);

		hPen = CreatePen(
			PS_SOLID,
			1,
			RGB(0, 0, 0)
			);
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		
		POINT lpPoints[8];
		lpPoints[0].x = 100;
		lpPoints[0].y = 120;
		lpPoints[1].x = 50;
		lpPoints[1].y = 120;
		lpPoints[2].x = 100;
		lpPoints[2].y = 120;
		lpPoints[3].x = 100;
		lpPoints[3].y = 180;
		lpPoints[4].x = 50;
		lpPoints[4].y = 200;
		lpPoints[5].x = 100;
		lpPoints[5].y = 180;
		lpPoints[6].x = 100;
		lpPoints[6].y = 200;
		lpPoints[7].x = 100;
		lpPoints[7].y = 100;
		SelectObject(hDC, hPen);
		SelectObject(hDC, hBrush);
		Polygon(hDC, lpPoints, 8);

		POINT lpPoints2[8];
		lpPoints2[0].x = 120;
		lpPoints2[0].y = 120;
		lpPoints2[1].x = 120;
		lpPoints2[1].y = 200;
		lpPoints2[2].x = 170;
		lpPoints2[2].y = 200;
		lpPoints2[3].x = 120;
		lpPoints2[3].y = 200;
		lpPoints2[4].x = 120;
		lpPoints2[4].y = 100;
		lpPoints2[5].x = 120;
		lpPoints2[5].y = 120;
		lpPoints2[6].x = 160;
		lpPoints2[6].y = 100;
		lpPoints2[7].x = 120;
		lpPoints2[7].y = 120;
		SelectObject(hDC, hPen);
		SelectObject(hDC, hBrush);
		Polygon(hDC, lpPoints2, 8);

		POINT lpPoints3[6];
		lpPoints3[0].x = 250;
		lpPoints3[0].y = 120;
		lpPoints3[1].x = 200;
		lpPoints3[1].y = 120;
		lpPoints3[2].x = 250;
		lpPoints3[2].y = 120;
		lpPoints3[3].x = 240;
		lpPoints3[3].y = 100;
		lpPoints3[4].x = 250;
		lpPoints3[4].y = 120;
		lpPoints3[5].x = 300;
		lpPoints3[5].y = 120;
		SelectObject(hDC, hPen);
		SelectObject(hDC, hBrush);
		Polygon(hDC, lpPoints3, 6);

		POINT lpPoints4[5];
		lpPoints4[0].x = 220;
		lpPoints4[0].y = 130;
		lpPoints4[1].x = 280;
		lpPoints4[1].y = 130;
		lpPoints4[2].x = 280;
		lpPoints4[2].y = 150;
		lpPoints4[3].x = 220;
		lpPoints4[3].y = 150;
		lpPoints4[4].x = 220;
		lpPoints4[4].y = 130;
		SelectObject(hDC, hPen);
		SelectObject(hDC, hBrush);
		Polygon(hDC, lpPoints4, 5);

		POINT lpPoints5[7];
		lpPoints5[0].x = 250;
		lpPoints5[0].y = 150;
		lpPoints5[1].x = 250;
		lpPoints5[1].y = 200;
		lpPoints5[2].x = 250;
		lpPoints5[2].y = 170;
		lpPoints5[3].x = 210;
		lpPoints5[3].y = 180;
		lpPoints5[4].x = 250;
		lpPoints5[4].y = 170;
		lpPoints5[5].x = 290;
		lpPoints5[5].y = 180;
		lpPoints5[6].x = 250;
		lpPoints5[6].y = 170;
		SelectObject(hDC, hPen);
		SelectObject(hDC, hBrush);
		Polygon(hDC, lpPoints5, 7);

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