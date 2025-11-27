#pragma once
#include "Object.h"
class Player;
class Rigidbody;
class Texture;

class Weapon :
    public Object
{
public:
    Weapon();
    ~Weapon();
public:
    // Object을(를) 통해 상속됨
    void Update() override;
    void Render(HDC hdc) override;
    void EnterCollision(Collider* _other) override; //충돌진입
    void StayCollision(Collider* _other) override; // 충돌중
    void ExitCollision(Collider* _other) override;
    void PullWeapon();
    void SetPlayer(Player* player)
    {
        _player = player;
    }
private:
    Player* _player;
    Rigidbody* _rigidbody;
    Texture* _wTex;
    float _moveSpeed = 475;
};

