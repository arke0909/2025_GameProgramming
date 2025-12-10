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
    int _minParticle = 8;
    float _maxLifeTime = 1.2f;
    float _minLifeTime = 0.5f;
    float _maxSpeed = 250;
    float _minSpeed = 100;
    float _maxSize = 50;
    float _minSize = 20;
    vector<EffectParticle*> _particles;
};

