#pragma once
#include "Object.h"
#include <random>

class EffectParticle;

class Effect :
    public Object
{
public:
    Effect();
    ~Effect();
public:
    void CreateParticle(int maxParticle, int minParticle, float maxSpeed, float minSpeed, float maxLifeTime, float minLifeTime, float maxSize, float minSize);
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
    static std::random_device rd;
    static std::mt19937 gen;
};

