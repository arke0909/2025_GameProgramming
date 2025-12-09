#include "pch.h"
#include "HPImage.h"
#include "GameManager.h"

HpLabel::HpLabel(const Vec2& pos, const Vec2& size, FontType fontType)
    : UILabel(L"", pos, size, fontType)
{
    SetColor(RGB(255, 255, 255));
}

void HpLabel::Update()
{
    UILabel::Update();
    int hp = GET_SINGLE(GameManager)->playerHealth;

    std::wstringstream ss;
    ss << L"x " <<hp;

    SetText(ss.str());
}
