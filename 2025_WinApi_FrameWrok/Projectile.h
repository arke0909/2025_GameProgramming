#pragma once
#include "Object.h"

class Texture;
class Rigidbody;
class Player;

class Projectile :
    public Object
{
public:
    Projectile(int level, int splashLvl);
    ~Projectile();
public:
    // Object을(를) 통해 상속됨
    void Update() override;
    void Render(HDC hdc) override;
    void EnterCollision(Collider* _other) override; //충돌진입
    void StayCollision(Collider* _other) override; // 충돌중
    void ExitCollision(Collider* _other) override;
public:
    // 인라인 함수
    void SetAngle(float angle) { _angle = angle; }
    void SetWallForce(float wallForce) { _wallForce = wallForce; }
    void SetPenetration(int penetration) { _penetration = penetration; }
    void SetDir(Vec2 dir)
    {
        _dir = dir;
        _dir.Normalize();
    }
    float GetWallForce() { return _wallForce; }
    void Init(Vec2 pos, Vec2 dir);
private:
    void CreateSplash();
private:
    float _angle;
    float _moveSpeed = 800;
    float _wallForce;
    float _damage = 2.f;
    int _splashLvl;
    int _penetration = 1;
    Vec2 _dir;
    Texture* _projecTex;
    Rigidbody* _rigidbody;
};

