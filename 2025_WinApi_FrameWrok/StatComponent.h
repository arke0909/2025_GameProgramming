#pragma once
#include "Component.h"

class Stat;

class StatComponent :
    public Component
{
public:
    StatComponent();
    ~StatComponent();
public:
    // Component을(를) 통해 상속됨
    void Init() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void AddStat(wstring key, float value);
    Stat* GetStat(wstring key);
    float GetValue(wstring key);
private:
    map<wstring, Stat*> _statMap;

};