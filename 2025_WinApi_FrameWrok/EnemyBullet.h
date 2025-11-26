#pragma once
#include "Object.h"
class EnemyBullet
	: public Object
{
public:
	EnemyBullet();
	~EnemyBullet();
	// Object을(를) 통해 상속됨
	void Update() override;
	void Render(HDC hdc) override;
};

