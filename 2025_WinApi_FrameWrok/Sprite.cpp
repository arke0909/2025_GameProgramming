#include "pch.h"
#include "Sprite.h"
#include "Texture.h"
#include "ResourceManager.h"

// 생성자: 텍스처에서 특정 영역을 잘라 스프라이트용 DC와 비트맵을 생성
Sprite::Sprite(Texture* texture, int32 x, int32 y, int32 cx, int32 cy)
    : _texture(texture)
    , _x(x)
    , _y(y)
    , _cx(cx)
    , _cy(cy)
{
    // 원본 텍스처의 DC 얻기
    HDC textureDC = _texture->GetTextureDC();

    // 텍스처 DC와 호환되는 DC 및 비트맵 생성
    _hSpriteDC = CreateCompatibleDC(textureDC);
    _hSpriteBitmap = CreateCompatibleBitmap(textureDC, _cx, _cy);

    // 생성한 비트맵을 DC에 연결
    SelectObject(_hSpriteDC, _hSpriteBitmap);

    // 텍스처에서 스프라이트 영역만 복사 (BitBlt 사용)
    BitBlt(_hSpriteDC,           // 대상 DC
        0, 0,                 // 대상 위치
        _cx, _cy,             // 복사할 크기
        textureDC,            // 원본 DC
        _x, _y,               // 원본 위치
        SRCCOPY);             // 복사 방식
}

// 소멸자: GDI 리소스 해제
Sprite::~Sprite()
{
    DeleteObject(_hSpriteBitmap);
    DeleteDC(_hSpriteDC);
}

// 텍스처의 투명 색상값을 반환 (렌더링 시 사용)
const int32& Sprite::getTransparent()
{
    return _texture->getTransparent();
}
