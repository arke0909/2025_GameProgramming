#include "pch.h"
#include "Stat.h"

Stat::Stat()
{
}

Stat::Stat(float value, wstring statIcon)
{
	_baseValue = value;
	_statIcon = statIcon;
}

Stat::~Stat()
{
}

void Stat::AddModifier(float value)
{
	_modifiedValue += value;
}

void Stat::RemoveModifier(float value)
{
	_modifiedValue -= value;
}
