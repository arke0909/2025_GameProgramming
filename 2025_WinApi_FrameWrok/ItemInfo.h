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
    Texture* icon;
};

extern std::vector<ItemInfo> AllItems;