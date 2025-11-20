#include "pch.h"
#include "Texture.h"
#include "Core.h"

Texture::Texture() : _hBit(nullptr), _hdc(nullptr), _bitInfo(0)
{

}

Texture::~Texture()
{
	::DeleteDC(_hdc);
	::DeleteObject(_hBit);
}

void Texture::Load(const wstring& filePath)
{
	// 1. 인스턴스 핸들: nullptr = 독립형 리소스
	// 2. 경로
	// 3. 파일 형식 - 비트맵인지
	// 4,5. 파일 크기
	// 6. 옵션 플래그
	_hBit = (HBITMAP)::LoadImage(nullptr, filePath.c_str(), IMAGE_BITMAP,
		0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	// 필수
	assert(_hBit);
	_hdc = ::CreateCompatibleDC(GET_SINGLE(Core)->GetMainDC());
	::SelectObject(_hdc, _hBit);
	::GetObject(_hBit, sizeof(BITMAP), &_bitInfo);

}
