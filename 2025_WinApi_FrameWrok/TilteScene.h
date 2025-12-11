#pragma once
#include "Scene.h"
#include "UIButton.h"
#include "UIImage.h"

class TitleScene : public Scene
{
private:
	bool isSoundWindowOpen = false;
public:
    void Init() override;
};



