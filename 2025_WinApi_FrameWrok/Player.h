#pragma once
#include "Object.h"
class Rigidbody;
class Texture;
class Weapon;

class Player :
    public Object
{
public:
    Player();
    ~Player();
public:
    // Object을(를) 통해 상속됨
    void Update() override;
    void Render(HDC hdc) override;
private:
    void EnterCollision(Collider* _other) override; //충돌진입
    void StayCollision(Collider* _other) override; // 충돌중
    void ExitCollision(Collider* _other) override;
    Weapon* CreateWeapon();
    void ShotProjectile();
private:
    Rigidbody* _rigidbody;
    Texture* _pTex;
    Weapon* _weapon;
    float _moveSpeed = 250;
    float _weaponCreateRadius = 150;
    float _fireInterval = 1.5f;
    float _lastFireTime = 0.f;
};

