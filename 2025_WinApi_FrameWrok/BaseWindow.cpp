#include "pch.h"
#include "BaseWindow.h"
#include "Resource.h"
#include "Core.h"

BaseWindow::BaseWindow()
	:_hInstance(nullptr)
	, _hWnd(nullptr)
{
}

BaseWindow::~BaseWindow()
{
}

int BaseWindow::Run(HINSTANCE hInstance, int nCmdShow)
{
	this->_hInstance = hInstance;
	MyRegisterClass();
	createWindow();
	showWindow(nCmdShow);
	if (!GET_SINGLE(Core)->Init(_hWnd))
	{
		MessageBox(_hWnd, L"Core Init Error", L"ERROR", MB_OK);
	}
	return MessageLoop();
}

ATOM BaseWindow::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = BaseWindow::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = _hInstance;
	wcex.hIcon = LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_MY2025WINAPIFRAMEWROK));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"Gamep";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return ::RegisterClassExW(&wcex);
}

void BaseWindow::createWindow()
{
	int screenX = ::GetSystemMetrics(SM_CXSCREEN);
	int screenY = ::GetSystemMetrics(SM_CYSCREEN);
	int winposx = (screenX - WINDOW_WIDTH) / 2;
	int winposy = (screenY - WINDOW_HEIGHT) / 2;

	_hWnd = ::CreateWindowW(L"Gamep", L"내 총끝은 빛나고", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInstance, nullptr);

	RECT rtWindow = { winposx, winposy, winposx + WINDOW_WIDTH, winposy + WINDOW_HEIGHT };
	::AdjustWindowRect(&rtWindow, WS_OVERLAPPEDWINDOW, false);

	::MoveWindow(_hWnd, winposx, winposy
		, rtWindow.right - rtWindow.left, rtWindow.bottom - rtWindow.top, true);

}

void BaseWindow::showWindow(int nCmdShow)
{
	::ShowWindow(_hWnd, nCmdShow);
}

int BaseWindow::MessageLoop()
{
	MSG msg;

	while (true)
	{
		if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message) break;

			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			GET_SINGLE(Core)->GameLoop();

		}
	}
	GET_SINGLE(Core)->CleanUp();
	return (int)msg.wParam;
}

LRESULT BaseWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
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
