#include "pch.h"
#include "TilteScene.h"
#include "WindowManager.h"
#include "Window.h"
#include "UIButton.h"
#include "UISlider.h"
#include "UIImage.h"
#include "UILabel.h"
#include "ResourceManager.h"
#include "SubUIManager.h"
#include "UIManager.h"
#include "SceneManager.h"

void TitleScene::Init()
{
    GET_SINGLE(ResourceManager)->Play(L"BGM");
    Texture* buttonTex = GET_SINGLE(ResourceManager)->GetTexture(L"Button");
    UIButton* startBtn = new UIButton(L"Start", { 325, 430 }, { 350, 70 }, FontType::UI, buttonTex);
    UIButton* settingBtn = new UIButton(L"Setting", { 325, 515 }, { 350, 70 }, FontType::UI, buttonTex);
    UIButton* exitBtn = new UIButton(L"Exit", { 325, 600 }, { 350, 70 }, FontType::UI, buttonTex);

    startBtn->SetOnClick([]()
        {
            GET_SINGLE(SceneManager)->LoadScene(L"GameScene");
        });

    settingBtn->SetOnClick([]()
        {
            Texture* buttonTex = GET_SINGLE(ResourceManager)->GetTexture(L"Button");
            Window* soundWindow = GET_SINGLE(WindowManager)->CreateSubWindow<Window>(
                L"SoundSetting", { {SCREEN_WIDTH / 2 + 450, SCREEN_HEIGHT / 2}, {550,550} });

            SubUIManager* soudUI = soundWindow->GetUI();
            UIButton* exitsoundBtn = new UIButton(L"닫기", { 325, 450 }, { 350, 70 }, FontType::UI, buttonTex);
            exitsoundBtn->SetOnClick([soundWindow]() {
                GET_SINGLE(WindowManager)->CloseSubWindow(soundWindow);
                });

            UIImage* soundImage = new UIImage(
                GET_SINGLE(ResourceManager)->GetTexture(L"SoundPanel"),
                { 270, 280 }, { 500, 500 });

            UILabel* bgmLabel = new UILabel(L"BGM", { 450, 215 }, { 300,300 }, FontType::UI);
            UILabel* sfxLabel = new UILabel(L"SFX", { 450, 375 }, { 300,300 }, FontType::UI);

            bgmLabel->SetColor(RGB(0, 0, 0));
            sfxLabel->SetColor(RGB(0, 0, 0));

            UISlider* volumeSlider = new UISlider({ 265, 215 }, { 300, 20 });
            volumeSlider->SetOnValueChanged([](float val) {
                GET_SINGLE(ResourceManager)->Volume(SOUND_CHANNEL::BGM, val);
                });

            UISlider* sfxSlider = new UISlider({ 265, 375 }, { 300, 20 });
            sfxSlider->SetOnValueChanged([](float val) {
                GET_SINGLE(ResourceManager)->Volume(SOUND_CHANNEL::EFFECT, val);
                });

            soudUI->Add(soundImage);
            soudUI->Add(bgmLabel);
            soudUI->Add(sfxLabel);
            soudUI->Add(volumeSlider);
            soudUI->Add(sfxSlider);
        });
    exitBtn->SetOnClick([]()
        {
            PostQuitMessage(0);
        });

    Window* TitleWindow = GET_SINGLE(WindowManager)->CreateSubWindow<Window>(
        L"TilteWindow", { {SCREEN_WIDTH / 2 - 400, SCREEN_HEIGHT / 2 }, {650,650} });
    SubUIManager* tilteUI = TitleWindow->GetUI();
    tilteUI->Add(startBtn);
    tilteUI->Add(settingBtn);
    tilteUI->Add(exitBtn);



}