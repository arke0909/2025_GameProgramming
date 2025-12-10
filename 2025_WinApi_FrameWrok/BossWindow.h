#pragma once
#include "Window.h"
class BossWindow :
    public Window
{
public:
    BossWindow(LPCWSTR windowName, const WindowSet& windowSet);
    ~BossWindow();

public:
    void WindowMoveAndChangeSize(const Vec2& deltaPos, const Vec2& deltaSize, const float duration = 0.5f);
};
