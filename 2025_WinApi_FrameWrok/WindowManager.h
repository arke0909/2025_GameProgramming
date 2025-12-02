#pragma once

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
	void Render(HDC hDC);
	void Release();
	Window* CreateSubWindow(LPCWSTR windowName, WindowSet windowSet);
private:
	HWND _mainHwnd;
	vector<Window*> _subWindows;
};

