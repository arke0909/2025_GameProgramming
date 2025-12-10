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

void WindowManager::CloseSubWindow(Window* target)
{
	if (!target) return;

	auto it = std::find(_subWindows.begin(), _subWindows.end(), target);
	if (it != _subWindows.end())
	{
		::DestroyWindow(target->GetHandle());
		delete target;
		_subWindows.erase(it);
	}
}

void WindowManager::Release()
{
	for (auto window : _subWindows)
	{
		::ReleaseDC(window->GetHandle(), window->GetHDC());
		SAFE_DELETE(window);
	}
}

