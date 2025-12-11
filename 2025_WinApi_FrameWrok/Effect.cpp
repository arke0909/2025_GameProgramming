#include "pch.h"
#include "Effect.h"
#include "EffectParticle.h"
#include <random>

std::uniform_int_distribution<> typedef DistributionInt;
std::uniform_real_distribution<float> typedef DistributionFloat;

Effect::Effect()
{
	
}

void Effect::CreateParticle()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	DistributionInt cntDist(_minParticle, _maxParticle);
	DistributionFloat speedDist(_minSpeed, _maxSpeed);
	DistributionFloat lifeTimeDist(_minLifeTime, _maxLifeTime);
	DistributionFloat sizeDist(_minSize, _maxSize);
	
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
