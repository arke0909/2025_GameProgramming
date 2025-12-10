#include "pch.h"
#include "EntityHealthComponent.h"

EntityHealthComponent::EntityHealthComponent()
	: _currentHP(0),
	_maxHP(0)
{
}

EntityHealthComponent::~EntityHealthComponent()
{
}

void EntityHealthComponent::SetHealth(int hp)
{
    _maxHP = _currentHP = hp;
}

void EntityHealthComponent::ApplyHPScale(float multiplier)
{
    _maxHP = static_cast<int>(_maxHP * multiplier);
    _currentHP = _maxHP;
}

void EntityHealthComponent::UpdateHP(int value)
{
    _currentHP += value;
    if (_currentHP < 0)
        _currentHP = 0;
    if (_currentHP > _maxHP)
        _currentHP = _maxHP;
}

int EntityHealthComponent::GetCurrentHP()
{
    return _currentHP;
}

int EntityHealthComponent::GetMaxHP()
{
	return _maxHP;
}
