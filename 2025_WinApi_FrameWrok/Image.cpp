#include "pch.h"
#include "Image.h"
#include "SpriteRenderer.h"

Image::Image(Sprite* sprite)
{
	SpriteRenderer* spriteRenderer = AddComponent<SpriteRenderer>();
	spriteRenderer->setSprite(sprite);
}

Image::~Image()
{
}

void Image::Update()
{
}

void Image::Render(HDC hDC)
{
	ComponentRender(hDC);
}

void Image::SetSprite(Sprite* sprite)
{
	GetComponent<SpriteRenderer>()->setSprite(sprite);
}
