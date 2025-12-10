#pragma once
#include "EnemyState.h"
class EnemyMeleeAttackState :
    public EnemyState
{
public:
    EnemyMeleeAttackState(Enemy* owner, std::wstring animationName);
	~EnemyMeleeAttackState() override;

public:
    void Enter() override;
    void Update() override;
	void Exit() override;


    void Attack();
private:
    float _coolTime;
    float _currentTime;

	bool _isAttack;

    void Render(HDC hdc) override {};
};
