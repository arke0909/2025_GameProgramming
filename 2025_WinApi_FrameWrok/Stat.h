#pragma once
class Stat
{
public : 
	Stat();
	Stat(float value, wstring _statName);
	~Stat();
public:
	void AddModifier(float value);
	void RemoveModifier(float value);
	wstring GetStatName()
	{
		return _statName;
	}
	float GetValue()
	{
		return _baseValue + _modifiedValue;
	}
private:
	float _baseValue = 0;
	float _modifiedValue = 0;
	wstring _statName;
};

