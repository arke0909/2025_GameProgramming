#pragma once
#include "Scene.h"
#include "EnemySpawnManager.h"

class GameWindow;

class EnemyTestScene :
    public Scene
{
    // Scene을(를) 통해 상속됨
    void Init() override;
	void Update() override;

private:
    EnemySpawnManager* _spawn;
    GameWindow* _inGameWindow;
};
