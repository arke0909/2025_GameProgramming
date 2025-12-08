#pragma once
#include "Scene.h"
class HPImage;
class Window;
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
    Window* _storeWindow = nullptr;
    std::vector<HPImage*> _hearts;
    bool _storeVisible = true;
};

