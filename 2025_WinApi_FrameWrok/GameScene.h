#pragma once
#include "Scene.h"
class Window;
class HPImage;
class GameScene :
    public Scene
{
public:
    // Scene을(를) 통해 상속됨
    void Init() override;
    void Update();
private:
    Window* _inGameWindow = nullptr;
    Window* _informationWindow = nullptr;
    Window* _storeWindow = nullptr;
    std::vector<HPImage*> _hearts;
};

