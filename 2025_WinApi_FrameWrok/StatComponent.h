#pragma once
#include "Component.h"
enum class ItemType;

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
    void AddStat(ItemType key, float value);
    Stat* GetStat(ItemType key);
    float GetValue(ItemType key);
private:
    map<ItemType, Stat*> _statMap;

};