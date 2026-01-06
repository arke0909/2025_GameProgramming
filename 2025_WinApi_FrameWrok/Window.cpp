#include "pch.h"
#include "Window.h"
#include "Core.h"

Window::Window(LPCWSTR windowName, const WindowSet& windowSet)
{
    WNDCLASS wc = {};
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GET_SINGLE(Core)->GetInstance();
    wc.lpszClassName = L"Window";

    RegisterClass(&wc);

    _originSize = windowSet.size;
    SetSizeAndPos(windowSet.size, windowSet.pos);

    _hWnd = CreateWindowW(
        wc.lpszClassName,
        windowName,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        (int)_topLeft.x,
        (int)_topLeft.y,
        (int)_size.x,
        (int)_size.y,
        nullptr,
        nullptr,
        GET_SINGLE(Core)->GetInstance(),
        this);

    _hDC = GetDC(_hWnd);
    ShowWindow(_hWnd, SW_SHOW);
}

Window::~Window()
{
    // 삭제는 WindowManager에서 책임짐
}

void Window::SetVisible(bool visible)
{
    ShowWindow(_hWnd, visible ? SW_SHOW : SW_HIDE);
}

bool Window::IsVisible() const
{
    return IsWindowVisible(_hWnd);
}

void Window::Update()
{
    _uiManager.Update(_hWnd);
}

void Window::Render(HDC hDC)
{
    int w = _windowSize.x;
    int h = _windowSize.y;

    HDC memDC = CreateCompatibleDC(hDC);
    HBITMAP memBitmap = CreateCompatibleBitmap(hDC, w, h);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, memBitmap);

    BitBlt(memDC, 0, 0, w, h, hDC, (int)_topLeft.x, (int)_topLeft.y, SRCCOPY);

    if (_uiManager.Count() > 0)
        _uiManager.Render(memDC);

    BitBlt(_hDC, 0, 0, w, h, memDC, 0, 0, SRCCOPY);

    SelectObject(memDC, oldBitmap);
    DeleteObject(memBitmap);
    DeleteDC(memDC);
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Window* window = nullptr;

    if (msg == WM_CREATE)
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
        return window->HandleWnd(hWnd, msg, wParam, lParam);

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleWnd(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        return 0;
    }

    case WM_MOVE:
    {
        RECT rect;
        GetWindowRect(hWnd, &rect);
        _topLeft = { (float)rect.left, (float)rect.top };
        _pos = { _topLeft.x + _size.x * 0.5f, _topLeft.y + _size.y * 0.5f };
        return 0;
    }

    case WM_SIZE:
    {
        RECT rect;
        GetWindowRect(hWnd, &rect);
        _topLeft = { (float)rect.left, (float)rect.top };
        _size = { (float)(rect.right - rect.left), (float)(rect.bottom - rect.top) };
        return 0;
    }

    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
}

void Window::SetSizeAndPos(const Vec2& size, const Vec2& centerPos)
{
    RECT rect = { 0, 0, (LONG)size.x, (LONG)size.y };
    AdjustWindowRect(&rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, FALSE);

    int w = rect.right - rect.left;
    int h = rect.bottom - rect.top;

    float halfW = w * 0.5f;
    float halfH = h * 0.5f;

    int left = (int)(centerPos.x - halfW);
    int top = (int)(centerPos.y - halfH);

    _windowSize = size;
    _size = { (float)w, (float)h };
    _pos = centerPos;
    _topLeft = { (float)left, (float)top };
}
