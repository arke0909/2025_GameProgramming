#pragma once
#include "Enemy.h"
#include "Window.h"
class NoneMoveEnemy :
    public Enemy
{
public:
    NoneMoveEnemy();
    ~NoneMoveEnemy();
    void CreateEnemyWindow();
    void EnterCollision(Collider* _other) override;

private:
    Window* _window;
};

