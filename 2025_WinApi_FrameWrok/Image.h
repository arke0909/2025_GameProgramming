#pragma once
#include "UI.h"
class Sprite;
class Image : public UI
{
public:
	Image(Sprite* sprite);
	~Image();
public:
	void Update() override;
	void Render(HDC hDC) override;
public:
	void SetSprite(Sprite* sprite);
};

