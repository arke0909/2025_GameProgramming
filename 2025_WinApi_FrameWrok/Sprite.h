#pragma once

#include "ResourceBase.h"

class Texture;

// 스프라이트 클래스: 텍스처에서 특정 영역을 잘라낸 후, 별도의 DC와 비트맵으로 관리
class Sprite : public ResourceBase
{
public:
    // 생성자: Texture에서 (x, y) 위치에서 (cx, cy) 크기만큼 잘라서 스프라이트 생성
    Sprite(Texture* texture, int32 x, int32 y, int32 cx, int32 cy);
    ~Sprite(); // 소멸자: 리소스 정리

public:
    // 스프라이트의 DC (렌더링할 때 필요)
    const HDC& getSpriteDC() { return _hSpriteDC; }

    // 스프라이트 비트맵 객체
    const HBITMAP& getSpriteBitmap() { return _hSpriteBitmap; }

    // 원래 텍스처에서 잘라낸 시작 좌표
    const Vector2& getPosition() { return Vector2(_x, _y); }

    // 스프라이트의 크기
    const Vector2& getSize() { return Vector2(_cx, _cy); }

    // 투명 색상 반환 (Texture 객체에서 가져옴)
    const int32& getTransparent();

    // 스프라이트 시작 좌표 설정
    void setPosition(Vector2 pos) { _x = pos.x; _y = pos.y; }

    // 스프라이트 크기 설정
    void setSize(Vector2 size) { _cx = size.x; _cy = size.y; } 

private:
    Texture* _texture = nullptr;   // 원본 텍스처

    // 텍스처에서 잘라낼 위치와 크기
    int32 _x;
    int32 _y;
    int32 _cx;
    int32 _cy;

    // 잘라낸 스프라이트를 저장할 비트맵과 DC
    HBITMAP _hSpriteBitmap = nullptr;
    HDC _hSpriteDC = nullptr;
};
