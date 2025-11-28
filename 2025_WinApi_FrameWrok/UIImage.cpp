#include "pch.h"
#include "UIImage.h"
#include "Texture.h"

UIImage::UIImage(Texture* texture, const Vec2& pos, const Vec2& size)
    : UIElement(pos, size), _texture(texture)
{
}

void UIImage::Render(HDC hdc)
{
    if (!_texture || !_texture->GetTextureDC())
        return;

    RECT rc = GetRect();

    TransparentBlt(
        hdc,
        rc.left,
        rc.top,
        rc.right - rc.left,
        rc.bottom - rc.top,
        _texture->GetTextureDC(),
        0, 0,
        _texture->GetWidth(),
        _texture->GetHeight(),
        RGB(255, 0, 255) 
    );
}
