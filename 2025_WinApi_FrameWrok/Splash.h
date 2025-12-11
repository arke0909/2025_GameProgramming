#pragma once
#include "Object.h"

class CircleCollider;

class Splash :
    public Object
{
public:
    Splash(int level);
    ~Splash();
public:
    // Object을(를) 통해 상속됨
    void Update() override;
    void Render(HDC hdc) override;
    void EnterCollision(Collider* _other) override; //충돌진입
    void StayCollision(Collider* _other) override; // 충돌중
    void ExitCollision(Collider* _other) override;
private:
    float _currentRadius = 0;
    float _targetRadius = 60.f;
    float _lvlPerRadius = 30.f;
    float _timer = 0;
    float _duration = 0.5f;
    float _ease;
    float _damage;
    CircleCollider* _cirCol;
};

