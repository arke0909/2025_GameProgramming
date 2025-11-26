#pragma once
#include "Scene.h"
class PlayerDevScene :
    public Scene
{
public:
    // Scene을(를) 통해 상속됨
    void Init() override;
    void Update();
};

