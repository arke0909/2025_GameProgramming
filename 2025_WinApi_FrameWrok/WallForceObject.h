#pragma once
#include "Object.h"

class WallForceObject :
    public Object
{
    // Object을(를) 통해 상속됨
    void Update() override;
    void Render(HDC hdc) override;

public:
    void SetWallForce(float wallForce) { _wallForce = wallForce; }
    float GetWallForce() { return _wallForce; }
protected:
    float _wallForce;
};

