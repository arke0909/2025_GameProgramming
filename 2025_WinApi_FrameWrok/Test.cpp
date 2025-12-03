#include "pch.h"
#include "Test.h"
#include "ResourceManager.h"
#include "UIManager.h"
#include "UIButton.h"
#include "UIImage.h"
#include "UISlider.h"
#include "WindowManager.h"
#include "Window.h"
#include "SubUIManager.h"

void Test::Init()
{
    Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(L"Player");
    Texture* buttonTex = GET_SINGLE(ResourceManager)->GetTexture(L"Button");


    UIImage* img = new UIImage(tex, { 100,100 }, { 100,100 });
    GET_SINGLE(UIManager)->Add(img);

    UIButton* mainButton = new UIButton(L"Open Window", { 400,300 }, { 180,55 }, FontType::TITLE, buttonTex);
    GET_SINGLE(UIManager)->Add(mainButton);

    mainButton->SetOnClick([=]()
        {
            Window* sub = GET_SINGLE(WindowManager)->CreateSubWindow(L"SubWindow", { {600, 400}, {800, 800} });

            SubUIManager* subUI = sub->GetUI();

            UISlider* slider = new UISlider({ 50, 50 }, { 300, 20 });
            slider->SetOnValueChanged([](float val) {
                wprintf(L"[Sub] 슬라이더 값: %.2f\n", val);
                });
            subUI->Add(slider);

            UIButton* subBtn = new UIButton(L"Click Me", { 100, 100 }, { 180, 55 }, FontType::TITLE, buttonTex);
            subBtn->SetOnClick([]() {
                MessageBox(nullptr, L"서브 창 버튼 클릭됨!", L"Sub UI", MB_OK);
                });
            subUI->Add(subBtn);
        });

    UISlider* mainSlider = new UISlider({ 150, 450 }, { 300, 20 });
    mainSlider->SetOnValueChanged([](float val) {
        wprintf(L"[Main] 슬라이더 값: %.2f\n", val);
        });
    GET_SINGLE(UIManager)->Add(mainSlider);
}
