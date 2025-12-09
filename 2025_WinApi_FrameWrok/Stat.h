#pragma once
class Stat
{
public : 
	Stat();
	Stat(float value, wstring _statName);
	~Stat();
public:
	void AddModifier(wstring key, float value);
	void RemoveModifier(wstring key);
	wstring GetStatName()
	{
		return _statName;
	}
	float GetValue()
	{
		return _baseValue + _modifiedValue;
	}
private:
	map<wstring, float> _modifiedMap;
	float _baseValue = 0;
	float _modifiedValue = 0;
	wstring _statName;
};