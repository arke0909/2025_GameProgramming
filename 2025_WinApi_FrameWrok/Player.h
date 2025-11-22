#pragma once
#include "Object.h"
class Rigidbody;
class Texture;

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
    Rigidbody* _rigidBody;
    Texture* _pTex;
    float _moveSpeed = 150;
};

