#pragma once
#include "ResourceBase.h"
class Texture :
    public ResourceBase
{
public:
    Texture();
    ~Texture();
public:
    void Load(const wstring& filePath);
    LONG GetWidth() const { return _bitInfo.bmWidth; }
    LONG GetHeight() const { return _bitInfo.bmHeight; }
    const HDC& GetTextureDC() const { return _hdc; }
private:
    HBITMAP _hBit;
    HDC _hdc;
    BITMAP _bitInfo;
};

