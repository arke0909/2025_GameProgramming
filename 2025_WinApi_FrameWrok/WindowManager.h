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
	void Update();
	void Render(HDC hDC);
	template <typename T>
	T* CreateSubWindow(LPCWSTR windowName, WindowSet windowSet)
	{
		static_assert(std::is_base_of<Window, T>::value, "T must be Window-based");
		T* window = new T(windowName, windowSet);
		_subWindows.push_back(window);

		return window;
	}

	void CloseAllSubWindows();
	void CloseSubWindow(Window* target);
	void Release();

private:
	void ProcessRemovals();

	HWND _mainHwnd;
	vector<Window*> _subWindows;
	vector<Window*> _removeList;
};

