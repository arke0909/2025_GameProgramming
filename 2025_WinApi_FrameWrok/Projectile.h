#pragma once
#include "Object.h"

class Texture;

class Projectile :
    public Object
{
public:
    Projectile();
    ~Projectile();
public:
    // Object을(를) 통해 상속됨
    void Update() override;
    void Render(HDC hdc) override;
public:
    // 인라인 함수
    void SetAngle(float angle) { _angle = angle; }
    void SetDir(Vec2 dir)
    {
        _dir = dir;
        _dir.Normalize();
    }
private:
    //float _dir;
    float _angle;
    Vec2 _dir;
    Texture* _projecTex;
};

