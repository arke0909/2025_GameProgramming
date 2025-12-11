#pragma once

#include "Scene.h"
#include "GameWindow.h"
#include "Window.h"
#include "EnemySpawnManager.h"

class GameScene : public Scene
{
private:
    GameWindow* _inGameWindow = nullptr;
    Window* _storeWindow = nullptr;
    Window* _informationWindow = nullptr;

    EnemySpawnManager* _spawn = nullptr;
    bool _storeVisible = false;

public:
    void Init() override;
    void Update() override;
};
