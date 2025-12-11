#pragma once

#include "Scene.h"
#include "GameWindow.h"
#include "Window.h"
#include "StoreUI.h"
#include "WaveLabel.h"
#include "CoinLabel.h"
#include "UIImage.h"
#include "HPImage.h"
#include "Player.h"
#include "EnemySpawnManager.h"

class GameScene : public Scene
{
private:
    GameWindow* _inGameWindow = nullptr;
    Window* _storeWindow = nullptr;
    Window* _informationWindow = nullptr;

    StoreUI* _shop = nullptr;
    WaveLabel* _waveLabel = nullptr;
    CoinLabel* _coinLabel = nullptr;
    UIImage* _heart = nullptr;
    HpLabel* _hpLabel = nullptr;
    Player* _player = nullptr;

    EnemySpawnManager* _spawn = nullptr;
    bool _storeVisible = false;

public:
    void Init() override;
    void Update() override;
    void Release() override;
};
