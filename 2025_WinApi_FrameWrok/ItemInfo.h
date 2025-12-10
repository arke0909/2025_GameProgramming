#pragma once
#include "pch.h"
#include <unordered_set>

class Texture;
struct ItemInfo
{
    ItemType type;
    std::wstring displayName;
    std::wstring name;
    std::wstring description;
    int price;
    float value;
    Texture* icon;
};

extern std::vector<ItemInfo> AllItems;
extern std::unordered_set<ItemType> PurchasedItems;
extern std::unordered_map<ItemType, int> ItemPriceMap;
