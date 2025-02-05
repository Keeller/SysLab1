// WindowsProject3.cpp : Определяет точку входа для приложения.
//
#include "stdafx.h"
#include "WindowsProject3.h"
#include<windows.h>
#include<iostream>
#include<string>
#define _STD_STRING_SIZE_ 255

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR mainMessage[] = L"Hello World";

void createClass(WNDCLASSEX& wc,const HINSTANCE& hinst,const int r,const int g,const int b,const TCHAR Name[],
	WNDPROC proc) {
	
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = proc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = Name;
	wc.cbWndExtra = NULL;
	wc.cbClsExtra = NULL;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(r,g,b));
	wc.hInstance = hinst;
}
HWND hMainWind[10];
LRESULT numSymb=0;
int WINAPI WinMain(HINSTANCE hInst,
	HINSTANCE hPrevInst,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	TCHAR szClassName[] = L"My class";
	
	
	MSG msg;
	WNDCLASSEX wc[3];

	createClass(wc[0],hInst,0,165,80,szClassName,WndProc);
	createClass(wc[1],hInst,0,0,255,(TCHAR*)(L"Child1"),WndProc);
	createClass(wc[2],hInst,66,170,255,(TCHAR*)(L"Child2"),WndProc);
	for (WNDCLASSEX wclass : wc) {
		if (!RegisterClassEx(&wclass)) {
			MessageBox(NULL, (L"Не получилось зарегистрировать класс "+std::wstring(wc->lpszClassName)).c_str(), L"Ошибка", MB_OK);
			return NULL;
		}
	}
	INT cxScreen = GetSystemMetrics(SM_CXSCREEN);
	INT cyScreen = GetSystemMetrics(SM_CYSCREEN);
	hMainWind[0] = CreateWindow(szClassName,
		L"Полноценная оконная процедура",
		WS_OVERLAPPEDWINDOW | WS_VSCROLL,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		cxScreen,
		cyScreen,
		(HWND)NULL,
		NULL, // 
		HINSTANCE(hInst),
		NULL
	);
	RECT rc;
	GetClientRect(hMainWind[0],&rc);
	hMainWind[1] = CreateWindow((TCHAR*)(L"Child1"),
		L"Окно 1",
		WS_CHILD,
		rc.left+(rc.right-rc.left)/3,
		rc.top+(rc.bottom-rc.top)/3,
		(rc.right-rc.left)/3,
		(rc.bottom-rc.top)/3,
		hMainWind[0],
		NULL,
		hInst,
		NULL
	);

	if (!hMainWind) {

		MessageBox(NULL, L"Не получилось создать окно!", L"Ошибка", MB_OK);
		return NULL;
	}
	
	

	hMainWind[2] = CreateWindow((TCHAR*)(L"Child2"),
		L"Окно 2",
		WS_CHILD,
		rc.right-(rc.right-rc.left)/5,
		rc.top+(rc.bottom-rc.top)/2,
		rc.right-(rc.right - (rc.right - rc.left) / 5),
		(rc.bottom - rc.top) / 6,
		hMainWind[0],
		NULL,
		hInst,
		NULL
	);
	RECT r; GetClientRect(hMainWind[1], &r);
	 hMainWind[3] = CreateWindow(
		(TCHAR*)(L"BUTTON"),
		(TCHAR*)(L"open"),
		WS_CHILD | WS_VISIBLE,
		r.left,
		r.top,
		70,
		30,
		hMainWind[1],
		(HMENU)1001,
		hInst,
		NULL
	);

	 hMainWind[6] = CreateWindow(
		 (TCHAR*)(L"BUTTON"),
		 (TCHAR*)(L"open B"),
		 WS_CHILD | WS_VISIBLE,
		 r.left,
		 r.top+40,
		 70,
		 30,
		 hMainWind[1],
		 (HMENU)1003,
		 hInst,
		 NULL
	 );
	 hMainWind[4]= CreateWindow(
		 (TCHAR*)(L"Edit"),
		 NULL,
		 WS_BORDER | WS_CHILD | WS_VISIBLE | NULL | NULL,
		 10,
		 10,
		 200,
		 20,
		 hMainWind[2],
		 NULL,
		 hInst,
		 NULL
	 );
	 hMainWind[5] = CreateWindow(
		 (TCHAR*)(L"BUTTON"),
		 (TCHAR*)(L"Write"),
		WS_CHILD | WS_VISIBLE,
		 10,
		 30,
		 200,
		 20,
		 hMainWind[2],
		 (HMENU)1002,
		 hInst,
		 NULL
	 );

	 hMainWind[7] = CreateWindow(
		 (TCHAR*)(L"Edit"),
		 NULL,
		 WS_BORDER | WS_CHILD | WS_VISIBLE | NULL | NULL,
		 10,
		 80,
		 200,
		 20,
		 hMainWind[2],
		 NULL,
		 hInst,
		 NULL
	 );
	 hMainWind[8] = CreateWindow(
		 (TCHAR*)(L"BUTTON"),
		 (TCHAR*)(L"Write B"),
		 WS_CHILD | WS_VISIBLE,
		 10,
		 110,
		 200,
		 20,
		 hMainWind[2],
		 (HMENU)1004,
		 hInst,
		 NULL
	 );
	for (int i = 0;i<3;i++) {
		if (!hMainWind[i]) {

			MessageBox(NULL, (L"Не получилось создать окно "+std::to_wstring(i)).c_str(), L"Ошибка", MB_OK);
			return NULL;
		}
	}
	for (HWND hwd : hMainWind) {
		ShowWindow(hwd, nCmdShow);
		UpdateWindow(hwd);
	}
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;
	COLORREF colorText = RGB(255, 0, 0);
	switch (uMsg) {
	case WM_PAINT:
		/*
		hDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		SetTextColor(hDC, colorText);
		DrawText(hDC, mainMessage, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hWnd, &ps);
		*/
		break;
	case WM_DESTROY:
		PostQuitMessage(NULL);
		break;
	case WM_COMMAND:

		HANDLE myFile;
		WCHAR cBuffer[_STD_STRING_SIZE_];
		WCHAR i;
		switch (wParam)
		{

		case 1001:
			DWORD m;
			myFile = CreateFile(L"test.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
			ReadFile(myFile, &cBuffer, sizeof(WCHAR)*numSymb, &m, NULL);
			CloseHandle(myFile);
			hDC = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rect);
			SetTextColor(hDC, colorText);
			DrawText(hDC, (WCHAR*)cBuffer, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hWnd, &ps);
			break;

		case 1002:
			myFile = CreateFile(L"test.txt", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
			DWORD l;
			WCHAR buffer[_STD_STRING_SIZE_];
			numSymb=SendMessage(hMainWind[4],WM_GETTEXTLENGTH,0,0)+1;
			SendMessage(hMainWind[4],WM_GETTEXT,numSymb,LPARAM(buffer));
			WriteFile(myFile, &buffer, sizeof(WCHAR)*numSymb, &l, NULL);
			CloseHandle(myFile);
			break;

		case 1003:
			char buffert[102555];
			DWORD m1;
			myFile = CreateFile(L"tbin.bin", GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			ReadFile(myFile, &buffer, sizeof(char)*numSymb, &m1, NULL);
			CloseHandle(myFile);
			/*
			hDC = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rect);
			SetTextColor(hDC, colorText);
			DrawText(hDC, LPWSTR((char*)cBuffer), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hWnd, &ps);
			*/
			break;

		case 1004:
			myFile = CreateFile(L"tbin.bin", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			DWORD l1;
			char bufferb[_STD_STRING_SIZE_];
			numSymb = SendMessage(hMainWind[7], WM_GETTEXTLENGTH, 0, 0) + 1;
			SendMessage(hMainWind[7], WM_GETTEXT, numSymb, LPARAM(bufferb));
			WriteFile(myFile, &bufferb, sizeof(char)*numSymb, &l1, NULL);
			CloseHandle(myFile);
			break;
		default:
			break;
		}
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return NULL;
}