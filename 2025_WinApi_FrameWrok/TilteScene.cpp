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

    auto startBtn = std::make_unique<UIButton>(L"Start", Vec2{ 325, 430 }, Vec2{ 350, 70 }, FontType::UI, buttonTex);
    auto settingBtn = std::make_unique<UIButton>(L"Setting", Vec2{ 325, 515 }, Vec2{ 350, 70 }, FontType::UI, buttonTex);
    auto exitBtn = std::make_unique<UIButton>(L"Exit", Vec2{ 325, 600 }, Vec2{ 350, 70 }, FontType::UI, buttonTex);

    auto titleImage = std::make_unique<UIImage>(titleTex, Vec2{ 325, 150 }, Vec2{ 350, 250 });

    startBtn->SetOnClick([this]()
        {
            if (isSoundWindowOpen) return;
            GET_SINGLE(SceneManager)->LoadScene(L"GameScene");
        });

    settingBtn->SetOnClick([this]()
        {
            if (isSoundWindowOpen) return;
            isSoundWindowOpen = true;

            Texture* noTex = GET_SINGLE(ResourceManager)->GetTexture(L"No");

            Window* soundWindow =
                GET_SINGLE(WindowManager)->CreateSubWindow<Window>(
                    L"SoundSetting",
                    { { SCREEN_WIDTH / 2 + 450, SCREEN_HEIGHT / 2 }, { 550, 550 } }
                );

            SubUIManager* soundUI = soundWindow->GetUI();

            auto exitSoundBtn = std::make_unique<UIButton>(
                L"", Vec2{ 510, 55 }, Vec2{ 70, 70 }, FontType::UI, noTex
            );

            exitSoundBtn->SetOnClick([this, soundWindow]()
                {
                    GET_SINGLE(WindowManager)->CloseSubWindow(soundWindow);
                    isSoundWindowOpen = false;
                });

            auto soundImage = std::make_unique<UIImage>(
                GET_SINGLE(ResourceManager)->GetTexture(L"SoundPanel"),
                Vec2{ 270, 280 }, Vec2{ 500, 500 }
            );

            auto bgmLabel = std::make_unique<UILabel>(L"BGM", Vec2{ 450, 215 }, Vec2{ 300, 300 }, FontType::UI);
            auto sfxLabel = std::make_unique<UILabel>(L"SFX", Vec2{ 450, 375 }, Vec2{ 300, 300 }, FontType::UI);

            bgmLabel->SetColor(RGB(0, 0, 0));
            sfxLabel->SetColor(RGB(0, 0, 0));

            auto volumeSlider = std::make_unique<UISlider>(Vec2{ 265, 215 }, Vec2{ 300, 20 });
            volumeSlider->SetOnValueChanged([](float v)
                {
                    GET_SINGLE(ResourceManager)->Volume(SOUND_CHANNEL::BGM, v);
                });

            auto sfxSlider = std::make_unique<UISlider>(Vec2{ 265, 375 }, Vec2{ 300, 20 });
            sfxSlider->SetOnValueChanged([](float v)
                {
                    GET_SINGLE(ResourceManager)->Volume(SOUND_CHANNEL::EFFECT, v);
                });

            soundUI->Add(std::move(soundImage));
            soundUI->Add(std::move(bgmLabel));
            soundUI->Add(std::move(sfxLabel));
            soundUI->Add(std::move(volumeSlider));
            soundUI->Add(std::move(sfxSlider));
            soundUI->Add(std::move(exitSoundBtn));
        });


    exitBtn->SetOnClick([]()
        {
            GET_SINGLE(WindowManager)->CloseAllSubWindows();
            PostQuitMessage(0);
        });

    Window* titleWindow =
        GET_SINGLE(WindowManager)->CreateSubWindow<Window>(
            L"TitleWindow",
            { { SCREEN_WIDTH / 2 - 400, SCREEN_HEIGHT / 2 }, { 650, 650 } }
        );

    SubUIManager* titleUI = titleWindow->GetUI();

    titleUI->Add(std::move(startBtn));
    titleUI->Add(std::move(settingBtn));
    titleUI->Add(std::move(exitBtn));
    titleUI->Add(std::move(titleImage));
}

