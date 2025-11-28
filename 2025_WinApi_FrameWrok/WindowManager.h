#pragma once

struct WindowSet
{
	Vec2 pos;
	Vec2 size;
};

class WindowManager
{
	DECLARE_SINGLE(WindowManager);

public:
	void Init(HWND hWnd);
	void Release();
	HWND CreateSubWindow(LPCWSTR windowName, WindowSet windowSet);
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	HWND _mainHwnd;
	map<wstring ,HWND> _subWindowsHwnd;
};

