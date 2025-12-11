#pragma once
#include "Enemy.h"
#include "WindowManager.h"
#include "Window.h"

class CircleShotEnemy :
    public Enemy
{
public:
    CircleShotEnemy();
	~CircleShotEnemy() override;

public:
    void CreateEnemyWindow();
    void RemoveEnemyWindow()
    {
        GET_SINGLE(WindowManager)->CloseSubWindow(_window);
	}

private:
    void Update() override;
    void Attack();

private:
    float _coolTime;
	float _accTime;

    Window* _window;
};
