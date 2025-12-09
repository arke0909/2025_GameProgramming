#pragma once
#include "Object.h"
#include "IAfterInit.h"
#include "StatComponent.h"

class Rigidbody;
class Texture;
class Weapon;
class Window;
class StatComponent;

class Player :
    public Object, public IAfterInit
{
public:
    Player();
    ~Player();
public:
    // IInit을(를) 통해 상속됨 
    void AfterInit() override;
    // Object을(를) 통해 상속됨
    void Update() override;
    void Render(HDC hdc) override;
    void SetWindow(Window* inGameWindow)
    {
        _inGameWindow = inGameWindow;
    }
private:
    void EnterCollision(Collider* _other) override; //충돌진입
    void StayCollision(Collider* _other) override; // 충돌중
    void ExitCollision(Collider* _other) override;
    Weapon* CreateWeapon();
    void ShotProjectile();
private:
    Rigidbody* _rigidbody;
    StatComponent* _statCompo;
    Texture* _pTex;
    Weapon* _weapon;
    float _bulletTermAngle = 15.f;
    float _moveSpeed = 250;
    float _weaponCreateRadius = 150;
    float _lastFireTime = 0.f;
    float _circleColRadius;
    Window* _inGameWindow;
};

