#pragma once
class TextUI
{
	public:
		TextUI();
		~TextUI();
public:
	void setupFont(float size, const wstring& fontName = L"GG",float fontweight = 400);
	void setColor(const COLORREF& color) { _color = color; }
	void setText(const wstring& text) { _text = text; }
private:
	wstring _text;
	COLORREF _color;
	HFONT _hFont;
	SIZE _textSize;
};

