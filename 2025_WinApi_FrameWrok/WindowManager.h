#pragma once

#include <vector>
#include <algorithm>
#include "Vec2.h"

struct WindowSet
{
    Vec2 pos;
    Vec2 size;
};

class Window;

class WindowManager
{
    DECLARE_SINGLE(WindowManager);

public:
    void Init(HWND hWnd);
    void Update();
    void Render(HDC hDC);

    template <typename T>
    T* CreateSubWindow(LPCWSTR windowName, WindowSet windowSet)
    {
        static_assert(std::is_base_of<Window, T>::value, "T must be derived from Window");
        T* window = new T(windowName, windowSet);
        _subWindows.push_back(window);
        return window;
    }

    void CloseSubWindow(Window* target);
    void CloseAllSubWindows();
    void Release();

private:
    void ProcessRemovals();

private:
    HWND _mainHwnd = nullptr;
    std::vector<Window*> _subWindows;
    std::vector<Window*> _removeList;
};
