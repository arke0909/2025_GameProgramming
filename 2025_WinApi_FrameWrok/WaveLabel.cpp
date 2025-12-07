#include "pch.h"
#include "WaveLabel.h"
#include "GameManager.h"

WaveLabel::WaveLabel(const Vec2& pos, const Vec2& size, FontType fontType)
    : UILabel(L"", pos, size, fontType)  
{
    SetColor(RGB(255, 255, 255)); 
}

void WaveLabel::Update()
{
    UILabel::Update();
    int wave = GET_SINGLE(GameManager)->currentWavwe;

    std::wstringstream ss;
    ss << L"Wave : " << wave;

    SetText(ss.str());
}
