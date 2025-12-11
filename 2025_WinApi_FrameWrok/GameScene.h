#pragma once
#include "Scene.h"

class Window;
class StoreUI;
class WaveLabel;
class CoinLabel;
class UIImage;
class HpLabel;
class Player;
class EnemySpawnManager;

class GameScene : public Scene
{
private:
    Window* _inGameWindow = nullptr;
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
