#include "pch.h"
#include "UIImage.h"
#include "Texture.h"

UIImage::UIImage(Texture* texture, RECT rect)
    : UIElement(rect), _texture(texture) {
}

void UIImage::Render(HDC hdc) {
    if (!_texture || !_texture->GetTextureDC()) return;

    BitBlt(hdc, _rect.left, _rect.top,
        _rect.right - _rect.left, _rect.bottom - _rect.top,
        _texture->GetTextureDC(), 0, 0, SRCCOPY);
}


