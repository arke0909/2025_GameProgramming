#pragma once
#include "Window.h"
class GameWindow :
    public Window
{
public:
	GameWindow(LPCWSTR windowName, const WindowSet& windowSet);
	~GameWindow();
public:
	void Update() override;
	void WindowMoveAndChangeSize(const Vec2& deltaPos, const Vec2& deltaSize, const float duration = 0.5f);
private:
	Vec2 _moveStartPos;
	Vec2 _destination;
	Vec2 _targetSize;
	bool _isChangeing = false;
	float _duration = 2.f;
	float _timer = 0.f;
	bool  _isRestoring = false;
	float _restoreDelay = 1.5f;
	float _restoreTimer = 0.f;
};

