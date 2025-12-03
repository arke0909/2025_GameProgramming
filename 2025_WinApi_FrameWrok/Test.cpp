#include "pch.h"
#include "Test.h"
#include "ResourceManager.h"
#include "UIManager.h"
#include "UIImage.h"
#include "UILabel.h"
#include "UIButton.h"
#include "UISlider.h"
#include "WindowManager.h"

void Test::Init()
{
    Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(L"Player");
    Texture* tex2 = GET_SINGLE(ResourceManager)->GetTexture(L"Button");

    UIImage* img = new UIImage(tex, { 100,100 }, { 100,100 });
    GET_SINGLE(UIManager)->Add(img);

    UIButton* button = new UIButton(L"Play", { 400,300 }, { 180,55 }, FontType::TITLE, tex2);

  

    GET_SINGLE(UIManager)->Add(button);

    button->SetOnClick([=]() 
        {
            cout << "버튼클릭됨" << "\n";
        });

   

    UISlider* slider = new UISlider({ 150,450 }, { 300,20 });
    slider->SetOnValueChanged([](float val) {
        wprintf(L"슬라이더 값: %.2f\n", val);
        });
    GET_SINGLE(UIManager)->Add(slider);

   GET_SINGLE(WindowManager)
    ->CreateSubWindow(
        L"Temp",
        {
            {SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2 -200},
            {400,400}
        });
}
