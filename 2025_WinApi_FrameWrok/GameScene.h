#pragma once
#include "Scene.h"
class HPImage;
class GameWindow;

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
    std::vector<HPImage*> _hearts;
};

