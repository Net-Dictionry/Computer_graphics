#include<windows.h>
#include<tchar.h>
#include<math.h>
#include<stdlib.h>
#include"header.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	HDC hDC;
	PAINTSTRUCT PtStr;
	int i, j;

	//����ζ���(�ɸ���)
	int edge = 6;
	PolyLine line[6];//����εı߶��壨���鳤�Ⱥ� edge һ��Ҫ��ͬ��
	//�����ÿ���߸�ֵ
	line[0].x1 = 100;
	line[0].y1 = 100;
	line[0].x2 = 200;
	line[0].y2 = 200;
	line[1].x1 = 200;
	line[1].y1 = 200;
	line[1].x2 = 300;
	line[1].y2 = 100;
	line[2].x1 = 300;
	line[2].y1 = 100;
	line[2].x2 = 300;
	line[2].y2 = 400;
	line[3].x1 = 300;
	line[3].y1 = 400;
	line[3].x2 = 200;
	line[3].y2 = 300;
	line[4].x1 = 200;
	line[4].y1 = 300;
	line[4].x2 = 100;
	line[4].y2 = 400;
	line[5].x1 = 100;
	line[5].y1 = 400;
	line[5].x2 = 100;
	line[5].y2 = 100;
	//����ζ������

	for (i = 0; i < edge; i++){
		if (line[i].y1 > line[i].y2){
			int temp = line[i].y1;
			line[i].y1 = line[i].y2;
			line[i].y2 = temp;
			temp = line[i].x1;
			line[i].x1 = line[i].x2;
			line[i].x2 = temp;
		}
	}//line����װ��ÿ����

	int right = line[0].x1, left = line[0].x1;
	int up = line[0].y2, down = line[0].y1;
	for (i = 1; i < edge; i++){
		if (min(line[i].x1, line[i].x2) < left)
			left = min(line[i].x1, line[i].x2);
		if (max(line[i].x1, line[i].x2) > right)
			right = max(line[i].x1, line[i].x2);
		if (line[i].y1 < down)
			down = line[i].y1;
		if (line[i].y2 > up)
			up = line[i].y2;
	}//Ѱ�Ҷ���ε��������ң����ϣ����µĵ�

	PNODE NET = (PNODE) malloc(sizeof(Node) * (up - down + 1));
	for (i = 0; i <= up - down; i++){
		NET[i].delta = 0;
		NET[i].x = 0;
		NET[i].ymax = 0;
		NET[i].pNext = NULL;
	}

	for (i = 0; i < edge; i++){
		PNODE temp = (PNODE) malloc(sizeof(Node));
		temp->x = line[i].x1;
		temp->ymax = line[i].y2;
		temp->pNext = NULL;
		if (line[i].y1 != line[i].y2)
			temp->delta = (line[i].x1 - line[i].x2) / (line[i].y1 - line[i].y2);
		else
			temp->delta = 0;
		insert(&NET[line[i].y1 - down], temp);
	}

	PNODE Nodebegin = (PNODE) malloc(sizeof(Node));
	Nodebegin->x = 0;
	Nodebegin->delta = 0;
	Nodebegin->pNext = NULL;
	Nodebegin->ymax = 0;

	switch (message)
	{
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &PtStr);
		SetMapMode(hDC, MM_TEXT);

		for (i = 0; i < edge; i++){
			Sleep(50);
			MoveToEx(hDC, line[i].x1, line[i].y1, NULL);
			LineTo(hDC, line[i].x2, line[i].y2);
		}//����ͼ������

		for (i = 0; i <= up - down; i++){
			PNODE temp = Nodebegin;
			while (temp->pNext != NULL){
				if (temp->pNext->ymax - down <= i)
					deletenode(temp);
				else{
					temp->pNext->x = int(temp->pNext->x + temp->pNext->delta);
					temp = temp->pNext;
				}
			}

			PNODE temp2 = NET[i].pNext;
			while (temp2 != NULL){
				PNODE temp3 = (PNODE) malloc(sizeof(Node));
				temp3->x = temp2->x;
				temp3->delta = temp2->delta;
				temp3->pNext = NULL;
				temp3->ymax = temp2->ymax;
				insert(Nodebegin, temp3);
				temp2 = temp2->pNext;
			}

			sort(Nodebegin);
			temp = Nodebegin->pNext;
			if (temp != NULL)
				temp2 = temp->pNext;
			while (temp != NULL && temp2 != NULL){
				for (j = temp->x; j < temp2->x; j++){
					SetPixel(hDC, j, i+down, RGB(0, 0, 0));
				}
				temp = temp2->pNext;
				if (temp != NULL)
					temp2 = temp->pNext;
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
	TCHAR szWindowClass[] = L"����";
	TCHAR szTitle[] = L"�����ͼ��ѧ";
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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	MSG msg;
	if (!InitWindowClass(hInstance, nCmdShow)){
		MessageBox(NULL, L"��������ʧ�ܣ�", _T("��������"), NULL);
		return 1;
	}
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int) msg.wParam;
}