#pragma once
#include "Scene.h"
class GameWindow;

class GameScene :
    public Scene
{
public:
    // Scene을(를) 통해 상속됨
    void Init() override;
    void Update();
private:
    GameWindow* _inGameWindow;
};

