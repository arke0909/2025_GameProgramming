#pragma once
#include "SubUIManager.h"

struct WindowSet;

class Window
{
public:
	Window(LPCWSTR windowName, const WindowSet& windowSet);
	~Window();
public:
	void Update();
	void Render(HDC hDC);
	HWND GetHandle()
	{
		return _hWnd;
	}
	HDC GetHDC()
	{
		return _hDC;
	}
	Vec2 GetPos()
	{
		return _pos;
	}
	Vec2 GetSize()
	{
		return _size;
	}
	Vec2 GetWindowSize()
	{
		return _windowSize;
	}
	SubUIManager* GetUI() { return &_uiManager; }
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	HWND _hWnd;
	HDC _hDC;
	Vec2 _pos;
	Vec2 _size;
	Vec2 _windowSize;
	SubUIManager _uiManager;
};

