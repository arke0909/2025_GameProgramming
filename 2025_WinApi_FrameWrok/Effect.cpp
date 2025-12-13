#include "pch.h"
#include "Effect.h"
#include "EffectParticle.h"

using DistributionInt = std::uniform_int_distribution<>;
using DistributionFloat = std::uniform_real_distribution<float>;



Effect::Effect() : gen(rd())
{
	
}

void Effect::CreateParticle(int maxParticle, int minParticle, float maxSpeed, float minSpeed, float maxLifeTime, float minLifeTime, float maxSize, float minSize)
{
	DistributionInt cntDist(minParticle, maxParticle);
	DistributionFloat speedDist(minSpeed, maxSpeed);
	DistributionFloat lifeTimeDist(minLifeTime, maxLifeTime);
	DistributionFloat sizeDist(minSize, maxSize); 
	srand(time(NULL));
	
	for (int i = 0; i < cntDist(gen); ++i)
	{
		EffectParticle* ep = new EffectParticle();
		ep->SetPos(_pos);

		float angle = (rand() % 360) * PI / 180.f;
		float x = ::cos(angle);
		float y = ::sin(angle);

		Vec2 dir = { x,y };
		ep->Init(dir, speedDist(gen), lifeTimeDist(gen), sizeDist(gen));
		ep->SetColor(_color);
		_particles.push_back(ep);
	}
}

Effect::~Effect()
{
	for (auto* particle : _particles)
	{
		SAFE_DELETE(particle);
	}
}

void Effect::Update()
{
	bool isNotEnd = false;
	for (auto* particle : _particles)
	{
		if (!particle->GetIsDead())
		{
			particle->Update();
			isNotEnd = true;
		}
	}
	if (!isNotEnd)
		SetDead();
}

void Effect::Render(HDC hdc)
{
	for (auto* particle : _particles)
	{
		particle->Render(hdc);
	}
}
