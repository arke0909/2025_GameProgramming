#pragma once
#include "WindowManager.h"
#include "SubUIManager.h"

class Window
{
public:
    Window(LPCWSTR windowName, const WindowSet& windowSet);
    virtual ~Window();

    virtual void Update();
    virtual void Render(HDC hDC);

    HWND GetHandle() const { return _hWnd; }
    HDC GetHDC() const { return _hDC; }
    Vec2 GetPos() const { return _pos; }
    Vec2 GetSize() const { return _size; }
    Vec2 GetWindowSize() const { return _windowSize; }
    Vec2 GetClientTopLeft() const
    {
        POINT pt = { 0, 0 };
        ::ClientToScreen(_hWnd, &pt);
        return Vec2{ (float)pt.x, (float)pt.y };
    }

    void SetVisible(bool visible);
    void SetTop();
    void SetTopMost(bool topMost);
    bool IsVisible() const;

    SubUIManager* GetUI() { return &_uiManager; }

protected:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    virtual LRESULT HandleWnd(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    void SetSizeAndPos(const Vec2& size, const Vec2& centerPos);
    void CreateBackBuffer();
    void ReleaseBackBuffer();

protected:
    HWND _hWnd = nullptr;
    HDC _hDC = nullptr;
    Vec2 _pos;
    Vec2 _topLeft;
    Vec2 _originSize;
    Vec2 _size;
    Vec2 _windowSize;

    HDC _memDC = nullptr;
    HBITMAP _memBitmap = nullptr;
    HBITMAP _oldBitmap = nullptr;

    SubUIManager _uiManager;
};
