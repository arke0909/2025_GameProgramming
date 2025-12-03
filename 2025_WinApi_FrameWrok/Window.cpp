#include "pch.h"
#include "Window.h"
#include "WindowManager.h"
#include "EasingManager.h"
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
		posX, posY,
		w, h,
		nullptr,
		nullptr,
		GET_SINGLE(Core)->GetInstance(),
		this);

	_hDC = ::GetDC(_hWnd);
	::ShowWindow(_hWnd, SW_SHOW);
}

Window::~Window()
{
}

void Window::Update()
{
	_uiManager.Update(_hWnd);

	if(!_isMoving) return;

	float ratio = _timer / _duration;
	float ease = GET_SINGLE(EasingManager)->OutSine(ratio);
	float xL = std::lerp(_pos.x, _destination.x, ease);
	float yL = std::lerp(_pos.y, _destination.y, ease);
	xL = std::clamp(xL, 0.f, SCREEN_WIDTH - _size.x);
	yL = std::clamp(yL, 0.f, SCREEN_HEIGHT - _size.y);
	_timer += GET_SINGLE(TimeManager)->GetDeletaTime();
	::MoveWindow(_hWnd, xL, yL, _size.x, _size.y, true);
	_isMoving = _timer <= _duration;
}

void Window::Render(HDC hDC)
{
	int w = _windowSize.x;
	int h = _windowSize.y;

	int posX = _pos.x;
	int posY = _pos.y;

	::PatBlt(hDC, 0, 0, _windowSize.x, _windowSize.y, BLACKNESS);

	_uiManager.Render(hDC);

	::BitBlt(_hDC, 0, 0, _windowSize.x, _windowSize.y, hDC, 0, 0, SRCCOPY);
}



void Window::MoveWindow(const Vec2& velocitiy, const float duration)
{
	_destination.x = velocitiy.x + _pos.x;
	_destination.y = velocitiy.y + _pos.y;
	_timer = 0.f;
	_isMoving = true;
	_duration = duration;
}

void Window::ChangeWindowSize(const Vec2& targetSize, const float duration)
{
}

LRESULT Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Window* window;

	if (message == WM_CREATE)
	{
		CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
		window = (Window*)cs->lpCreateParams;

		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)window);

		window->_hWnd = hWnd;
	}
	else
	{
		window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}

	if (window)
		window->HandleWnd(hWnd, message, wParam, lParam);

	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT Window::HandleWnd(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
	case WM_MOVE:
	{
		RECT rt;
		::GetWindowRect(hWnd, &rt);

		_pos.x = rt.left;
		_pos.y = rt.top;
	}
	break;
	case WM_SIZE:
	{
		RECT rt;
		::GetClientRect(hWnd, &rt);

		//_size.x = rt.right - rt.left;
		//_size.y = rt.bottom - rt.top;
	}
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
