#include "pch.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "Window.h"

void WindowManager::Init(HWND hWnd)
{
	_mainHwnd = hWnd;
}

void WindowManager::Update()
{
	for (auto window : _subWindows)
	{
		GET_SINGLE(InputManager)->UpdateMouse(window->GetHandle());
		window->Update();
		window->GetUI()->Update(window->GetHandle());
	}
}

void WindowManager::Render(HDC hDC)
{
	for (auto window : _subWindows)
	{
		window->Render(hDC);
		window->GetUI()->Render(window->GetHDC());
	}
}

void WindowManager::CloseAllSubWindows()
{
	for (Window* window : _subWindows)
	{
		if (window)
		{
			::DestroyWindow(window->GetHandle());
			delete window; 
		}
	}
	_subWindows.clear(); 
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

