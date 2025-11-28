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
    RECT imgRect = { 100, 100, 356, 228 };
    Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(L"Player");
    Texture* tex2 = GET_SINGLE(ResourceManager)->GetTexture(L"CloseEnemy");
    UIImage* img = new UIImage(tex, imgRect);

	GET_SINGLE(UIManager)->Add(img);

    UILabel* label = new UILabel(L"게임 스타트!", { 200, 200, 400, 240 }, FontType::TITLE);
    GET_SINGLE(UIManager)->Add(label);

	UIButton* button = new UIButton(L"클릭", { 200, 300, 300, 350 }, FontType::TITLE, tex2);

    button->SetOnClick([=]() {
        UIImage* img = new UIImage(tex, { 400, 200, 500, 400 });
        GET_SINGLE(UIManager)->Add(img);
		});
	GET_SINGLE(UIManager)->Add(button);

    UISlider* slider = new UISlider({ 100, 100, 300, 120 });
    slider->SetOnValueChanged([](float val) {
        wprintf(L"슬라이더 값: %.2f\n", val);
        });
    GET_SINGLE(UIManager)->Add(slider);



}