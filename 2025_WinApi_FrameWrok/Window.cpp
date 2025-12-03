#include "pch.h"
#include "Window.h"
#include "WindowManager.h"
#include "Core.h"

Window::Window(LPCWSTR windowName, const WindowSet& windowSet)
{
	WNDCLASS wcex = { 0 };

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GET_SINGLE(Core)->GetInstance();
	//wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"Window";

	::RegisterClass(&wcex);

	auto windowSetting = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	
	RECT rect = { 0, 0, windowSet.size.x , windowSet.size.y };
	::AdjustWindowRect(&rect, windowSetting, false);

	int w = rect.right - rect.left;
	int h = rect.bottom - rect.top;
	
	int posX = windowSet.pos.x - (w / 2);
	int posY = windowSet.pos.y - (h / 2);
	
	_windowSize = windowSet.size;
	_pos = { posX, posY };
	_size = { w, h };

	_hWnd = ::CreateWindowW(
		L"Window",
		windowName,
		windowSetting,
		posX, posY ,
		w, h,
		nullptr,
		nullptr,
		GET_SINGLE(Core)->GetInstance(),
		nullptr);

	_hDC = ::GetDC(_hWnd);
	::ShowWindow(_hWnd, SW_SHOW);
}

Window::~Window()
{
}

void Window::Update()
{
	_uiManager.Update(_hWnd);
}

void Window::Render(HDC hDC)
{
	_uiManager.Render(_hDC);
}

LRESULT Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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