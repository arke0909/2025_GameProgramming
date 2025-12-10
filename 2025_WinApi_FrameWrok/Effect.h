#pragma once
#include "Object.h"

class EffectParticle;

class Effect :
    public Object
{
public:
    Effect();
    ~Effect();
public:
    void CreateParticle();
    // Object을(를) 통해 상속됨
    void Update() override;
    void Render(HDC hdc) override;
private:
    int _maxParticle = 13;
    int _minParticle = 10;
    float _maxLifeTime = 0.5f;
    float _minLifeTime = 0.2f;
    float _maxSpeed = 80;
    float _minSpeed = 50;
    float _maxSize = 30;
    float _minSize = 10;
    vector<EffectParticle*> _particles;
};

