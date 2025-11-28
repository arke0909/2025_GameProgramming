#include "pch.h"
#include "Test.h"
#include "ResourceManager.h"
#include "UIManager.h"
#include "UIImage.h"
#include "UILabel.h"
#include "UIButton.h"
#include "UISlider.h"

void Test::Init()
{
    Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(L"Player");
    Texture* tex2 = GET_SINGLE(ResourceManager)->GetTexture(L"CloseEnemy");

    UIImage* img = new UIImage(tex, { 100,100 }, { 100,100 });
    GET_SINGLE(UIManager)->Add(img);

    UIButton* button = new UIButton(L"Play", { 400,300 }, { 100,100 }, FontType::TITLE, tex);
    button->SetOnClick([=]() {
        UIImage* img2 = new UIImage(tex, { 0,0 }, { 100,100 });
        GET_SINGLE(UIManager)->Add(img2);
        });
    GET_SINGLE(UIManager)->Add(button);

    UISlider* slider = new UISlider({ 150,450 }, { 300,20 });
    slider->SetOnValueChanged([](float val) {
        wprintf(L"슬라이더 값: %.2f\n", val);
        });
    GET_SINGLE(UIManager)->Add(slider);
}
