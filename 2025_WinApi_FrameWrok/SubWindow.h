#pragma once
class SubWindow
{
public:
	SubWindow();
	~SubWindow();
public:
	void Update();
	void Render(HDC hDC);

private:
	HWND _hWnd;

};

