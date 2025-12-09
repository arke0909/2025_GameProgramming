#pragma once
#include "pch.h"

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