#pragma once
enum class ItemType;

class Stat
{
public:
	Stat();
	Stat(float value, ItemType _statName);
	~Stat();
public:
	void AddModifier(ItemType key, float value);
	void RemoveModifier(ItemType key);
	ItemType GetStatType()
	{
		return _type;
	}
	float GetValue()
	{
		return _baseValue + _modifiedValue;
	}
	int GetModifyCnt()
	{
		return _modifiedMap.size();
	}
private:
	map<ItemType, float> _modifiedMap;
	float _baseValue = 0;
	float _modifiedValue = 0;
	ItemType _type;
};