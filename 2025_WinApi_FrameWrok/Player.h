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
    Weapon* CreateWeapon();
    void ShotProjectile();
private:
    Rigidbody* _rigidbody;
    Texture* _pTex;
    Weapon* _weapon;
    float _moveSpeed = 150;
    float _weaponCreateRadius = 150;
    float _fireInterval = 1.5f;
    float _lastFireTime = 0.f;
};

