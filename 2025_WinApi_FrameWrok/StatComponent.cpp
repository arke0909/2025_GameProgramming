#include "pch.h"
#include "StatComponent.h"
#include "Stat.h"
#include "GameEvent.h"

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

void StatComponent::AddStat(wstring key, float value)
{
	Stat* newStat = new Stat(value, key);
	_statMap.insert(std::make_pair(key, newStat));
}

Stat* StatComponent::GetStat(wstring key)
{
	return _statMap[key];
}

float StatComponent::GetValue(wstring key)
{
	return GetStat(key)->GetValue();
}

void StatComponent::Init()
{
	GameEvents::OnItemPurchased
		.Subscribe([this](const ItemInfo& item)
			{
				if (_statMap.find(item.name) != _statMap.end())
				{
					_statMap[item.name]->AddModifier(L"e", item.value);
				}
			});
}

void StatComponent::LateUpdate()
{
}

void StatComponent::Render(HDC hDC)
{
}
