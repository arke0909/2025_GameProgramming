#pragma once
#include "SubUIManager.h"

struct WindowSet;

class Window
{
public:
	Window(LPCWSTR windowName, const WindowSet& windowSet);
	~Window();
public:
	virtual void Update();
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
	Vec2 GetLTPos()
	{
		return _topLeft;
	}
	Vec2 GetSize()
	{
		return _size;
	}
	Vec2 GetWindowSize()
	{
		return _windowSize;
	}
	void SetVisible(bool visible);   
	bool IsVisible() const;            

	SubUIManager* GetUI() { return &_uiManager; }

protected:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT HandleWnd(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetSizeAndPos(const Vec2& size, const Vec2& pos);
protected:
	HWND _hWnd;
	HDC _hDC;
	Vec2 _pos;
	Vec2 _topLeft;
	Vec2 _originSize;
	Vec2 _size;
	Vec2 _windowSize;
	SubUIManager _uiManager;
};

