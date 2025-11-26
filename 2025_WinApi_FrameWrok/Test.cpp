#include "pch.h"
#include "Test.h"
#include "ResourceManager.h"
#include "UIManager.h"
#include "UIImage.h"
#include "UILabel.h"
#include "UIButton.h"

void Test::Init()
{
    RECT imgRect = { 100, 100, 356, 228 };
    Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(L"Test");
    UIImage* img = new UIImage(tex, imgRect);

	GET_SINGLE(UIManager)->Add(img);

    UILabel* label = new UILabel(L"게임 스타트!", { 200, 200, 400, 240 }, FontType::TITLE);
    GET_SINGLE(UIManager)->Add(label);

	UIButton* button = new UIButton(L"클릭", { 200, 300, 300, 350 }, FontType::TITLE, tex);

    button->SetOnClick([=]() {
        UIImage* img = new UIImage(tex, { 400, 200, 500, 400 });
        GET_SINGLE(UIManager)->Add(img);
		});
	GET_SINGLE(UIManager)->Add(button);

}