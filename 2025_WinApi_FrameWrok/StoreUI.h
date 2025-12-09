#include "UIButton.h" 
#include "UILabel.h"
#include "UIButton.h" 
#include "ItemButton.h"

class StoreUI : public UIElement
{
public:
    StoreUI(const Vec2& pos, const Vec2& size);

    void Init();
    void Render(HDC hdc) override;
    void Update() override;

private:
    std::vector<ItemButton*> _itemSlots;
    UIButton* _rerollButton = nullptr;
    UILabel* _coinLabel = nullptr;

    void Reroll();
    std::vector<ItemInfo> GetRandomItems(int count);
};
