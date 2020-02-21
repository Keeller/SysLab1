// WindowsProject3.cpp : Определяет точку входа для приложения.
//
#include "stdafx.h"
#include "WindowsProject3.h"
#include<windows.h>
#include<iostream>
#include<string>

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

int WINAPI WinMain(HINSTANCE hInst,
	HINSTANCE hPrevInst,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	TCHAR szClassName[] = L"My class";
	
	HWND hMainWind[3];
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
		WS_OVERLAPPEDWINDOW,
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
		WS_OVERLAPPEDWINDOW,
		rc.right-(rc.right-rc.left)/5,
		rc.top+(rc.bottom-rc.top)/2,
		rc.right-(rc.right - (rc.right - rc.left) / 5),
		(rc.bottom - rc.top) / 6,
		hMainWind[0],
		NULL,
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
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return NULL;
}