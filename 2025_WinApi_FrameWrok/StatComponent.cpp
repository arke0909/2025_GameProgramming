#include "pch.h"
#include "StatComponent.h"
#include "Stat.h"
#include "GameEvent.h"
#include "ItemInfo.h"

StatComponent::StatComponent()
{
}

StatComponent::~StatComponent()
{
	for (auto stat : _statMap)
	{
		SAFE_DELETE(stat.second);
	}
}

void StatComponent::AddStat(ItemType key, float value)
{
	auto it = _statMap.find(key);
	if (it != _statMap.end())
		return;

	Stat* newStat = new Stat(value, key);
	_statMap.insert(std::make_pair(key, newStat));
}

Stat* StatComponent::GetStat(ItemType key)
{
	if(_statMap.find(key) != _statMap.end())
		return _statMap[key];
	return nullptr;
}

float StatComponent::GetValue(ItemType key)
{
	return GetStat(key)->GetValue();
}

void StatComponent::Init()
{
	
}

void StatComponent::LateUpdate()
{
}

void StatComponent::Render(HDC hDC)
{
}
