#include "pch.h"
#include "Stat.h"
#include "ItemInfo.h"

Stat::Stat()
{
}

Stat::Stat(float value, ItemType statIcon)
{
	_baseValue = value;
}

Stat::~Stat()
{
}

void Stat::AddModifier(ItemType key, float value)
{
	_modifiedMap.insert({ key, value });
	_modifiedValue += value;
}

void Stat::RemoveModifier(ItemType key)
{
	float value = _modifiedMap[key];
	_modifiedValue -= value;
	_modifiedMap.erase(key);
}