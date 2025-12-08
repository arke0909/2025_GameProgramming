#include "pch.h"
#include "Stat.h"

Stat::Stat()
{
}

Stat::Stat(float value, wstring statIcon)
{
	_baseValue = value;
	_statName = statIcon;
}

Stat::~Stat()
{
}

void Stat::AddModifier(wstring key, float value)
{
	_modifiedMap.insert({ key, value });
	_modifiedValue += value;
}

void Stat::RemoveModifier(wstring key)
{
	float value = _modifiedMap[key];
	_modifiedValue -= value;
}