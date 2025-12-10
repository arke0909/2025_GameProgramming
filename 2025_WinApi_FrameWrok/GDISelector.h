#pragma once
class GDISelector
{
public:
    GDISelector(HDC _hdc, MyPenType _pen);
    GDISelector(HDC _hdc, MyBrushType _brush);
    GDISelector(HDC _hdc, FontType _font);
    ~GDISelector();
private:
    HDC        m_hDC;
    HPEN    m_hDefaultPen;
    HBRUSH    m_hDefaultBrush;
    HFONT   m_hDefaultFont;
};