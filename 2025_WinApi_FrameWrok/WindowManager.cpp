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
		window->Update();
	}
}

void WindowManager::Render(HDC hDC)
{
	for (auto window : _subWindows)
	{
		window->Render(hDC);
	}
}

Window* WindowManager::CreateSubWindow(LPCWSTR windowName, WindowSet windowSet)
{
	Window* window = new Window(windowName, windowSet);

	_subWindows.push_back(window);

	return window;
}

void WindowManager::Release()
{
	for (auto window : _subWindows)
	{
		::ReleaseDC(window->GetHandle(), window->GetHDC());
	}
}

