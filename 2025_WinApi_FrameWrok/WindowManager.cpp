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
		if (!window) continue;
		window->Update();
	}

	ProcessRemovals();
}

void WindowManager::Render(HDC hDC)
{
	for (auto window : _subWindows)
	{
		if (!window) continue;
		window->Render(hDC);
	}
}

void WindowManager::CloseAllSubWindows()
{
	for (Window* window : _subWindows)
	{
		if (window)
			_removeList.push_back(window);
	}
}

void WindowManager::CloseSubWindow(Window* target)
{
	if (!target) return;

	if (std::find(_removeList.begin(), _removeList.end(), target) == _removeList.end())
		_removeList.push_back(target);
}

void WindowManager::ProcessRemovals()
{
	for (Window* target : _removeList)
	{
		if (!target) continue;

		auto it = std::find(_subWindows.begin(), _subWindows.end(), target);
		if (it != _subWindows.end())
		{
			::DestroyWindow(target->GetHandle());
			delete target;
			_subWindows.erase(it);
		}
	}
	_removeList.clear();
}

void WindowManager::Release()
{
	for (auto window : _subWindows)
	{
		if (window)
			::ReleaseDC(window->GetHandle(), window->GetHDC());
	}
	CloseAllSubWindows();
	ProcessRemovals();
	_subWindows.clear();
}

