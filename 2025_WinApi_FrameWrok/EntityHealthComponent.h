#pragma once
#include "Component.h"
class EntityHealthComponent :
    public Component
{
public:
    EntityHealthComponent();
	~EntityHealthComponent() override;

public:
    // Component을(를) 통해 상속됨
    void Init() override {};
    void LateUpdate() override {};
    void Render(HDC hDC) override {};

	void SetHealth(int hp);
    void ApplyHPScale(float multiplier);
    void UpdateHP(int value);
    int GetCurrentHP();
    int GetMaxHP();

private:
    int _currentHP;
    int _maxHP;

};
