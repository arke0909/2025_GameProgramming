#pragma once
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
	void MoveWindow(const Vec2& velocitiy, const float duration = 10.f);
	void ChangeWindowSize(const Vec2& targetSize, const float duration = 10.f);
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT HandleWnd(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	HWND _hWnd;
	HDC _hDC;
	Vec2 _pos;
	Vec2 _size;
	Vec2 _windowSize;
	Vec2 _destination;
	bool _isMoving = false;
	float _duration = 2.f;
	float _timer = 0.f;
};

