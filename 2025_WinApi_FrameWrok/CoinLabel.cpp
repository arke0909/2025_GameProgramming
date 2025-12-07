#include "pch.h"
#include "CoinLabel.h"
#include "GameManager.h"

CoinLabel::CoinLabel(const Vec2& pos, const Vec2& size, FontType fontType)
    : UILabel(L"", pos, size, fontType)
{
    SetColor(RGB(255, 255, 255));
}

void CoinLabel::Update()
{
    UILabel::Update();
    int wave = GET_SINGLE(GameManager)->coin;

    std::wstringstream ss;
    ss << L"COIN : " << wave;

    SetText(ss.str());
}