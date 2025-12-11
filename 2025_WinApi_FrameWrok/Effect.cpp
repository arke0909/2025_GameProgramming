#include "pch.h"
#include "Effect.h"
#include "EffectParticle.h"
#include <random>

std::uniform_int_distribution<> typedef DistributionInt;
std::uniform_real_distribution<float> typedef DistributionFloat;

Effect::Effect()
{
	
}

void Effect::CreateParticle(float maxParticle, float minParticle, float maxSpeed, float minSpeed, float maxLifeTime, float minLifeTime, float maxSize, float minSize)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	DistributionInt cntDist(minParticle, maxParticle);
	DistributionFloat speedDist(minSpeed, maxSpeed);
	DistributionFloat lifeTimeDist(minLifeTime, maxLifeTime);
	DistributionFloat sizeDist(minSize, maxSize);
	
	for (int i = 0; i < cntDist(gen); ++i)
	{
		EffectParticle* ep = new EffectParticle();
		ep->SetPos(_pos);

		srand(i * time(NULL));
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
