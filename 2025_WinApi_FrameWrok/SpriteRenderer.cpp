// SpriteRenderer.cpp

#include "pch.h"
#include "Object.h"
#include "SpriteRenderer.h"
#include "Core.h"
#include "Sprite.h"
#include <format>

SpriteRenderer::SpriteRenderer()
    : _sprite(nullptr)
    , _scale{ 1,1 }      // 기본 스케일은 1 (크기 그대로)
    , _offset{ 0, 0 }    // 오프셋은 기본적으로 없음
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::LateUpdate()
{
    // 현재는 특별히 처리하는 로직 없음
}

void SpriteRenderer::Render(HDC hDC)
{
    // 스프라이트가 없으면 그리지 않음
    if (_sprite == nullptr) return;

    // 오브젝트의 현재 위치 가져오기
    Vector2 pos = GetOwner()->GetPos();

    // 원본 스프라이트의 크기
    Vector2 size = _sprite->getSize();

    // 스케일 적용된 실제 렌더링 크기 계산
    Vector2 scaledSize = _scale * _sprite->getSize();

    // GDI의 TransparentBlt 함수로 스프라이트를 화면에 그리기
    TransparentBlt(
        hDC,                                          // DC (Device Context)
        pos.x - scaledSize.x / 2 + _offset.x,         // 화면에 그릴 X 좌표 (중앙 정렬 + 오프셋)
        pos.y - scaledSize.y / 2 + _offset.y,         // 화면에 그릴 Y 좌표
        scaledSize.x, scaledSize.y,                   // 확대/축소된 스프라이트 크기
        _sprite->getSpriteDC(),                       // 스프라이트 DC (원본 이미지가 들어 있음)
        0, 0,                                          // 원본 이미지의 시작 좌표
        size.x, size.y,                               // 원본 이미지의 크기
        _sprite->getTransparent());                   // 투명 색상

    // 흰색 효과를 켰을 경우 추가 렌더링
    if (_whiteness)
    {
        BITMAP info;
        HBITMAP spriteBitmap = _sprite->getSpriteBitmap();

        // BITMAP 구조체에 이미지 정보 가져오기
        GetObject(spriteBitmap, sizeof(BITMAP), &info);

        // 이미지 전체 픽셀 데이터를 저장할 버퍼 생성
        vector<BYTE> bits(info.bmWidthBytes * info.bmHeight);
        GetBitmapBits(spriteBitmap, bits.size(), bits.data());

        // 이미지 전체 픽셀 순회
        for (int y = 0; y < scaledSize.y; y++)
        {
            for (int x = 0; x < scaledSize.x; x++)
            {
                // 스케일링에 맞춰 원본 이미지에서의 좌표 계산
                int sourceX = x * size.x / scaledSize.x;
                int sourceY = y * size.y / scaledSize.y;

                // RGB 순서에 맞게 픽셀 데이터 가져오기 (BGR 순으로 저장되어 있음)
                BYTE* byte = &bits[sourceY * info.bmWidthBytes + sourceX * 3];
                COLORREF pixelColor = RGB(byte[2], byte[1], byte[0]);

                // 현재 픽셀이 투명색이 아닐 경우
                if (pixelColor != _sprite->getTransparent())
                {
                    // 해당 위치에 흰색으로 덮어 그림 (하이라이트 효과)
                    SetPixel(hDC,
                        pos.x - scaledSize.x / 2 + x,
                        pos.y - scaledSize.y / 2 + y,
                        RGB(255, 255, 255));
                }
            }
        }
    }
}
