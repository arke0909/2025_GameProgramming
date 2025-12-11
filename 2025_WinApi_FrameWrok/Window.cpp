#include "pch.h"
#include "Window.h"
#include "WindowManager.h"
#include "EasingManager.h"
#include "Core.h"
#include "Resource.h"

#undef max

Window::Window(LPCWSTR windowName, const WindowSet& windowSet)
{
	WNDCLASS wcex = { 0 };

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GET_SINGLE(Core)->GetInstance();
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"Window";

	::RegisterClass(&wcex);

	_originSize = windowSet.size;

	SetSizeAndPos(windowSet.size, windowSet.pos);

	_hWnd = ::CreateWindowW(
		L"Window",
		windowName,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		_topLeft.x, _topLeft.y,
		_size.x, _size.y,
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

void Window::SetVisible(bool visible)
{
	ShowWindow(_hWnd, visible ? SW_SHOW : SW_HIDE);
}

bool Window::IsVisible() const
{
	return IsWindowVisible(_hWnd) != FALSE;
}


void Window::Update()
{
	_uiManager.Update(_hWnd);
}

void Window::Render(HDC hDC)
{
    int w = _windowSize.x;
    int h = _windowSize.y;

    HDC memDC = ::CreateCompatibleDC(hDC);
    HBITMAP memBitmap = ::CreateCompatibleBitmap(hDC, w, h);
    HBITMAP oldBitmap = (HBITMAP)::SelectObject(memDC, memBitmap);

    ::BitBlt(memDC, 0, 0, w, h, hDC, _topLeft.x, _topLeft.y, SRCCOPY);

    if (_uiManager.Count() > 0)
        _uiManager.Render(memDC);
    ::BitBlt(_hDC, 0, 0, w, h, memDC, 0, 0, SRCCOPY);

    ::SelectObject(memDC, oldBitmap);
    ::DeleteObject(memBitmap);
    ::DeleteDC(memDC);
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
        return window->HandleWnd(hWnd, message, wParam, lParam);

    return DefWindowProc(hWnd, message, wParam, lParam);
}


LRESULT Window::HandleWnd(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_NCHITTEST:
	{
		LRESULT hit = DefWindowProc(hWnd, message, wParam, lParam);
		if (hit == HTCAPTION)
			return HTCLIENT;   // 마우스 드래그 차단
		return hit;
	}
	case WM_SYSCOMMAND:

		switch (wParam & 0xFFF0)
		{
		case SC_MOVE:
		case SC_SIZE:
		case SC_MAXIMIZE:
			return 0;
		}

	return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	return 0;
	case WM_MOVE:
	{
		RECT rt;
		::GetWindowRect(hWnd, &rt);

		int left = rt.left;
		int top = rt.top;

		// 중앙 기준 저장
		_topLeft = { left, top };
		_pos = { left + _size.x * 0.5f, top + _size.y * 0.5f };
	}
	return 0;

	case WM_SIZE:
	{
		RECT rt;
		::GetWindowRect(hWnd, &rt);

		int left = rt.left;
		int top = rt.top;
		_topLeft = { left, top };

		_size.x = rt.right - rt.left;
		_size.y = rt.bottom - rt.top;
	}
	return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

void Window::SetSizeAndPos(const Vec2& size, const Vec2& centerPos)
{
	auto windowSetting = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;

	// 클라이언트 영역 기준
	RECT rect = { 0, 0, (LONG)size.x, (LONG)size.y };
	AdjustWindowRect(&rect, windowSetting, FALSE);

	int w = rect.right - rect.left;
	int h = rect.bottom - rect.top;

	w = std::max(w, 1);
	h = std::max(h, 1);

	float halfW = w * 0.5f;
	float halfH = h * 0.5f;

	float minX = halfW;
	float maxX = SCREEN_WIDTH - halfW;
	float minY = halfH;
	float maxY = SCREEN_HEIGHT - halfH;

	if (minX > maxX)  minX = maxX = SCREEN_WIDTH * 0.5f;
	if (minY > maxY)  minY = maxY = SCREEN_HEIGHT * 0.5f;

	float clampedX = std::clamp(centerPos.x, minX, maxX);
	float clampedY = std::clamp(centerPos.y, minY, maxY);

	int left = (int)(clampedX - halfW);
	int top = (int)(clampedY - halfH);

	int minLeft = 0;
	int maxLeft = SCREEN_WIDTH - w;

	if (maxLeft < minLeft)
		maxLeft = minLeft;

	int minTop = 0;
	int maxTop = SCREEN_HEIGHT - h;

	if (maxTop < minTop)
		maxTop = minTop;

	left = std::clamp(left, minLeft, maxLeft);
	top = std::clamp(top, minTop, maxTop);


	_windowSize = size;
	_size = { (float)w, (float)h };
	_pos = { clampedX, clampedY };
	_topLeft = { (float)left, (float)top };

	if (_hWnd == nullptr) return;

	MoveWindow(_hWnd, left, top, w, h, TRUE);
}
