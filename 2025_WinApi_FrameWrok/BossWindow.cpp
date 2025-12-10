#include "pch.h"
#include "BossWindow.h"
#include "EasingManager.h"

BossWindow::BossWindow(LPCWSTR windowName, const WindowSet& windowSet)
	: Window(windowName, windowSet)
{
}

BossWindow::~BossWindow()
{
}

void BossWindow::WindowMoveAndChangeSize(const Vec2& deltaSize, const Vec2& deltaPos, const float duration)
{
	SetSizeAndPos(deltaSize, deltaPos);
}
