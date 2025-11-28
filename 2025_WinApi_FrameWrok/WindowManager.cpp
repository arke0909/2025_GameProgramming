#include "pch.h"
#include "Core.h"
#include "WindowManager.h"

void WindowManager::Init(HWND hWnd)
{
	_mainHwnd = hWnd;
}

HWND WindowManager::CreateSubWindow(LPCWSTR windowName, WindowSet windowSet)
{
	WNDCLASS wcex = {0};

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GET_SINGLE(Core)->GetInstance();
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"Window";

	::RegisterClass(&wcex);

	auto windowSetting = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	int posX = windowSet.pos.x - (windowSet.size.x / 2);
	int posY = windowSet.pos.y - (windowSet.size.y / 2);

	HWND hWnd = ::CreateWindowW(
		L"Window",
		windowName,
		windowSetting,
		posX, posY,
		windowSet.size.x,
		windowSet.size.y,
		nullptr,
		nullptr,
		GET_SINGLE(Core)->GetInstance(),
		nullptr);

	_subWindowsHwnd.insert({ windowName, hWnd });

	::ShowWindow(hWnd, SW_SHOW);
	return hWnd;
}

LRESULT WindowManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}