#include "pch.h"
#include "WindowManager.h"
#include "Window.h"

void WindowManager::Init(HWND hWnd)
{
    _mainHwnd = hWnd;
}

void WindowManager::Update()
{
    for (auto window : _subWindows)
    {
        if (window) window->Update();
    }

    ProcessRemovals();
}

void WindowManager::Render(HDC hDC)
{
    for (auto window : _subWindows)
    {
        if (window) window->Render(hDC);
    }
}

void WindowManager::CloseSubWindow(Window* target)
{
    if (!target) return;

    if (std::find(_removeList.begin(), _removeList.end(), target) == _removeList.end())
    {
        _removeList.push_back(target);
    }
}

void WindowManager::CloseAllSubWindows()
{
    for (Window* window : _subWindows)
    {
        if (window && std::find(_removeList.begin(), _removeList.end(), window) == _removeList.end())
        {
            _removeList.push_back(window);
        }
    }
}

void WindowManager::ProcessRemovals()
{
    for (Window* window : _removeList)
    {
        auto it = std::find(_subWindows.begin(), _subWindows.end(), window);
        if (it != _subWindows.end())
        {
            ::ReleaseDC(window->GetHandle(), window->GetHDC());
            ::DestroyWindow(window->GetHandle());
            delete window;
            _subWindows.erase(it);
        }
    }
    _removeList.clear();
}

void WindowManager::Release()
{
    CloseAllSubWindows();
    ProcessRemovals();
    _subWindows.clear();
}
