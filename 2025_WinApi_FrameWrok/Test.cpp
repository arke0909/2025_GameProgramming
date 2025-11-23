#include "pch.h"
#include "Test.h"
#include "ResourceManager.h"
#include "UIManager.h"
#include "UIImage.h"

void Test::Init()
{
    RECT imgRect = { 100, 100, 356, 228 };
    Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(L"Test");
    UIImage* img = new UIImage(tex, imgRect);

	GET_SINGLE(UIManager)->Add(img);
}