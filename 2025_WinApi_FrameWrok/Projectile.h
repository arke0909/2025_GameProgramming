#pragma once
#include "Object.h"

class Texture;
class Rigidbody;
class Player;

class Projectile :
    public Object
{
public:
    Projectile(int level, int splashLvl, float speed);
    ~Projectile();
public:
    // Object��(��) ���� ��ӵ�
    void Update() override;
    void Render(HDC hdc) override;
    void EnterCollision(Collider* _other) override; //�浹����
    void StayCollision(Collider* _other) override; // �浹��
    void ExitCollision(Collider* _other) override;
public:
    // �ζ��� �Լ�
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
    float _moveSpeed;
    float _wallForce;
    float _damage = 2.f;
    int _splashLvl;
    int _penetration = 1;
    Vec2 _dir;
    Texture* _projecTex;
    Rigidbody* _rigidbody;
};

