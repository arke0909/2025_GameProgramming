#pragma once
#include "Scene.h"
class HpLabel;
class Window;
class GameWindow;
class EnemySpawnManager;

class GameScene :
    public Scene
{
public:
    // Scene��(��) ���� ��ӵ�
    void Init() override;
    void Update();
private:
    GameWindow* _inGameWindow;
    Window* _informationWindow = nullptr;
    Window* _storeWindow = nullptr;
    EnemySpawnManager* _spawn;
    bool _storeVisible = true;
};

