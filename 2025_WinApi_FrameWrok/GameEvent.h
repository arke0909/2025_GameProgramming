#pragma once
#include "Action.h"
#include "ItemInfo.h"

namespace GameEvents
{
    inline Event<const ItemInfo&> OnItemPurchased;
}
