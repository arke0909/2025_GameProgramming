#pragma once
#include "Object.h"
class EffectParticle :
	public Object
{
public:
	EffectParticle();
	~EffectParticle();
public:
	// Object을(를) 통해 상속됨
	void Update() override;
	void Render(HDC hdc) override;
	void Init(Vec2 dir, float speed, float lifeTime, float targetRadius)
	{
		_dir = dir;
		_speed = speed;
		_lifeTime = lifeTime;
		_targetRadius = targetRadius;
	}
private:
	Vec2 _dir;
	float _speed;
	float _lifeTime;
	float _timer = 0;
	float _ease;
	float _currentRadius;
	float _targetRadius;
};

