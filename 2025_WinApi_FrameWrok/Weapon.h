#pragma once
#include "WallForceObject.h"
class Player;
class Rigidbody;
class Texture;

class Weapon :
    public WallForceObject
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
    void AddSpeed(float value)
    {
		_moveSpeed += value;
    }
    void SizeUp(float value);
    void SetSplashLevelUp(int level)
    {
        _splashLvl += level;
	}
private:
    void CreateSplash();
private:
    Player* _player;
    Rigidbody* _rigidbody;
    float _moveSpeed = 0;
    float _currentRadius = 15;
    int _splashLvl = 0;
};

