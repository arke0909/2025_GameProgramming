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
#include "SceneManager.h"

void TitleScene::Init()
{
	GET_SINGLE(ResourceManager)->Play(L"BGM");
    Texture* buttonTex = GET_SINGLE(ResourceManager)->GetTexture(L"Button");

    Window* startWindow = GET_SINGLE(WindowManager)->CreateSubWindow(
        L"Start Window", { {300, 300}, {220, 100} });
    SubUIManager* startUI = startWindow->GetUI();

    UIButton* startBtn = new UIButton(L"게임 시작", { 110, 50 }, { 200, 75 }, FontType::TITLE, buttonTex);
    startBtn->SetOnClick([]() 
        {
            GET_SINGLE(WindowManager)->CloseAllSubWindows();
            GET_SINGLE(SceneManager)->LoadScene(L"PlayerDevScene");
        });
    startUI->Add(startBtn);

    Window* soundWindow = GET_SINGLE(WindowManager)->CreateSubWindow(
        L"Sound Settings", { {900, 500}, {550,550} });
    SubUIManager* soundUI = soundWindow->GetUI();
    
    UIImage* soundImage = new UIImage(
        GET_SINGLE(ResourceManager)->GetTexture(L"SoundPanel"),
		{270, 280 }, { 500, 500 });

    UILabel* bgmLabel = new UILabel(L"BGM", { 450, 215 }, { 300,300 }, FontType::TITLE);
    UILabel* sfxLabel = new UILabel(L"SFX", { 450, 375 }, { 300,300 }, FontType::TITLE);

    UISlider* volumeSlider = new UISlider({ 265, 215 }, { 300, 20 });
    volumeSlider->SetOnValueChanged([](float val) {
        GET_SINGLE(ResourceManager)->Volume(SOUND_CHANNEL::BGM, val);
        });

    UISlider* sfxSlider = new UISlider({ 265, 375 }, { 300, 20 });
    sfxSlider->SetOnValueChanged([](float val) {
        GET_SINGLE(ResourceManager)->Volume(SOUND_CHANNEL::EFFECT, val);
        });

	soundUI->Add(soundImage);
    soundUI->Add(volumeSlider);
    soundUI->Add(sfxSlider);
	soundUI->Add(bgmLabel);
	soundUI->Add(sfxLabel);
}