#pragma once
#include "Scene.h"
#include "UIButton.h"
#include "UIImage.h"

class TitleScene : public Scene
{
private:
    UIButton* _startBtn = nullptr;
    UIButton* _settingBtn = nullptr;
    UIButton* _exitBtn = nullptr;
    UIImage* _titleImage = nullptr;

public:
    void Init() override;
    void Release() override;
};



