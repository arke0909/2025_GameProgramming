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
#include "TimeManager.h"


void TitleScene::Init()
{
    GET_SINGLE(TimeManager)->SetTimeScale(1.0f);
    GET_SINGLE(ResourceManager)->Play(L"BGM");

    Texture* buttonTex = GET_SINGLE(ResourceManager)->GetTexture(L"Button");
    Texture* titleTex = GET_SINGLE(ResourceManager)->GetTexture(L"Title");

    UIButton* startBtn = new UIButton(L"Start", { 325, 430 }, { 350, 70 }, FontType::UI, buttonTex);
    UIButton* settingBtn = new UIButton(L"Setting", { 325, 515 }, { 350, 70 }, FontType::UI, buttonTex);
    UIButton* exitBtn = new UIButton(L"Exit", { 325, 600 }, { 350, 70 }, FontType::UI, buttonTex);

    UIImage* titleImage = new UIImage(titleTex, { 325, 150 }, { 350, 250 });

    startBtn->SetOnClick([this]() {
        if (isSoundWindowOpen) return; 
        GET_SINGLE(SceneManager)->LoadScene(L"GameScene");
        });

    settingBtn->SetOnClick([this]() {
        if (isSoundWindowOpen) return; 

        isSoundWindowOpen = true;

        Texture* buttonTex = GET_SINGLE(ResourceManager)->GetTexture(L"No");
        Window* soundWindow = GET_SINGLE(WindowManager)->CreateSubWindow<Window>(
            L"SoundSetting", { {SCREEN_WIDTH / 2 + 450, SCREEN_HEIGHT / 2}, {550, 550} });

        SubUIManager* soundUI = soundWindow->GetUI();

        UIButton* exitSoundBtn = new UIButton(L"", { 510, 55 }, { 70, 70 }, FontType::UI, buttonTex);
        exitSoundBtn->SetOnClick([this, soundWindow]() {
            GET_SINGLE(WindowManager)->CloseSubWindow(soundWindow);
            isSoundWindowOpen = false;
            });

        UIImage* soundImage = new UIImage(
            GET_SINGLE(ResourceManager)->GetTexture(L"SoundPanel"),
            { 270, 280 }, { 500, 500 });

        UILabel* bgmLabel = new UILabel(L"BGM", { 450, 215 }, { 300, 300 }, FontType::UI);
        UILabel* sfxLabel = new UILabel(L"SFX", { 450, 375 }, { 300, 300 }, FontType::UI);

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

        soundUI->Add(soundImage);
        soundUI->Add(bgmLabel);
        soundUI->Add(sfxLabel);
        soundUI->Add(volumeSlider);
        soundUI->Add(sfxSlider);
        soundUI->Add(exitSoundBtn);
        });

    exitBtn->SetOnClick([]() {
        PostQuitMessage(0);
        });

    Window* titleWindow = GET_SINGLE(WindowManager)->CreateSubWindow<Window>(
        L"TitleWindow", { {SCREEN_WIDTH / 2 - 400, SCREEN_HEIGHT / 2}, {650, 650} });

    SubUIManager* titleUI = titleWindow->GetUI();
    titleUI->Add(startBtn);
    titleUI->Add(settingBtn);
    titleUI->Add(exitBtn);
    titleUI->Add(titleImage);
}
