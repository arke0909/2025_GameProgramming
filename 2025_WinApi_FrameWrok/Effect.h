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
    void CreateParticle(float maxParticle, float minParticle, float maxSpeed, float minSpeed, float maxLifeTime, float minLifeTime, float maxSize, float minSize);
    void SetColor(Color color)
    {
        _color = color;
    }
    // Object을(를) 통해 상속됨
    void Update() override;
    void Render(HDC hdc) override;
private:
    Color _color;
    vector<EffectParticle*> _particles;
};

